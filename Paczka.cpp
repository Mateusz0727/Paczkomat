#include "Paczka.h"

// Konstruktor
Paczka::Paczka() : id(0), telefon(""), kodOdbioru(""), u_id(0), gabaryt(nullptr) {}

// Settery
void Paczka::setGabaryt(Gabaryt* g) {
    gabaryt = g;  // Ustawienie wska�nika na gabaryt
}

// Wy�wietlanie informacji o paczce
void Paczka::wyswietlInfo() const {
    cout << "ID paczki: " << id << endl;
    cout << "Telefon: " << telefon << endl;
    cout << "Kod odbioru: " << kodOdbioru << endl;
    cout << "User ID: " << u_id << endl;
    if (gabaryt) {
        gabaryt->wyswietl();  // Wy�wietlenie gabarytu
    }
    else {
        cout << "Brak gabarytu." << endl;
    }
}

void Paczka::nadaj() {
    cout << "Enter recipient's phone number: ";
    cin >> telefon;

    cout << "Enter parcel locker number: ";
    cin >> numerPaczkomatu;

    cout << "Choose parcel size (A - Small, B - Medium, C - Large): ";
    char x;
    cin >> x;
    x = tolower(x);  // Zmiana na ma�e litery

    // Tworzenie obiektu Gabaryt na podstawie wyboru u�ytkownika
    if (x == 'a') {
        gabaryt = new GabarytA();
    }
    else if (x == 'b') {
        gabaryt = new GabarytB();
    }
    else if (x == 'c') {
        gabaryt = new GabarytC();
    }
    else {
        cout << "Invalid size choice! Defaulting to large size." << endl;
        gabaryt = new GabarytC();  // Domy�lny wyb�r gabarytu du�ego
    }

    // Zapis do pliku
    ofstream file("paczka.txt", ios::app);  // Otwieramy plik w trybie dopisywania
    if (file.is_open()) {
        file << *this;  // Zapisujemy paczk� do pliku
        cout << "Paczka zosta�a nadana i zapisana w pliku." << endl;
        file.close();
    }
    else {
        cout << "Nie uda�o si� otworzy� pliku do zapisu." << endl;
    }
}

// Operator wej�cia - wczytywanie danych paczki
istream& operator>>(istream& in, Paczka& obj) {
    cout << "Podaj ID paczki: ";
    in >> obj.id;
    in.ignore();  // Ignorowanie nowej linii po wczytaniu ID
    cout << "Podaj telefon: ";
    getline(in, obj.telefon);
    cout << "Podaj kod odbioru: ";
    getline(in, obj.kodOdbioru);
    cout << "Podaj User ID: ";
    in >> obj.u_id;
    return in;
}

// Operator wyj�cia - zapis paczki do pliku
ofstream& operator<<(ofstream& os, const Paczka& paczka) {
    os << paczka.id << endl;
    os << paczka.telefon << endl;
    os << paczka.kodOdbioru << endl;
    os << paczka.u_id << endl;
    return os;
}

// Destruktor
Paczka::~Paczka() {
    delete gabaryt;  // Zwalniamy pami��, kt�r� dynamicznie przypisali�my do gabarytu
}
