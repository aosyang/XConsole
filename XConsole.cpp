#include "XConsole.h"

XConsole GConsole;

bool XConsole::Initialize(ConsoleInitParameter InitParam /*= ConsoleInitParameter()*/)
{
	hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX ScreenBufferInfo;
	ZeroMemory(&ScreenBufferInfo, sizeof(ScreenBufferInfo));
	ScreenBufferInfo.cbSize = sizeof(ScreenBufferInfo);
	if (!GetConsoleScreenBufferInfoEx(hOutput, &ScreenBufferInfo))
	{
		DWORD ErrorCode = GetLastError();
		return false;
	}

	// Resize console window if user requests to
	if (InitParam.WindowSizeX > 0 && InitParam.WindowSizeY > 0)
	{
		COORD WindowSize = { (SHORT)InitParam.WindowSizeX , (SHORT)InitParam.WindowSizeY };
		ScreenBufferInfo.srWindow.Right = InitParam.WindowSizeX;
		ScreenBufferInfo.srWindow.Bottom = InitParam.WindowSizeY;
		ScreenBufferInfo.dwSize = WindowSize;
		ScreenBufferInfo.dwMaximumWindowSize = WindowSize;
		if (!SetConsoleScreenBufferSize(hOutput, WindowSize))
		{
			DWORD ErrorCode = GetLastError();
			return false;
		}

		if (!SetConsoleScreenBufferInfoEx(hOutput, &ScreenBufferInfo))
		{
			DWORD ErrorCode = GetLastError();
			return false;
		}

		// Wait until console resizing is done
		// TODO: Should query result or use callback functions
		Sleep(100);
	}

	HWND hWnd = GetConsoleWindow();
	RECT WindowRect;
	if (!GetWindowRect(hWnd, &WindowRect))
	{
		DWORD ErrorCode = GetLastError();
		return false;
	}

	int Left = (GetSystemMetrics(SM_CXSCREEN) - (WindowRect.right - WindowRect.left)) / 2;
	int Top = (GetSystemMetrics(SM_CYSCREEN) - (WindowRect.bottom - WindowRect.top)) / 2;

	if (!SetWindowPos(hWnd, NULL, Left, Top, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, 0))
	{
		DWORD ErrorCode = GetLastError();
		return false;
	}

	ScreenWidth = ScreenBufferInfo.srWindow.Right;
	ScreenHeight = ScreenBufferInfo.srWindow.Bottom;
	int BufferArraySize = ScreenWidth * ScreenHeight;

	CharBuffer = new CHAR_INFO[BufferArraySize];

	ClearScreen();

	return true;
}

void XConsole::Shutdown()
{
	delete [] CharBuffer;
}

void XConsole::ClearScreen()
{
	int BufferArraySize = ScreenWidth * ScreenHeight;
	memset(CharBuffer, 0, sizeof(CHAR_INFO) * BufferArraySize);
}

void XConsole::DrawChar(char c, int x, int y, UINT8 ColorCode)
{
	// Checking if out of range
	if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight)
	{
		return;
	}

	int BufferOffset = x + y * ScreenWidth;
	CHAR_INFO& CharInfo = CharBuffer[BufferOffset];
	CharInfo.Char.AsciiChar = c;
	CharInfo.Attributes = (CharInfo.Attributes & ~0xFF) | (ColorCode & 0xFF);
}

void XConsole::DrawCharFast(char c, int x, int y, UINT8 ColorCode)
{
	int BufferOffset = x + y * ScreenWidth;
	CHAR_INFO& CharInfo = CharBuffer[BufferOffset];
	CharInfo.Char.AsciiChar = c;
	CharInfo.Attributes = (CharInfo.Attributes & ~0xFF) | (ColorCode & 0xFF);
}

void XConsole::PresentBuffer() const
{
	COORD BufferSize = { ScreenWidth, ScreenHeight };
	COORD BufferCoord = { 0, 0 };
	SMALL_RECT Region = { 0, 0, ScreenWidth - 1, ScreenHeight - 1 };
	WriteConsoleOutput(hOutput, CharBuffer, BufferSize, BufferCoord, &Region);
}
