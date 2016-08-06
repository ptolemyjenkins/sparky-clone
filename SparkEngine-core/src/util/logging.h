#pragma once
#include <iostream>
namespace sparky { namespace util {
	class Logging {
	public:
		static void log_exit(std::string msg, int errorNum) {
			std::cerr << msg.c_str() << std::endl;
			system("PAUSE");
			exit(errorNum);
		}

		static void log(std::string msg) {
			std::cerr << msg.c_str() << std::endl;
		}
	};
} }