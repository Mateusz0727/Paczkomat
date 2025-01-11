#include "AdminService.h"
#include <iomanip>
#include <sstream>
#include <fstream>

void AdminService::generateRaport() {
    string inputDate;
    cout << "Enter a date (YYYY-MM-DD) or press Enter to use today's date: ";
    cin >> inputDate;

    struct tm currentDate = { 0 };
    if (inputDate.empty()) {
        time_t currentTime = time(nullptr);
        localtime_s(&currentDate, &currentTime);
    }
    else {
        istringstream ss(inputDate);
        ss >> get_time(&currentDate, "%Y-%m-%d");
        if (ss.fail()) {
            cerr << "Invalid date format. Please use YYYY-MM-DD." << endl;
            return;
        }
    }

    string fileName;
    cout << "Enter the name of the file to save the report (e.g., report.txt): ";
    cin >> fileName;

    ofstream reportFile(fileName);
    if (!reportFile) {
        cerr << "Error: Could not create file " << fileName << endl;
        return;
    }

    vector<Paczka> packages = paczkaTable.getAll();

    reportFile << "======================================================================" << endl;
    reportFile << "|                             RAPORT PACZEK                         |" << endl;
    reportFile << "======================================================================" << endl;
    reportFile << left << setw(10) << "ID"
        << setw(15) << "Phone number"
        << setw(15) << "Code"
        << setw(20) << "User Email"
        << setw(15) << "Status"
        << "Last Modified" << endl;
    reportFile << "----------------------------------------------------------------------" << endl;

    for (const Paczka& package : packages) {
        struct tm paczkaDate;
        time_t lastModified = package.getLastModifiedTime();
        localtime_s(&paczkaDate, &lastModified);

        if (currentDate.tm_year == paczkaDate.tm_year &&
            currentDate.tm_mon == paczkaDate.tm_mon &&
            currentDate.tm_mday == paczkaDate.tm_mday) {
            reportFile << left << setw(10) << package.getId()
                << setw(15) << package.getTelefon()
                << setw(15) << package.getKodOdbioru()
                << setw(20) << customerTable.getById(package.getUId()).getEmail()
                << setw(15) << statusToString(package.getStatus())
                << package.getLastModified() << endl;
        }
    }

    reportFile << "======================================================================" << endl;
    reportFile.close();

    cout << "Report saved to " << fileName << endl;
}
