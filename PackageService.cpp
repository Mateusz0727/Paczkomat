#include "PackageService.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "Extensions.h"

using namespace std;

void PackageService::nadaj(Customer user) {
   
    Paczka package;
    package.setUId(user.getId());

    cout << "Enter recipient's phone number: ";
    string telefon;
    cin.ignore();
    getline(cin, telefon);

    // Walidacja numeru telefonu
    if (telefon.empty()) {
        cout << "Invalid phone number. Please try again.\n";
        return;
    }
    package.setTelefon(telefon);

    cout << "Available parcel sizes:\n";
    bool hasOptions = false;
    if (lockerService.canFitPackage(GabarytA())) {
        cout << "A - Large\n";
        hasOptions = true;
    }
    if (lockerService.canFitPackage(GabarytB())) {
        cout << "B - Medium\n";
        hasOptions = true;
    }
    if (lockerService.canFitPackage(GabarytC())) {
        cout << "C - Small\n";
        hasOptions = true;
    }

    if (!hasOptions) {
        cout << "No available slots in the locker. Please try again later.\n";
        return;
    }

    cout << "Choose package size: ";
    char x;
    cin >> x;
    x = tolower(x);

    Gabaryt* selectedGabaryt = nullptr;

    if (x == 'a' && lockerService.canFitPackage(GabarytA())) {
        selectedGabaryt = new GabarytA();
    }
    else if (x == 'b' && lockerService.canFitPackage(GabarytB())) {
        selectedGabaryt = new GabarytB();
    }
    else if (x == 'c' && lockerService.canFitPackage(GabarytC())) {
        selectedGabaryt = new GabarytC();
    }
    else {
        cout << "Invalid size choice! Defaulting to large size.\n";
        selectedGabaryt = new GabarytA();
    }

    package.setGabaryt(selectedGabaryt);
    package.setKodOdbioru(generateRandomDigits());

    // Dodanie paczki do tabeli:
    // teraz add(T& entity) ustawi ID w oryginalnym obiekcie 'package'
    paczkaTable.add(package);

    // Zarezerwuj slot w paczkomacie
    lockerService.reserveSlot(*selectedGabaryt);

    // Teraz 'package.getId()' jest ju¿ aktualnym ID z bazy!
    cout << "Code of this package: " << package.getKodOdbioru() << endl;
    cout << "You sent package with ID = " << package.getId() << endl;
    cout << "Last modified: " << package.getLastModified() << endl;

    // Pobranie bie¿¹cej daty i godziny
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    string currentDate = to_string(1900 + ltm.tm_year) + "-" +
        to_string(1 + ltm.tm_mon) + "-" +
        to_string(ltm.tm_mday);

    string currentTime = to_string(ltm.tm_hour) + ":" +
        to_string(ltm.tm_min) + ":" +
        to_string(ltm.tm_sec);

    // Dodanie informacji o paczce do pliku u¿ytkownika
    string fileName = "users_info/" + to_string(user.getId()) + "_info.txt";
    ofstream outFile(fileName, ios::app);
    if (outFile.is_open()) {
        // Teraz paczka ma poprawne ID
        outFile << package.getId() << ", sent, "
            << currentDate << ", "
            << currentTime << endl;
        outFile.close();
    }
    else {
        cout << "Error: Could not open file for writing: " << fileName << endl;
    }

    cout << "Package successfully added!\n";
}

void PackageService::pickUp(Customer user) {
    string pickUpCode;
    cout << "Enter your pickup code: ";
    cin >> pickUpCode;

    vector<Paczka> packages = paczkaTable.getAll();
    Paczka packageCollected;
    bool found = false;

    for (Paczka package : packages) {
        // Automatyczna zmiana statusu po 5 minutach
        if (isModifiedMoreThanFiveMinutesAgo(package.getLastModifiedTime())) {
            package.setStatus(Status::doOdebrania);
            paczkaTable.update(package);
        }

        if (package.getKodOdbioru() == pickUpCode &&
            package.getStatus() == Status::doOdebrania)
        {
            packageCollected = package;
            
            found = true;
            break;
        }
    }

    if (found) {
        packageCollected.setStatus(Status::odebrana);
        cout << "Package successfully picked up! ID = "
            << packageCollected.getId() << endl;

        paczkaTable.update(packageCollected);

        Gabaryt* gabaryt = packageCollected.getGabaryt();
        lockerService.releaseSlot(*gabaryt);  
        cout << "Slot for the package has been released.\n";

        // Pobranie bie¿¹cej daty i godziny
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        string currentDate = to_string(1900 + ltm.tm_year) + "-" +
            to_string(1 + ltm.tm_mon) + "-" +
            to_string(ltm.tm_mday);

        string currentTime = to_string(ltm.tm_hour) + ":" +
            to_string(ltm.tm_min) + ":" +
            to_string(ltm.tm_sec);

        // Dodanie informacji o paczce do pliku u¿ytkownika
        string fileName = "users_info/" + to_string(user.getId()) + "_info.txt";
        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            // Teraz paczka ma poprawne ID
            outFile << packageCollected.getId() << ", picked up, "
                << currentDate << ", "
                << currentTime << endl;
            outFile.close();
        }
        else {
            cout << "Error: Could not open file for writing: " << fileName << endl;
        }
    }
    else {
        cout << "Package not found or incorrect status.\n";
    }

}
