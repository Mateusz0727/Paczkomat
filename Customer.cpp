#include "Customer.h"
#include "Paczka.h"
#include <iostream>
using namespace std;

istream& operator>>(istream& in, Customer& obj) {
    in >> obj.id >> obj.firstname >> obj.surname >> obj.email >> obj.password >> obj.isAdmin;
    return in;
}

ostream& operator<<(ostream& os, const Customer& customer) {
    os << customer.id << " " << customer.firstname << " " << customer.surname << " "
        << customer.email << " " << customer.password << " " << (customer.isAdmin ? "Admin" : "User");
    return os;
}

// Wyœwietlanie menu dla u¿ytkownika
void Customer::displayMenu() const {
    cout << "\n=== Main Menu ===\n";
    cout << "1. View Profile\n";


    if (isAdmin) {
        cout << "\n--- Admin Functions ---\n";
        cout << "2. View All Users\n";
    }

    cout << "\n0. Logout\n";
    cout << "========================\n";
    cout << "Choose an option: ";
}

