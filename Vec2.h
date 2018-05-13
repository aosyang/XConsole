#pragma once

#include <windows.h>
#include <math.h>

class Vec2
{
public:
	float X, Y;

	Vec2();
	Vec2(float InX, float InY);
	const Vec2& operator=(const Vec2& Rhs);

	Vec2 operator+(const Vec2& Rhs) const;
	Vec2 operator-(const Vec2& Rhs) const;
	Vec2 operator*(float Val) const;
	Vec2 operator/(float Val) const;

	const Vec2& operator+=(const Vec2& Rhs);
	const Vec2& operator-=(const Vec2& Rhs);

	float Length() const;
	float LengthSquared() const;

	// Generate a random vector inside unit circle
	static Vec2 RandomVectorInUnitCircle();
};

FORCEINLINE Vec2::Vec2()
	: X(0.0f)
	, Y(0.0f)
{
}

FORCEINLINE Vec2::Vec2(float InX, float InY)
	: X(InX)
	, Y(InY)
{
}

FORCEINLINE const Vec2& Vec2::operator=(const Vec2& Rhs)
{
	if (&Rhs != this)
	{
		this->X = Rhs.X;
		this->Y = Rhs.Y;
	}

	return *this;
}

FORCEINLINE Vec2 Vec2::operator+(const Vec2& Rhs) const
{
	return Vec2(X + Rhs.X, Y + Rhs.Y);
}

FORCEINLINE Vec2 Vec2::operator-(const Vec2& Rhs) const
{
	return Vec2(X - Rhs.X, Y - Rhs.Y);
}

FORCEINLINE Vec2 Vec2::operator*(float Val) const
{
	return Vec2(X * Val, Y * Val);
}

FORCEINLINE Vec2 Vec2::operator/(float Val) const
{
	return Vec2(X / Val, Y / Val);
}

FORCEINLINE const Vec2& Vec2::operator+=(const Vec2& Rhs)
{
	X += Rhs.X; Y += Rhs.Y;
	return *this;
}

FORCEINLINE const Vec2& Vec2::operator-=(const Vec2& Rhs)
{
	X -= Rhs.X; Y -= Rhs.Y;
	return *this;
}

FORCEINLINE float Vec2::Length() const
{
	return sqrtf(X * X + Y * Y);
}

FORCEINLINE float Vec2::LengthSquared() const
{
	return X * X + Y * Y;
}
