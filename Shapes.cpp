#include "Shapes.h"
#include "XMath.h"
#include "XConsole.h"

void ShapesDemo::Initialize()
{
	Frame = 0;
}

void ShapesDemo::UpdateFrame()
{
	float Radius = sinf((float)Frame * 0.05f) * 20.0f + 50.0f;
	char CharArray[] = { '@', 'O', 'o', '.', ' ' };
	int Index = int((float)Frame * 0.25f) % ARRAYSIZE(CharArray);
	//float Radius = 58.0f;
	float center_x = (float)GConsole.GetScreenWidth() / 2;
	float center_y = (float)GConsole.GetScreenHeight() / 2;
	DrawCircle('@', Vec2(center_x, center_y), Radius);

	Frame++;
}

void ShapesDemo::DrawCircle(char c, const Vec2 Center, float Radius)
{
	int x_start = (int)(Center.X - Radius);
	int x_end = (int)(Center.X + Radius);
	int y_start = (int)(Center.Y - Radius);
	int y_end = (int)(Center.Y + Radius);

	for (int y = y_start; y <= y_end; y++)
	{
		for (int x = x_start; x <= x_end; x++)
		{
			float dx = (float)x - Center.X;
			float dy = (float)y - Center.Y;
			dy *= 2.0f;
			Vec2 Point(dx, dy);
			if (Point.Length() <= Radius)
			{
				static const UINT8 ColorTable[] = { 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15 };
				float Ratio = Point.Length() / Radius;
				UINT8 Color = SampleArrayByRatio(ColorTable, ARRAYSIZE(ColorTable), Ratio);
				GConsole.DrawChar(c, x, y, Color);
			}
		}
	}
}
