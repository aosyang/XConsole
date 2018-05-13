#pragma once

#include "IDemo.h"
#include "BounceBall.h"

const int FireworksBallNums = 70;

class Fireworks
{
public:
	Fireworks();

	void Update();

	void Draw();

	void CreateFireworks();
	void SetVisible(bool bEnabled);

private:
	BounceBall Ball[FireworksBallNums];

	bool bVisible;
	Vec2 Center;
	int Frame;
};

class FireworksDemo : public IDemo
{
public:
	virtual void Initialize() override;

	virtual void UpdateFrame() override;

private:
	Fireworks FireworksObject[3];

	int Frame;
	int Delay;
	int FireworkIndex;
};