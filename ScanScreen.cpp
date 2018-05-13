#include "ScanScreen.h"

#include "XConsole.h"
#include <math.h>
#include <time.h>

UINT8 ColorArray[0xF];

void ScanScreenDemo::Initialize()
{
	Offset = 0;
	WaveOffset = 0;

	for (int i = 0; i < 8; i++)
	{
		ColorArray[i * 2] = i << 4;
		ColorArray[i * 2 + 1] = (i | 8) << 4;
	}
}

void ScanScreenDemo::UpdateFrame()
{
	for (int i = 0; i < GConsole.GetScreenWidth(); i++)
	{
		float t = (float)i / 15.0f * 3.14159265f * 2.0f * 0.2f - 0.2f * (float)WaveOffset;
		int s = int(sinf(t) * 5.0f + 5.0f);

		for (int j = s; j < GConsole.GetScreenHeight(); j++)
		{
			GConsole.DrawChar('|', i, j, ColorArray[(i + Offset) % 16]);
		}
	}

	Offset++;
	Offset %= 16;

	WaveOffset++;
}
