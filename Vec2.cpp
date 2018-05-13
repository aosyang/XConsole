#include "Vec2.h"

#include "XMath.h"

Vec2 Vec2::RandomVectorInUnitCircle()
{
	float a = RandF() * 2 * fPI;
	float r = 3.0f * sqrtf(RandF());

	float x = r * cosf(a);
	float y = r * sinf(a);

	return Vec2(x, y);
}
