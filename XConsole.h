#pragma once

#include <windows.h>

struct ConsoleInitParameter
{
	ConsoleInitParameter();

	int WindowSizeX;
	int WindowSizeY;
};

class XConsole
{
public:
	bool Initialize(ConsoleInitParameter InitParam = ConsoleInitParameter());
	void Shutdown();

	void ClearScreen();

	// Draw a character at given position of screen
	void DrawChar(char c, int x, int y, UINT8 ColorCode);

	// Draw a character WITHOUT memory checking. Faster than DrawChar but may crash.
	void DrawCharFast(char c, int x, int y, UINT8 ColorCode);

	// Present current buffer in console window
	void PresentBuffer() const;

	int GetScreenWidth() const;
	int GetScreenHeight() const;

private:
	HANDLE hOutput;
	SHORT ScreenWidth;
	SHORT ScreenHeight;
	CHAR_INFO* CharBuffer;
};

extern XConsole GConsole;


FORCEINLINE ConsoleInitParameter::ConsoleInitParameter()
	: WindowSizeX(-1)
	, WindowSizeY(-1)
{

}

FORCEINLINE int XConsole::GetScreenWidth() const
{
	return (int)ScreenWidth;
}

FORCEINLINE int XConsole::GetScreenHeight() const
{
	return (int)ScreenHeight;
}
