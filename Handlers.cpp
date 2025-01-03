#include "Handlers.h"
#include <iostream>
using namespace std;

void LogHandler:: log(const string& message) const {
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
        cout << "Unable to open log file!" << endl;
    }
}