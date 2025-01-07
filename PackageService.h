#ifndef PACKAGE_SERVICE_H
#define PACKAGE_SERVICE_H

#include "Customer.h"
#include "Database.h"
#include "Paczka.h"
#include "PackageLocker.h"
#include "PackageLockerService.h"

class PackageService {
private:
  
    Table<Paczka>& paczkaTable; // Referencja do tabeli paczek
    Table<PackageLocker>& lockerTable;
    PackageLockerService lockerService;

public:
    explicit PackageService(Database& db) : paczkaTable(db.getTable<Paczka>()), lockerTable(db.getTable<PackageLocker>()), lockerService(db){}

    void nadaj(Customer user); // Deklaracja funkcji nadaj

    void pickUp();
};

#endif // PACKAGE_SERVICE_H
