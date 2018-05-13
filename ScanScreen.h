#pragma once

#include "IDemo.h"

class ScanScreenDemo : public IDemo
{
public:
	virtual void Initialize() override;

	virtual void UpdateFrame() override;

private:
	int Offset;
	int WaveOffset;
};