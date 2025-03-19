#include "WeaselTimer.h"

using namespace std::chrono;

WeaselTimer::WeaselTimer()
{
	last = steady_clock::now();
}

float WeaselTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float WeaselTimer::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}
