#include "profileTimer.h"


namespace sparky { namespace profiling {
	ProfileTimer::ProfileTimer()
	{
		numInvocations = 0;
		totalTime = 0;
		startTime = 0;
	}
	void ProfileTimer::startInvocation()
	{
		startTime = util::Time::getNanoTime();
	}
	void ProfileTimer::stopInvocation()
	{
		if (startTime == 0) {
			std::cout << "Error: Stop Invocation call without matching start invocation" << std::endl;
			return;
		}
		numInvocations++;
		totalTime += (util::Time::getNanoTime() - startTime);
		startTime = 0;
	}
	double ProfileTimer::displayAndReset(const char * message)
	{
		return displayAndReset(message, 0);
	}
	double ProfileTimer::displayAndReset(const char * message, double dividend)
	{
		double time;
		if (dividend == 0) {
			if (numInvocations != 0) {
				dividend = numInvocations;
			}
			else {
				time = 0;
				return time;
			}
		}
		time = totalTime / (double) (1000000 * dividend);
		printf("%s %.2fms. ", message, time);
		totalTime = 0;
		numInvocations = 0;
		return time;
	}
} }