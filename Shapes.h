#pragma once

#include "IDemo.h"
#include "Vec2.h"

class ShapesDemo : public IDemo
{
public:
	virtual void Initialize() override;
	virtual void UpdateFrame() override;

private:
	void DrawCircle(char c, const Vec2 Center, float Radius);

	int Frame;
};