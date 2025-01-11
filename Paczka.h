#ifndef PACZKA_H
#define PACZKA_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime> 
#include <vector>
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

    // Klasa wewnêtrzna Historia
    class Historia {
    public:
        time_t timestamp;
        Status status;

        Historia(time_t ts, Status st) : timestamp(ts), status(st) {}

        void wyswietl() const {
            char buffer[26];  // Bufor na sformatowany czas
            ctime_s(buffer, sizeof(buffer), &timestamp);
            cout << "Czas: " << buffer << endl;

        }
    };

    vector<Historia> historiaStatusow;  // Lista historii zmian statusu

public:
    // Konstruktor
    Paczka();

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

    Gabaryt* getGabaryt() const { return gabaryt; }
    void setGabaryt(Gabaryt* g) { gabaryt = g; updateModificationTime(); }

    Status getStatus() const { return status; }
    void setStatus(Status status) {
        this->status = status;
        updateModificationTime();
        historiaStatusow.emplace_back(time(nullptr), status);
    }

    string getLastModified() const;
    time_t getLastModifiedTime() const { return lastModified; }

    void wyswietlInfo() const;

    // Wyœwietlenie historii zmian statusu
    void wyswietlHistorie() const {
        for (const auto& h : historiaStatusow) {
            h.wyswietl();
        }
    }

    // Przeci¹¿enie operatorów
    friend istream& operator>>(istream& in, Paczka& obj);
    friend ostream& operator<<(ostream& os, const Paczka& paczka);

    // Destruktor
    ~Paczka();
};

#endif  // PACZKA_H
