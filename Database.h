#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <functional>
#include "Table.h"
#include "Customer.h"
class Database {
private:
    vector<string> tables;
    
public:
    Table<Customer> _customer;

    template <typename T>
    Table<T>& getTable();

};

#endif 