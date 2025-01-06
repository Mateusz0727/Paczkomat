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
    if (locker->canFitPackage(GabarytA())) {
        cout << "A - Large\n";
        hasOptions = true;
    }
    if (locker->canFitPackage(GabarytB())) {
        cout << "B - Medium\n";
        hasOptions = true;
    }
    if (locker->canFitPackage(GabarytC())) {
        cout << "C - Small\n";
        hasOptions = true;
    }

    if (!hasOptions) {
        cout << "No available slots in the locker. Please try again later.\n";
        return;
    }
    cout << "Choose parcel size (A - Large, B - Medium, C - Small): ";
    char x;
    cin >> x;
    x = tolower(x);

    // Ustawienie rozmiaru paczki
    Gabaryt* selectedGabaryt = nullptr;

    if (x == 'a' && locker->canFitPackage(GabarytA())) {
        selectedGabaryt = new GabarytA();
    }
    else if (x == 'b' && locker->canFitPackage(GabarytB())) {
        selectedGabaryt = new GabarytB();
    }
    else if (x == 'c' && locker->canFitPackage(GabarytC())) {
        selectedGabaryt = new GabarytC();
    }
    else {
        cout << "Invalid size choice! Defaulting to large size.\n";
        package.setGabaryt(new GabarytC());
    }
    package.setKodOdbioru(generateRandomDigits());
    // Dodanie paczki do tabeli
    paczkaTable.add(package);
    locker->reserveSlot(*selectedGabaryt);
    cout << "Kod odbioru tej paczki to " + package.getKodOdbioru() << endl;


    cout << package.getLastModified()<<endl;
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

    cout << "Package successfully added!\n";
}

void PackageService::pickUp( )
{
    string pickUpCode;
    cout << "Enter your pickup code: ";
    cin >> pickUpCode;
    vector<Paczka> packages = paczkaTable.getAll();
    Paczka packageCollected;
    bool found = false;
    for (Paczka package : packages)
    {
        if (isModifiedMoreThanFiveMinutesAgo(package.getLastModifiedTime()))
        {
            package.setStatus(Status::doOdebrania);
            paczkaTable.update(package);
        }
        if ( package.getKodOdbioru() == pickUpCode &&package.getStatus()==Status::doOdebrania)
        {
            packageCollected = package;
            found = true;
            break;
        }
    }
    if (found) {
        packageCollected.setStatus(Status::odebrana);
        cout << "Paczka odebrana pomyœlnie!" << endl;

        paczkaTable.update(packageCollected);
    }
    else {
        cout << "Nie znaleziono paczki do odbioru lub paczka ma nieodpowiedni status." << endl;
    }
}
