#ifndef PACZKA_H
#define PACZKA_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Paczka {
private:
    unsigned int id;
    string telefon;
    string kodOdbioru;
    unsigned int u_id;

public:
    // Konstruktor
    Paczka() : id(0), telefon(""), kodOdbioru(""), u_id(0) {}

    // Gettery i settery
    unsigned int getId() const { return id; }
    void setId(unsigned int id) { this->id = id; }

    string getTelefon() const { return telefon; }
    void setTelefon(const string& telefon) { this->telefon = telefon; }

    string getKodOdbioru() const { return kodOdbioru; }
    void setKodOdbioru(const string& kodOdbioru) { this->kodOdbioru = kodOdbioru; }

    unsigned int getUId() const { return u_id; }
    void setUId(unsigned int u_id) { this->u_id = u_id; }

    // Przeci¹¿enie operatorów
    friend istream& operator>>(istream& in, Paczka& obj);
    friend ofstream& operator<<(ofstream& os, const Paczka& paczka);
};

#endif  // PACZKA_H
