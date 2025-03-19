#pragma once
#include <chrono>

class WeaselTimer
{
public:
	WeaselTimer();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};

