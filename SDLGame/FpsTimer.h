#pragma once
#include <SDL.h>

class FpsTimer
{
public:
	FpsTimer();
	void start();
	float mark();
private:
	unsigned int last;
};