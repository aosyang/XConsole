#include "BounceBall.h"

#include <math.h>

// Tail to head
const char BounceBall::TailSymbols[HistoryNum + 1] = ".....ooooO";

void BounceBall::ResetHistory()
{
	for (int i = 0; i < HistoryNum; i++)
	{
		Histories[i] = Position;
	}
}

void BounceBall::Update()
{
	Histories[HistoryIndex] = Position;
	HistoryIndex++;
	HistoryIndex %= HistoryNum;

	Position += Velocity;
	Velocity += GravityFactor;

	if (bCanBounce)
	{
		if (Velocity.X < 0 && Position.X <= 0)
		{
			Velocity.X = fabsf(Velocity.X);
		}
		else if (Velocity.X > 0 && Position.X >= GConsole.GetScreenWidth() - 1)
		{
			Velocity.X = -fabsf(Velocity.X);
		}

		if (Velocity.Y < 0 && Position.Y <= 0)
		{
			Velocity.Y = fabsf(Velocity.Y);
		}
		else if (Velocity.Y > 0 && Position.Y >= GConsole.GetScreenHeight() - 1)
		{
			Velocity.Y = -fabsf(Velocity.Y);
		}
	}
}

void BounceBall::Draw()
{
	int n = 0;
	for (int i = HistoryIndex; i < HistoryIndex + HistoryNum; i++)
	{
		int d = i % HistoryNum;
		GConsole.DrawChar(TailSymbols[n++], (int)Histories[d].X, (int)Histories[d].Y, Color);
	}

	GConsole.DrawChar('O', (int)Position.X, (int)Position.Y, Color);
}

void BounceBallDemo::Initialize()
{
	for (int i = 0; i < BallNums; i++)
	{
		// Random position
		float x = RandF() * (GConsole.GetScreenWidth() - 1);
		float y = RandF() * (GConsole.GetScreenHeight() - 1);
		Ball[i].SetPosition(Vec2(x, y));
		
		// Generate random velocity, avoid having stationary balls
		Vec2 Velocity;
		do
		{
			Velocity = Vec2::RandomVectorInUnitCircle();
		} while (Velocity.X == 0 && Velocity.Y == 0);
		// Adjust y since console character is not square
		Velocity.Y *= 0.5f;
		Ball[i].SetVelocity(Velocity);

		// Random color
		UINT8 Color = rand() % 0xF + 1;
		Ball[i].SetColor(Color);

		//Ball[i].SetGravityFactor(Vec2(0.0f, 0.1f));
	}
}

void BounceBallDemo::UpdateFrame()
{
	for (int i = 0; i < BallNums; i++)
	{
		Ball[i].Update();
		Ball[i].Draw();
	}
}
