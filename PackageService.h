#ifndef PACKAGE_SERVICE_H
#define PACKAGE_SERVICE_H

#include "Customer.h"
#include "Database.h"
#include "Paczka.h"
#include "PackageLocker.h"

class PackageService {
private:
    PackageLocker* locker = new PackageLocker();
    Table<Paczka>& paczkaTable; // Referencja do tabeli paczek

public:
    explicit PackageService(Database& db) : paczkaTable(db.getTable<Paczka>()) {}

    void nadaj(Customer user); // Deklaracja funkcji nadaj

    void pickUp();
};

#endif // PACKAGE_SERVICE_H
