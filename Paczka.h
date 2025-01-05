#ifndef PACZKA_H
#define PACZKA_H

#include <string>
#include <iostream>
#include <fstream>
#include "EnumStatus.h"
#include "Customer.h"
using namespace std;

// Klasa abstrakcyjna Gabaryt
class Gabaryt {
public:
    virtual void wyswietl() const = 0;  // Czysto wirtualna funkcja
    virtual ~Gabaryt() {}  // Wirtualny destruktor, zapewnia usuwanie obiektów pochodnych
    virtual string getSize() const = 0;
};

// Klasy pochodne Gabaryt
class GabarytA : public Gabaryt {
public:
    void wyswietl() const override {
        cout << "Gabaryt: duzy" << endl;
    }
    string getSize() const override {
        return "L";
    }
};

class GabarytB : public Gabaryt {
public:
    void wyswietl() const override {
        cout << "Gabaryt: sredni" << endl;
    }
    string getSize() const override {
        return "M";
    }
};

class GabarytC : public Gabaryt {
public:
    void wyswietl() const override {
        cout << "Gabaryt: maly" << endl;
    }
    string getSize() const override {
        return "S";
    }
};

// Klasa Paczka
class Paczka {
private:
    
    unsigned int id;
    string telefon;
    string kodOdbioru;
    string numerPaczkomatu;
    unsigned int u_id;
    Gabaryt* gabaryt;  // WskaŸnik do gabarytu
    Status status;

public:
    // Konstruktor
    Paczka();

    // Gettery i settery
    unsigned int getId() const { return id; }
    void setId(unsigned int id) { this->id = id; }

    string getTelefon() const { return telefon; }
    void setTelefon(const string& telefon) { this->telefon = telefon; }

    string getKodOdbioru() const { return kodOdbioru; }
    void setKodOdbioru(const string& kodOdbioru) { this->kodOdbioru = kodOdbioru; }

    string getNumerPaczkomatu() const { return numerPaczkomatu; }
    void setNumerPaczkomatu(const string& numerPaczkomatu) { this->numerPaczkomatu = numerPaczkomatu; }

    unsigned int getUId() const { return u_id; }
    void setUId(unsigned int u_id) { this->u_id = u_id; }

    // Ustawienie gabarytu
    void setGabaryt(Gabaryt* g);

    // Wyœwietlenie informacji o paczce
    void wyswietlInfo() const;
    //nadawanie


    // Przeci¹¿enie operatorów
    friend istream& operator>>(istream& in, Paczka& obj);
    friend ofstream& operator<<(ofstream& os, const Paczka& paczka);

    // Destruktor
    ~Paczka();
};

#endif  // PACZKA_H
