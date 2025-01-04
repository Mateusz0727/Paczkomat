#include "AuthService.h"
#include <iostream>
using namespace std;

bool AuthService::login(const string& email, const string& password) {
    if (loggedInUser != nullptr) {
        cout << "Error: A user is already logged in." << endl;
        return false;
    }

    auto users = customerTable.getAll(); // Pobierz wszystkich u¿ytkowników
    for (auto& user : users) {
        if (user.getEmail() == email && user.getPassword() == password) {
            loggedInUser = new Customer(user); // Kopia obiektu
            system("cls");
            cout << "Login successful. Welcome, " << loggedInUser->getFirstname() << "!" << endl;
            return true;
        }
    }
    cout << "Invalid email or password." << endl;
    return false;
}
// Funkcja rejestracji u¿ytkownika
bool AuthService::registration() {
    string firstname, lastname, email, password, confirmPassword;

    cout << "Enter your first name: ";
    cin >> firstname;
    cout << "Enter your last name: ";
    cin >> lastname;
    cout << "Enter your email: ";
    cin >> email;

    auto users = customerTable.getAll();
    for (const auto& user : users) {
        if (user.getEmail() == email) {
            cout << "Error: An account with this email already exists." << endl;
            return false;
        }
    }

    cout << "Enter your password: ";
    cin >> password;
    cout << "Confirm your password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Error: Passwords do not match." << endl;
        return false;
    }


    unsigned int newId = 1; 
    if (!users.empty()) {
        newId = users.back().getId() + 1; 
    }

    Customer newUser(newId, firstname, lastname, email, password);
    customerTable.add(newUser); 

    cout << "Registration successful. You can now log in." << endl;
    return true;
}

// Funkcja wylogowania
void AuthService::logout() {
    if (loggedInUser == nullptr) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    cout << "User " << loggedInUser->getFirstname() << " has been logged out." << endl;
    loggedInUser = nullptr;
}

// Sprawdzenie, czy u¿ytkownik jest zalogowany
bool AuthService::isLoggedIn() const {
    return loggedInUser != nullptr;
}

// Pobranie aktualnie zalogowanego u¿ytkownika
const Customer* AuthService::getLoggedInUser() const {
    return loggedInUser;
}
