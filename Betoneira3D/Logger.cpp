#include "Logger.h"

#include "System.h"
#include "File.h"

#include <iostream>
#include <chrono>
#include <process.h>

bool Betoneira::Logger::logYearMonthDay = true;
bool Betoneira::Logger::logCout = true;
bool Betoneira::Logger::logTime = true;
bool Betoneira::Logger::logTimeSecond = true;
bool Betoneira::Logger::useUTCTimeZone = false;
bool Betoneira::Logger::saveEachLogCall = true;
std::string Betoneira::Logger::logFileName = "log.log";

void Betoneira::Logger::init() {
    std::tm timeNow;
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t time_tNow = std::chrono::system_clock::to_time_t(now);
        localtime_s(&timeNow, &time_tNow);
    }

    std::stringstream fileName;
    fileName << timeNow.tm_year + 1900
        << '-' << timeNow.tm_mon + 1
        << '-' << timeNow.tm_yday - timeNow.tm_mon * 30
        << '_' << timeNow.tm_hour
        << '_' << _getpid() << ".log";

    logFileName = fileName.str();
}

std::filesystem::path Betoneira::Logger::logsPath{ "logs" };
std::stringstream Betoneira::Logger::logData = {};

std::string Betoneira::Logger::getFormattedTime() {
    std::stringstream formatted;
    
    std::tm timeNow;
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        // Convert to time_t (Unix timestamp)
        std::time_t time_tNow = std::chrono::system_clock::to_time_t(now);

        if (useUTCTimeZone)
            gmtime_s(&timeNow, &time_tNow);
        else
            localtime_s(&timeNow, &time_tNow);
    }

    formatted << '[';

    if (logYearMonthDay)
        formatted << timeNow.tm_year + 1900
        << "-" << timeNow.tm_mon + 1
        << "-" << timeNow.tm_yday - timeNow.tm_mon * 30;

    if (logTime)
    {
        formatted << " " << timeNow.tm_hour << ":" << timeNow.tm_min;
        if (logTimeSecond)
            formatted << ":" << timeNow.tm_sec;
    }

    formatted << "]";

    return formatted.str();
}

std::string Betoneira::Logger::getFormattedContext(std::initializer_list<std::string> context) {
    std::stringstream formatted;
    for (std::string ctx : context)
        formatted << "[" << ctx << "]";

    return formatted.str();
}

void Betoneira::Logger::log(std::initializer_list<std::string> args, std::initializer_list<std::string> context) {
    std::stringstream logMessage;

    logMessage << getFormattedTime() << getFormattedContext(context) << " ";

    for (std::string arg : args)
        logMessage << arg;

    logMessage << '\n';

    if (logCout)
        std::cout << logMessage.str();

    Betoneira::Logger::logData << logMessage.str();

    if (saveEachLogCall) {
        std::filesystem::path copyLogPath{ logsPath };
        copyLogPath.append(logFileName);
        Betoneira::Logger::saveToFile(copyLogPath.string(), true);
    }
}

Betoneira::Status Betoneira::Logger::saveToFile(std::string path, bool appendMode) {
    if (Betoneira::System::pathExists(path) && !Betoneira::System::isFile(path)) {
        return Betoneira::Status::NOT_A_FILE;
    }

    std::filesystem::create_directories(std::filesystem::path(path).remove_filename());

    Betoneira::FileSystem::FileHandler file{ path };

    std::ios_base::openmode mode = Betoneira::FileSystem::FILE_WRITE;
    if (appendMode)
        mode |= Betoneira::FileSystem::FILE_APPEND;

    file.open(mode);

    file.write(Betoneira::Logger::logData.str().c_str());

    file.close();

    Betoneira::Logger::logData.str(std::string());

    return Betoneira::Status::OK;
}