#include "Paczka.h"
#include <sstream>
// Konstruktor
Paczka::Paczka() : id(0), telefon(""), kodOdbioru(""), u_id(0), gabaryt(nullptr) {}
const Customer* loggedInUser;  


// Wyœwietlanie informacji o paczce
void Paczka::wyswietlInfo() const {
    cout << "package ID: " << id << "phone number: " << telefon << "Code: " << kodOdbioru << "User ID: " << loggedInUser->getId() << "first name: " << loggedInUser->getFirstname() << " surname: " << loggedInUser->getSurname();
    if (gabaryt) {
        gabaryt->wyswietl();  // Wyœwietlenie gabarytu
    }
    else {
        cout << "No size found" << endl;
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
                throw runtime_error("Incorrect status in an input data.");
            }
        }
        if (getline(ss, token, ',')) obj.kodOdbioru = token;
        if (getline(ss, token, ',')) obj.u_id = stoi(token);
        if (getline(ss, token, ',')) obj.lastModified = stoll(token);

        if (getline(ss, token, ',')) {
            if (token == "A") {
                obj.gabaryt = new GabarytA();
            }
            else if (token == "B") {
                obj.gabaryt = new GabarytB();
            }
            else if (token == "C") {
                obj.gabaryt = new GabarytC();
            }
            else {
                throw runtime_error("Incorrect size in an input data.");
            }
        }
    }
    return in;
}

ostream& operator<<(ostream& os, const Paczka& paczka) {
    os << paczka.id << ",";
    os << paczka.telefon << ",";
    os << paczka.status << ",";
    os << paczka.kodOdbioru << ",";
    os << paczka.u_id << ",";
    os << paczka.lastModified << ",";

    if (paczka.gabaryt) {
        if (dynamic_cast<GabarytA*>(paczka.gabaryt)) {
            os << "A";
        }
        else if (dynamic_cast<GabarytB*>(paczka.gabaryt)) {
            os << "B";
        }
        else if (dynamic_cast<GabarytC*>(paczka.gabaryt)) {
            os << "C";
        }
        else {
            os << "Nieznany";
        }
    }
    else {
        os << "Brak gabarytu";  
    }

    return os;
}

// Destruktor
Paczka::~Paczka() {
    /*delete gabaryt;*/  // Zwalniamy pamiêæ, któr¹ dynamicznie przypisaliœmy do gabarytu
}
