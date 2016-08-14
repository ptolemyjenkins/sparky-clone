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
			util::Logging::log("Error: Stop Invocation call without matching start invocation");
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
		char number[24];
		sprintf(number, "%.2f", time);
		std::string a = message;
		std::string b = number;
		util::Logging::log(a + " " + b + "ms. "); 
		totalTime = 0;
		numInvocations = 0;
		return time;
	}
} }