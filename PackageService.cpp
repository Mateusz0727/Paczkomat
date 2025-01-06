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

    cout << "Choose parcel size (A - Small, B - Medium, C - Large): ";
    char x;
    cin >> x;
    x = tolower(x);

    // Ustawienie rozmiaru paczki
    if (x == 'a') {
        package.setGabaryt(new GabarytA());
    }
    else if (x == 'b') {
        package.setGabaryt(new GabarytB());
    }
    else if (x == 'c') {
        package.setGabaryt(new GabarytC());
    }
    else {
        cout << "Invalid size choice! Defaulting to large size.\n";
        package.setGabaryt(new GabarytC());
    }

    // Dodanie paczki do tabeli
    paczkaTable.add(package);

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
    ofstream outFile(fileName, ios::app); // Otwórz plik w trybie dopisywania

    if (outFile.is_open()) {
        outFile << package.getId() << ", nadana, " << currentDate << ", " << currentTime << endl;
        outFile.close();
    }
    else {
        cout << "Error: Could not open file for writing: " << fileName << endl;
    }

    cout << "Parcel successfully added!\n";
}
