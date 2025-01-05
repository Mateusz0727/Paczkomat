#ifndef PACKAGE_SERVICE_H
#define PACKAGE_SERVICE_H

#include <string>
#include "Customer.h"
#include "Database.h"

class PackageService {
private:
    Table<Paczka>& paczkaTable; // Referencja do tabeli u¿ytkowników

public:
    explicit PackageService(Database& db) : paczkaTable(db.getTable<Paczka>()) {}

    void nadaj(Customer user);
};

#endif // PACKAGE_SERVICE_H