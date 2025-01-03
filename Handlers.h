#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
class LogHandler {
private:
    string logFileName;

public:
    LogHandler(const string& logFile = "error_log.txt")
        : logFileName(logFile) {}

    void log(const string& message) const;
};

#endif // ERROR_HANDLER_H
