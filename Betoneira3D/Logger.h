#pragma once

#include <string>
#include <filesystem>
#include <sstream>

#include "Status.h"

namespace Betoneira::Logger {
	extern bool logYearMonthDay;
	extern bool logCout;
	extern bool logTime;
	extern bool logTimeSecond;
	extern bool useUTCTimeZone; // whether use UTC or local timezone (default: 0)
	extern bool saveEachLogCall; // dunno if this should be true by default, but it is...
	extern std::string logFileName;

	extern std::filesystem::path logsPath; // (default: "logs")
	extern std::stringstream logData;

	void init(); // used to set the logFileName variable
	void log(std::initializer_list<std::string> args, std::initializer_list<std::string> context = {});
	// saves logData and clears it
	Betoneira::Status saveToFile(std::string file, bool appendMode=false);
}