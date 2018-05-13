#pragma once

const float fPI = 3.14159265f;

// Returns a random float number between 0.0f and 1.0f
FORCEINLINE float RandF()
{
	return (float)rand() / (float)RAND_MAX;
}

namespace XMath
{
	template<typename T>
	FORCEINLINE T Square(T Val)
	{
		return Val * Val;
	}
}

template<typename T>
T SampleArrayByRatio(T* Array, int ArraySize, float Ratio)
{
	int Index = (int)(Ratio * ArraySize);
	if (Index >= ArraySize)
	{
		Index = ArraySize - 1;
	}
	return Array[Index];
}
