#include "Database.h"
#include <iostream>
#include "Table.h"
using namespace std;

template <>
Table<Customer>& Database::getTable<Customer>() {
    return _customer;
}
template <>
Table<Paczka>& Database::getTable<Paczka>() {
    return _paczka;
}
template <>
Table<PackageLocker>& Database::getTable<PackageLocker>() {
    return _packageLocker;
}