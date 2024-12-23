#include "Database.h"
#include <iostream>
#include "Table.h"
using namespace std;

template <>
Table<Customer>& Database::getTable<Customer>() {
    return _customer;
}