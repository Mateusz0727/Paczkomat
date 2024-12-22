#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;
class Customer {
public:
    int id;
    string firstname;  
    string surname;    
    string email;
    string password;
    bool isAdmin;
    Customer(int _id, const string& _firstname, const string& _surname,
        const string& _email, const string& _password, bool _isAdmin = false)
        : id(_id), firstname(_firstname), surname(_surname),
        email(_email), password(_password), isAdmin(_isAdmin) {}

    Customer() : id(0), firstname(""), surname(""), email(""), password(""), isAdmin(false) {}


    friend istream& operator>>(istream& in, Customer& obj);
    friend ostream& operator<<(ostream& os, const Customer& customer);
    void displayMenu() const;
};

#endif CUSTOMER_H