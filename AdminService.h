#ifndef ADMIN_SERVICE_H
#define ADMIN_SERVICE_H

#include <string>
#include <iostream>
#include "Customer.h"
#include "Database.h"
#include "Handlers.h"
#include "Extensions.h"
class AdminService {
private:

    Table<Customer>& customerTable;
    Table<Paczka>& paczkaTable;   
    const LogHandler logHandler;
public:
    explicit AdminService(Database& db) : customerTable(db.getTable<Customer>()),paczkaTable(db.getTable<Paczka>()) {}
    void generateRaport();
    
};

#endif // ADMIN_SERVICE_H
