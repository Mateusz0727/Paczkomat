#include "Table.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Customer.h"
#include "Paczka.h"
#include "Handlers.h"
using namespace std;
LogHandler logHandler;

template class Table<Customer>;
template class Table<Paczka>;

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

 //get all entities
template <typename T>
vector<T> Table<T>::getAll() {
    ifstream inFile(_fileName);
    if (!inFile.is_open()) {
        logHandler.log("Error: Unable to open file for writing: " + _fileName);
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
//Get entity by Id
template <typename T>
 T Table<T>::getById(unsigned int id) {
    auto records = getAll();
    for (  auto& record : records) {         
        if (record.getId() == id) {
            return  record;
        }
    }
    
}

 //Add entity to table
 template <typename T>
 void Table<T>::add(T entity) {
     auto records = getAll();

     unsigned int maxId = 0;
     for (const auto& record : records) {
         if (record.getId() > maxId) {
             maxId = record.getId();
         }
     }

     entity.setId(  maxId + 1);

     ofstream outFile(_fileName, ios::app); 
     if (!outFile.is_open()) {
         logHandler.log("Error: Unable to open file for writing: " + _fileName);
         return;
     }

     outFile << entity << endl; 
     outFile.close();

     logHandler.log("Added entity with ID " + to_string(entity.getId()) + " to table: " + _fileName);
 }
 template <typename T>
 void Table<T>::update( const T& updatedEntity) {
     auto records = getAll();
     bool found = false;
     unsigned int id = updatedEntity.getId();
     for (auto& record : records) {
         if (record.getId() == id) {
             record = updatedEntity; 
             found = true;
             break;
         }
     }

     if (!found) {
         logHandler.log("Error: Record with ID " + to_string(id) + " not found.");
         cout << "Error: Record with ID " << id << " not found." << endl;
         return;
     }

     ofstream outFile(_fileName, ios::trunc); 
     if (!outFile.is_open()) {
         logHandler.log("Error: Unable to open file for writing: " + _fileName);
         cout << "Error: Unable to open file for writing: " << _fileName << endl;
         return;
     }

     for (const auto& record : records) {
         outFile << record << endl; 
     }

     outFile.close();
     logHandler.log("Updated record with ID " + to_string(id) + " in table: " + _fileName);
 }


