#include "Fireworks.h"
#include <math.h>
#include "XShapeUtils.h"

Fireworks::Fireworks()
	: bVisible(false)
	, Frame(0)
{

}

void Fireworks::Update()
{
	if (bVisible)
	{
		for (int i = 0; i < FireworksBallNums; i++)
		{
			Ball[i].Update();
		}
	}

	Frame++;
}

void Fireworks::Draw()
{
	if (bVisible)
	{
		//static const char GlowCharArray[] = { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };
		//static const float GlowScaleArray[] = { 0.5f, 0.675f, 0.75f, 1.0f, 1.0f, 1.0f, 1.0f, 0.9f, 0.8f, 0.7f };
		//if (Frame < ARRAYSIZE(GlowCharArray))
		//{
		//	int Index = Frame;
		//	float Radius = GlowScaleArray[Index] * 20.0f;
		//	XShapeUtils::DrawCircle(GlowCharArray[Index], Center, Radius, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		//}

		for (int i = 0; i < FireworksBallNums; i++)
		{
			Ball[i].Draw();
		}
	}
}

void Fireworks::CreateFireworks()
{
	float x = (0.5f + (RandF() - 0.5f) * 0.5f) * GConsole.GetScreenWidth();
	float y = (0.5f + (RandF() - 0.5f) * 0.5f) * GConsole.GetScreenHeight();

	Center = Vec2(x, y);

	UINT8 PrimaryColor = rand() % 0xF + 1;
	UINT8 SecondaryColor = rand() % 0xF + 1;

	float GravityY = RandF() * 0.05f;
	float Scale = RandF() * 0.5f + 0.4f;

	for (int i = 0; i < FireworksBallNums; i++)
	{
		Ball[i].SetPosition(Vec2(x, y));

		Vec2 Velocity;
		do
		{
			Velocity = Vec2::RandomVectorInUnitCircle() * Scale;
		} while (Velocity.X == 0 && Velocity.Y == 0);
		// Adjust y since console character is not square
		Velocity.Y *= 0.5f;
		Ball[i].SetVelocity(Velocity);
		Ball[i].SetGravityFactor(Vec2(0.0f, GravityY));
		Ball[i].SetCanBounce(false);

		// Random color
		Ball[i].SetColor(RandF() < 0.8f ? PrimaryColor : SecondaryColor);
	}

	bVisible = true;
	Frame = 0;
}

void Fireworks::SetVisible(bool bEnabled)
{
	bVisible = bEnabled;
}

void FireworksDemo::Initialize()
{
	Frame = 0;
	FireworkIndex = 0;
	Delay = 20;
}

void FireworksDemo::UpdateFrame()
{
	for (int i = 0; i < 3; i++)
	{
		FireworksObject[i].Update();
	}

	for (int i = 0; i < 3; i++)
	{
		FireworksObject[i].Draw();
	}

	Frame++;
	if (Frame > Delay)
	{
		Frame = 0;
		FireworksObject[FireworkIndex].CreateFireworks();
		FireworkIndex++;
		FireworkIndex %= 3;

		if (Delay < 15)
		{
			Delay = rand() % 20 + 30;
		}
		else
		{
			Delay = rand() % 30 + 20;
		}
	}
}
