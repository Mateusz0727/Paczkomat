#include "Table.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Customer.h"
#include "Handlers.h"
using namespace std;
LogHandler logHandler;
//Constructior: Create table file if doesn't exist
 template <typename T>
 Table<T>::Table() : _fileName(string(typeid(T).name()) + ".txt") { 
     ifstream file(_fileName);
     if (!file) {
         ofstream createFile(_fileName);
         if (createFile) {
             logHandler.log("File " +'"' + _fileName + '"' + " created successfully");
         
         }
         else {
             logHandler.log("Failed to create file " + '"' + _fileName + '"');
         }
     }
     else {
         logHandler.log("File " + '"' + _fileName + '"' + " already exists.");
     }
 }

template <typename T>
vector<T> Table<T>::getAll() {
    ifstream inFile(_fileName);
    if (!inFile.is_open()) {
        // Obs³uga b³êdu
    }

    vector<T> entities;
    T entity;
    string line;
    while (inFile>>entity) {
        entities.push_back(entity);
    }

    inFile.close();
    return entities;
}


template class Table<Customer>;
