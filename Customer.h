#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;
class Customer {
private :
    unsigned int id;
    string firstname;
    string surname;
    string email;
    string password;
    bool isAdmin;
public:
    
    Customer(int _id, const string& _firstname, const string& _surname,
        const string& _email, const string& _password, bool _isAdmin = false)
        : id(_id), firstname(_firstname), surname(_surname),
        email(_email), password(_password), isAdmin(_isAdmin) {}

    Customer() : id(0), firstname(""), surname(""), email(""), password(""), isAdmin(false) {}

    unsigned int getId() const { return id; }
    string getFirstname() const { return firstname; }
    string getSurname() const { return surname; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    bool getIsAdmin() const { return isAdmin; }

    void setId(unsigned int _id) { id = _id; }
    void setFirstname(const string& _firstname) { firstname = _firstname; }
    void setSurname(const string& _surname) { surname = _surname; }
    void setEmail(const string& _email) { email = _email; }
    void setPassword(const string& _password) { password = _password; }
    void setIsAdmin(bool _isAdmin) { isAdmin = _isAdmin; }


    friend istream& operator>>(istream& in, Customer& obj);
    friend ostream& operator<<(ostream& os, const Customer& customer);
    void displayMenu() const;
};

#endif CUSTOMER_H