#include "XShapeUtils.h"
#include "XConsole.h"

namespace XShapeUtils
{
	void XShapeUtils::DrawCircle(char c, const Vec2 Center, float Radius, UINT8 Color)
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
					GConsole.DrawChar(c, x, y, Color);
				}
			}
		}
	}
}
