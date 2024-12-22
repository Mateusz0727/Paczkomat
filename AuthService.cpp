#include "AuthService.h"
#include <iostream>
using namespace std;
bool AuthService::login(const string& email, const string& password) {
    if (loggedInUser != nullptr) {
        cout << "Error: A user is already logged in." << endl;
        return false;
    }

    auto users = customerTable.getAll(); // Pobierz wszystkich użytkowników
    for (auto& user : users) {
        if (user.email == email && user.password == password) {
            loggedInUser = new Customer(user); // Kopia obiektu
            system("cls");
            cout << "Login successful. Welcome, " << loggedInUser->firstname << "!" << endl;
            return true;
        }
    }
    cerr << "Invalid email or password." << endl;
    return false;
}


// Funkcja wylogowania
void AuthService::logout() {
    if (loggedInUser == nullptr) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    cout << "User " << loggedInUser->firstname << " has been logged out." << endl;
    loggedInUser = nullptr;
}

// Sprawdzenie, czy użytkownik jest zalogowany
bool AuthService::isLoggedIn() const {
    return loggedInUser != nullptr;
}

// Pobranie aktualnie zalogowanego użytkownika
const Customer* AuthService::getLoggedInUser() const {
    return loggedInUser;
}
