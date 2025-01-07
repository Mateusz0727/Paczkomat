#include "Paczka.h"
#include <sstream>
// Konstruktor
Paczka::Paczka() : id(0), telefon(""), kodOdbioru(""), u_id(0), gabaryt(nullptr) {}
const Customer* loggedInUser;  


// Wyœwietlanie informacji o paczce
void Paczka::wyswietlInfo() const {
    cout << "ID paczki: " << id << "Telefon: " << telefon << "Kod odbioru: " << kodOdbioru << "User ID: " << loggedInUser->getId() << "first name: " << loggedInUser->getFirstname() << " surname: " << loggedInUser->getSurname();
    if (gabaryt) {
        gabaryt->wyswietl();  // Wyœwietlenie gabarytu
    }
    else {
        cout << "Brak gabarytu." << endl;
    }
}

void Paczka::updateModificationTime() {
    lastModified = time(nullptr);  // Ustawienie bie¿¹cego czasu
}
string Paczka::getLastModified() const {
    char buffer[80];
    struct tm timeinfo; 

    localtime_s(&timeinfo, &lastModified);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    return string(buffer);
}
istream& operator>>(istream& in, Paczka& obj) {
    string line;
    if (getline(in, line)) {
        stringstream ss(line);
        string token;

        if (getline(ss, token, ',')) obj.id = stoi(token);
        if (getline(ss, token, ',')) obj.telefon = token;
        if (getline(ss, token, ',')) {
            stringstream statusStream(token);
            statusStream >> obj.status; 
            if (statusStream.fail()) {
                throw runtime_error("Niepoprawny status w danych wejœciowych.");
            }
        }
        if (getline(ss, token, ',')) obj.kodOdbioru = token;
       
        if (getline(ss, token, ',')) obj.u_id = stoi(token);
        if (getline(ss, token, ',')) obj.lastModified = stoll(token);
    }
    return in;
}

// Operator wyjœcia - zapis paczki do pliku
ostream& operator<<(ostream& os, const Paczka& paczka) {
    os << paczka.id << ",";
    os << paczka.telefon << ",";
    os << paczka.status << ",";
    os << paczka.kodOdbioru << ",";
    os << paczka.u_id << ",";
    os << paczka.lastModified;
    return os;
}

// Destruktor
Paczka::~Paczka() {
    delete gabaryt;  // Zwalniamy pamiêæ, któr¹ dynamicznie przypisaliœmy do gabarytu
}
