#include "Table.h"
#include <fstream>
#include <typeinfo>
#include "Handlers.h"
#include "Customer.h"
#include "Paczka.h"
#include "PackageLocker.h"

static LogHandler logHandler;
// Lub, jeœli wolisz, mo¿esz u¿yæ swojego globalnego/pojedynczego loggera.

// ----------------------- Definicje metod szablonu -----------------------

template <typename T>
Table<T>::Table()
    : _fileName(std::string(typeid(T).name()) + ".txt")
{
    std::ifstream file(_fileName);
    if (!file) {
        std::ofstream createFile(_fileName);
        if (createFile) {
            logHandler.log("File \"" + _fileName + "\" created successfully");
        }
        else {
            logHandler.log("Failed to create file \"" + _fileName + "\"");
        }
    }
    else {
        logHandler.log("File \"" + _fileName + "\" already exists.");
    }
}

template <typename T>
void Table<T>::add(T& entity)
{
    auto records = getAll();

    unsigned int maxId = 0;
    for (const auto& record : records) {
        if (record.getId() > maxId) {
            maxId = record.getId();
        }
    }
    // Ustawiamy nowy ID – modyfikujemy przekazany obiekt!
    entity.setId(maxId + 1);

    std::ofstream outFile(_fileName, std::ios::app);
    if (!outFile.is_open()) {
        logHandler.log("Error: Unable to open file for writing: " + _fileName);
        return;
    }

    outFile << entity << std::endl;
    outFile.close();

    logHandler.log("Added entity with ID " + std::to_string(entity.getId()) +
        " to table: " + _fileName);
}

template <typename T>
std::vector<T> Table<T>::getAll()
{
    std::ifstream inFile(_fileName);
    if (!inFile.is_open()) {
        logHandler.log("Error: Unable to open file for reading: " + _fileName);
    }

    std::vector<T> entities;
    T entity;
    while (inFile >> entity) {
        entities.push_back(entity);
    }

    inFile.close();
    return entities;
}

template <typename T>
T Table<T>::getById(unsigned int id)
{
    auto records = getAll();
    for (auto& record : records) {
        if (record.getId() == id) {
            return record;
        }
    }
    // Jeœli nie znaleziono, zwracamy "pusty" obiekt T:
    return T();
}

template <typename T>
void Table<T>::update(const T& updatedEntity)
{
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
        logHandler.log("Error: Record with ID " + std::to_string(id) + " not found.");
        std::cout << "Error: Record with ID " << id << " not found." << std::endl;
        return;
    }

    std::ofstream outFile(_fileName, std::ios::trunc);
    if (!outFile.is_open()) {
        logHandler.log("Error: Unable to open file for writing: " + _fileName);
        std::cout << "Error: Unable to open file for writing: " << _fileName << std::endl;
        return;
    }

    for (const auto& record : records) {
        outFile << record << std::endl;
    }
    outFile.close();

    logHandler.log("Updated record with ID " + std::to_string(id) +
        " in table: " + _fileName);
}

// --------------------- Jawne instancjonowanie szablonu --------------------
// Dziêki temu linker wygeneruje kod dla nastêpuj¹cych typów:
template class Table<Customer>;
template class Table<Paczka>;
template class Table<PackageLocker>;