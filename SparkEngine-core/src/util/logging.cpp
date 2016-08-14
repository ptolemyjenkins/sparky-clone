#include "logging.h"
#include "fileutils.h"

namespace sparky { namespace util{
	std::string Logging::logPath = "";

	void Logging::log_exit(std::string msg, int errorNum)
	{
		std::cerr << msg.c_str() << std::endl;
		if (logPath != "") {
			FileUtils::append_file(logPath.c_str(), msg);
			exit(errorNum);
		}
		system("PAUSE");
		exit(errorNum);
	}

	void Logging::log(std::string msg)
	{
		std::cerr << msg.c_str();
		if (logPath != "") {
			FileUtils::append_file(logPath.c_str(), msg);
		}
	}

	void Logging::clearLog()
	{
		FileUtils::clear_file(logPath.c_str());
	}

} }
