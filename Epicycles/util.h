#pragma once
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <math.h>
#include "vec.h"

static long long getNanoTime() {
	auto nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
	return nanoseconds_since_epoch;
}

double Pi() {
	return 3.14159265359;
}