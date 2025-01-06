#include "Paczka.h"

// Konstruktor
Paczka::Paczka() : id(0), telefon(""), kodOdbioru(""), u_id(0), gabaryt(nullptr) {}
const Customer* loggedInUser;   // Wskaünik do zalogowanego uøytkownika (tylko do odczytu)
// Settery
void Paczka::setGabaryt(Gabaryt* g) {
    gabaryt = g;  // Ustawienie wskaünika na gabaryt
}

// Wyúwietlanie informacji o paczce
void Paczka::wyswietlInfo() const {
    cout << "ID paczki: " << id << "Telefon: " << telefon << "Kod odbioru: " << kodOdbioru << "User ID: " << loggedInUser->getId() << "first name: " << loggedInUser->getFirstname() << " surname: " << loggedInUser->getSurname();
    if (gabaryt) {
        gabaryt->wyswietl();  // Wyúwietlenie gabarytu
    }
    else {
        cout << "Brak gabarytu." << endl;
    }
}



// Operator wejúcia - wczytywanie danych paczki
istream& operator>>(istream& in, Paczka& obj) {
    
    in >> obj.id     >> obj.telefon     >> obj.status  >> obj.kodOdbioru   >> obj.u_id;
    return in;
}

// Operator wyjúcia - zapis paczki do pliku
ofstream& operator<<(ofstream& os, const Paczka& paczka) {
    os << paczka.id<<" ";
    os << paczka.telefon << " ";
    os << paczka.status << " ";
    os << paczka.kodOdbioru << " ";
    /*os << paczka.numerPaczkomatu << " ";*/
    os << paczka.u_id;
    return os;
}

// Destruktor
Paczka::~Paczka() {
   /* delete gabaryt;*/  // Zwalniamy pamiÍÊ, ktÛrπ dynamicznie przypisaliúmy do gabarytu
}
