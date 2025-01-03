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
//Aby miec dostêp do danych z plików trzeba dodaæ analogiczny obiekt do Table<Customer> _customer np. Table<Paczka> _paczka
// W Database.cpp dodaæ metodê getTable dla dodanej klasy
//W pliku Table.cpp Tak¿e dodaæ analogiczny template do tego który istnieje ( na górze pliku)
//Aby program odczytywa³ poprawnie wyniki trzeba do ka¿dej klasy dodaæ przeciazenia operatorów << oraz >> analogiczne do tych które s¹ w Customer
//jak nie dzia³a [nie tworzy siê plik txt (nie pokazuja siê odrazu w visualu trzeba je dodaæ do zasobów )lub nie odczytuje danych] konaktowaæ sie ze mn¹ ;)
#endif 