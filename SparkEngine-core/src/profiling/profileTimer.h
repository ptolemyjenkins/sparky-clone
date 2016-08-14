#pragma once
#include <string>
#include "../util/time.h"
#include "../util/fileUtils.h"

namespace sparky { namespace profiling {
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
	};

} }