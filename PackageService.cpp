#include<iostream>
#include "PackageService.h"
#include "Extensions.h"
void PackageService::nadaj(Customer user) {
    Paczka package =  Paczka();
    package.setUId(user.getId());

    cout << "Enter recipient's phone number: ";
    string telefon;
    cin >> telefon;
    package.setTelefon(telefon);

   /* cout << "Enter parcel locker number: ";
    string numerPaczkomatu;
    cin >> numerPaczkomatu;
    package.setNumerPaczkomatu(numerPaczkomatu);*/

    cout << "Choose parcel size (A - Small, B - Medium, C - Large): ";
    char x;
    cin >> x;
    x = tolower(x);

    // Tworzenie obiektu Gabaryt na podstawie wyboru u¿ytkownika
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
        cout << "Invalid size choice! Defaulting to large size." << endl;
        package.setGabaryt(new GabarytC());
    }
    package.setKodOdbioru(generateRandomDigits());
    paczkaTable.add(package);
   

}