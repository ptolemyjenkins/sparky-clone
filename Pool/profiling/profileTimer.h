#pragma once
#include <iostream>
#include "time.h"
class ProfileTimer
{
private:
	int numInvocations;
	long long totalTime;
	long long startTime;
public:
	ProfileTimer();
	void startInvocation();
	void stopInvocation();
	double displayAndReset(const char* message);
	double displayAndReset(const char* message, double dividend);
	int getNumInvocations();
};