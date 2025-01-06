#include "Paczka.h"

// Konstruktor
Paczka::Paczka() : id(0), telefon(""), kodOdbioru(""), u_id(0), gabaryt(nullptr) {}
const Customer* loggedInUser;   // Wska�nik do zalogowanego u�ytkownika (tylko do odczytu)


// Wy�wietlanie informacji o paczce
void Paczka::wyswietlInfo() const {
    cout << "ID paczki: " << id << "Telefon: " << telefon << "Kod odbioru: " << kodOdbioru << "User ID: " << loggedInUser->getId() << "first name: " << loggedInUser->getFirstname() << " surname: " << loggedInUser->getSurname();
    if (gabaryt) {
        gabaryt->wyswietl();  // Wy�wietlenie gabarytu
    }
    else {
        cout << "Brak gabarytu." << endl;
    }
}

void Paczka::updateModificationTime() {
    lastModified = std::time(nullptr);  // Ustawienie bie��cego czasu
}
string Paczka::getLastModified() const {
    char buffer[80];
    struct tm timeinfo; 

    localtime_s(&timeinfo, &lastModified);

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    return std::string(buffer);
}

// Operator wej�cia - wczytywanie danych paczki
istream& operator>>(istream& in, Paczka& obj) {
    
    in >> obj.id     >> obj.telefon     >> obj.status  >> obj.kodOdbioru   >> obj.u_id >> obj.lastModified;
    return in;
}

// Operator wyj�cia - zapis paczki do pliku
ofstream& operator<<(ofstream& os, const Paczka& paczka) {
    os << paczka.id<<" ";
    os << paczka.telefon << " ";
    os << paczka.status << " ";
    os << paczka.kodOdbioru << " ";
    /*os << paczka.numerPaczkomatu << " ";*/
    os << paczka.u_id << " ";
    os << paczka.lastModified ;
    return os;
}

// Destruktor
Paczka::~Paczka() {
    delete gabaryt;  // Zwalniamy pami��, kt�r� dynamicznie przypisali�my do gabarytu
}
