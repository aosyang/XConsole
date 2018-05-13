#pragma once

// The interface of demo class
class IDemo
{
public:
	virtual void Initialize() = 0;
	virtual void UpdateFrame() = 0;
};
