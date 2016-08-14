#pragma once
#include <iostream>
#include <string>
namespace sparky { namespace util {
	class Logging {
	public:
		static std::string logPath;
		static void log_exit(std::string msg, int errorNum);
		static void log(std::string msg);
		static void clearLog();
	};
} }