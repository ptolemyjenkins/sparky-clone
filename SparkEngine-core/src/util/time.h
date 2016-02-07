#pragma once
#include <chrono>
namespace sparky { namespace util {
	class Time
	{
	public:
		static long long getNanoTime() {
			auto nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
			return nanoseconds_since_epoch;
		}

		static long long getMicroTime() {
			auto microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
			return microseconds_since_epoch;
		}

		static long long getMilliTime() {
			auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
			return milliseconds_since_epoch;
		}

		static double NanoToSecond(long long nanoseconds) {
			return nanoseconds / 1000000000.0;
		}

		static double MicroToSecond(long long microseconds) {
			return microseconds / 1000000.0;
		}

		static double MilliToSecond(long long milliseconds) {
			return milliseconds / 1000.0;
		}
	};
} }