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
    Table<Customer> _customer;
public:
   

    template <typename T>
    Table<T>& getTable();

};
//Aby miec dost�p do danych z plik�w trzeba doda� analogiczny obiekt do Table<Customer> _customer np. Table<Paczka> _paczka
// W Database.cpp doda� metod� getTable dla dodanej klasy
//W pliku Table.cpp Tak�e doda� analogiczny template do tego kt�ry istnieje ( na g�rze pliku)
//Aby program odczytywa� poprawnie wyniki trzeba do ka�dej klasy doda� przeciazenia operator�w << oraz >> analogiczne do tych kt�re s� w Customer
//jak nie dzia�a [nie tworzy si� plik txt (nie pokazuja si� odrazu w visualu trzeba je doda� do zasob�w )lub nie odczytuje danych] konaktowa� sie ze mn� ;)
#endif 