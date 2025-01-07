#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <iostream>

template <typename T>
class Table {
private:
    std::string _fileName;

public:
    // Konstruktor
    explicit Table();

    // Dodawanie obiektu (przekazujemy przez referencjê!)
    void add(T& entity);

    // Pobiera wszystkie obiekty z "bazy" (z pliku)
    std::vector<T> getAll();

    // Pobiera obiekt po ID
    T getById(unsigned int id);

    // Aktualizuje obiekt w "bazie"
    void update(const T& updatedEntity);
};

#endif // TABLE_H
