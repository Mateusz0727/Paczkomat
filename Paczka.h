#ifndef PACZKA_H
#define PACZKA_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime> 
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
    time_t lastModified;
    void updateModificationTime();

public:
    // Konstruktor
    Paczka();

    // Gettery i settery
      // Gettery i settery
    unsigned int getId() const { return id; }
    void setId(unsigned int id) { this->id = id; updateModificationTime(); }

    string getTelefon() const { return telefon; }
    void setTelefon(const string& telefon) { this->telefon = telefon; updateModificationTime(); }

    string getKodOdbioru() const { return kodOdbioru; }
    void setKodOdbioru(const string& kodOdbioru) { this->kodOdbioru = kodOdbioru; updateModificationTime(); }

    string getNumerPaczkomatu() const { return numerPaczkomatu; }
    void setNumerPaczkomatu(const string& numerPaczkomatu) { this->numerPaczkomatu = numerPaczkomatu; updateModificationTime(); }

    unsigned int getUId() const { return u_id; }
    void setUId(unsigned int u_id) { this->u_id = u_id; updateModificationTime(); }

    // Ustawienie gabarytu
    void setGabaryt(Gabaryt* g) { gabaryt = g; updateModificationTime(); }

    Status getStatus() const { return status; }
    void setStatus(Status status) { this->status = status; updateModificationTime(); }

    // Nowa metoda, która zwraca czas ostatniej modyfikacji
    string getLastModified() const;
    time_t getLastModifiedTime() const { return lastModified; }
    // Wyœwietlenie informacji o paczce
    void wyswietlInfo() const;
    //nadawanie


    // Przeci¹¿enie operatorów
    friend istream& operator>>(istream& in, Paczka& obj);
    friend ostream& operator<<(ostream& os, const Paczka& paczka);

    // Destruktor
    ~Paczka();
};

#endif  // PACZKA_H
