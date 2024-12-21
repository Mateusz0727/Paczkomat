#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
class Customer {
public:
    int id;
    string firstname;  
    string surname;    

    friend istream& operator>>(istream& in, Customer& obj) {
        in >> obj.id >> obj.firstname >> obj.surname;  
        return in;
    }
};

#endif CUSTOMER_H