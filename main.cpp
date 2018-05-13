
#include "XConsole.h"
#include "BounceBall.h"
#include "ScanScreen.h"
#include "Fireworks.h"
#include "Shapes.h"
#include <time.h>
#include <iostream>

int main(int argc, char *argv[])
{
	FireworksDemo Demo;
	srand(static_cast<unsigned int>(time(0)));

	ConsoleInitParameter InitParam;
	InitParam.WindowSizeX = 220;
	InitParam.WindowSizeY = 60;

	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	const float TargetFps = 32.0f;
	const float TargetFrameTime = 1000.0f / TargetFps;

	if (GConsole.Initialize(InitParam))
	{
		Demo.Initialize();

		LARGE_INTEGER StartTime, EndTime;
		QueryPerformanceCounter(&StartTime);

		while (1)
		{
			QueryPerformanceCounter(&EndTime);
			float ElapsedTime = (EndTime.QuadPart - StartTime.QuadPart) * 1000.0f / Frequency.QuadPart;

			if (ElapsedTime >= TargetFrameTime)
			{
#if 0
				char DebugText[256];
				if (ElapsedTime - TargetFrameTime > 2.0f)
				{
					sprintf_s(DebugText, ">>> Frame time: %f <<<\n", ElapsedTime);
				}
				else
				{
					sprintf_s(DebugText, "Frame time: %f\n", ElapsedTime);
				}
				OutputDebugStringA(DebugText);
#endif	// if 0
				
				StartTime = EndTime;

				GConsole.ClearScreen();
				Demo.UpdateFrame();
				GConsole.PresentBuffer();
			}
			else if (TargetFrameTime - ElapsedTime > 3.f)
			{
				// Make cpu less busy. Since Sleep() is not precise, we only sleep for ~1ms and keep an eye one the frame time
				Sleep(1);
			}
		}

		GConsole.Shutdown();
	}
	else
	{
		std::cout << "Failed to initialize XConsole!" << std::endl;
	}

	return 0;
}