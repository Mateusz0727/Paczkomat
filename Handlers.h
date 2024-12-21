#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

class LogHandler {
private:
    string logFileName;

public:
    LogHandler(const string& logFile = "error_log.txt")
        : logFileName(logFile) {}

    void log(const string& message) const {
        time_t currentTime = time(nullptr);
        tm localTime;  
        
        localtime_s(&localTime, &currentTime);

        char timeStr[100];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);

        ofstream logFile(logFileName, ios::app);
        if (logFile.is_open()) {
            logFile << timeStr << ": " << message << endl;
            logFile.close();
        }
        else {
            cerr << "Unable to open log file!" << endl;
        }
    }
};

#endif // ERROR_HANDLER_H
