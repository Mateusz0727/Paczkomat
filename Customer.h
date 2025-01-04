#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include "Paczka.h"  // Zak³adam, ¿e masz plik nag³ówkowy "Paczka.h"
using namespace std;

class Customer {
private:
    unsigned int id;
    string firstname;
    string surname;
    string email;
    string password;
    bool isAdmin;

public:
    // Konstruktor
    Customer(int _id, const string& _firstname, const string& _surname,
        const string& _email, const string& _password, bool _isAdmin = false)
        : id(_id), firstname(_firstname), surname(_surname),
        email(_email), password(_password), isAdmin(_isAdmin) {
    }

    // Konstruktor domyœlny
    Customer() : id(0), firstname(""), surname(""), email(""), password(""), isAdmin(false) {}

    // Gettery
    unsigned int getId() const { return id; }
    string getFirstname() const { return firstname; }
    string getSurname() const { return surname; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    bool getIsAdmin() const { return isAdmin; }

    // Settery
    void setId(unsigned int _id) { id = _id; }
    void setFirstname(const string& _firstname) { firstname = _firstname; }
    void setSurname(const string& _surname) { surname = _surname; }
    void setEmail(const string& _email) { email = _email; }
    void setPassword(const string& _password) { password = _password; }
    void setIsAdmin(bool _isAdmin) { isAdmin = _isAdmin; }

    // Operator wejœcia
    friend istream& operator>>(istream& in, Customer& obj);

    // Operator wyjœcia
    friend ostream& operator<<(ostream& os, const Customer& customer);

    // Wyœwietlanie menu
    void displayMenu() const;

   
};

#endif // CUSTOMER_H
