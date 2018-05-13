#pragma once

#include "Vec2.h"
#include "XConsole.h"
#include "XMath.h"
#include "IDemo.h"

const int HistoryNum = 10;

const int BallNums = 50;

class BounceBall
{
public:
	BounceBall();

	void SetPosition(const Vec2& InPosition);
	void SetVelocity(const Vec2& InVelocity);
	void SetGravityFactor(const Vec2& InGravityFactor);
	void SetCanBounce(bool bNewBounceState);
	void SetColor(UINT8 InColor);

	// Set all tails' position same as ball's position
	void ResetHistory();
	void Update();
	void Draw();

private:
	Vec2 Position;
	Vec2 Velocity;
	Vec2 GravityFactor;
	bool bCanBounce;
	UINT8 Color;

	Vec2 Histories[HistoryNum];
	int HistoryIndex;

	static const char TailSymbols[HistoryNum + 1];
};

class BounceBallDemo : public IDemo
{
public:
	virtual void Initialize() override;

	virtual void UpdateFrame() override;

private:
	BounceBall Ball[BallNums];
};

FORCEINLINE BounceBall::BounceBall()
	: Position(0.5f * GConsole.GetScreenWidth(), 0.5f * GConsole.GetScreenHeight())
	, Velocity(1.0f, 1.0f)
	, GravityFactor(0.0f, 0.0f)
	, bCanBounce(true)
	, HistoryIndex(0)
{
	Color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}


FORCEINLINE void BounceBall::SetPosition(const Vec2& InPosition)
{
	Position = InPosition;
}

FORCEINLINE void BounceBall::SetVelocity(const Vec2& InVelocity)
{
	Velocity = InVelocity;
}

FORCEINLINE void BounceBall::SetGravityFactor(const Vec2& InGravityFactor)
{
	GravityFactor = InGravityFactor;
}

FORCEINLINE void BounceBall::SetCanBounce(bool bNewBounceState)
{
	bCanBounce = bNewBounceState;
}

FORCEINLINE void BounceBall::SetColor(UINT8 InColor)
{
	Color = InColor;
}
