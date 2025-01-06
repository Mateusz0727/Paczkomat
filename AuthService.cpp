#include "AuthService.h"
#include <iostream>
#include "Extensions.h"
#include "History.h"

using namespace std;

bool AuthService::login(const string& email, const string& password) {
    if (loggedInUser != nullptr) {
        cout << "Error: A user is already logged in." << endl;
        logHandler.log("Login attempt failed: A user is already logged in.");
        return false;
    }

    auto users = customerTable.getAll(); // Pobierz wszystkich użytkowników
    for (auto& user : users) {
        if (user.getEmail() == email && user.getPassword() == password) {
            loggedInUser = new Customer(user); // Kopia obiektu
            system("cls");
            cout << "Login successful. Welcome, " << loggedInUser->getFirstname() << "!" << endl;
            logHandler.log("Login successful. Email: " + email + ", User: " + loggedInUser->getFirstname());
            return true;
        }
    }
    cout << "Invalid email or password." << endl;
    logHandler.log("Login attempt failed: Invalid email or password. Email: " + email);

    return false;
}
// Funkcja rejestracji użytkownika
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
            logHandler.log("Registration failed: An account with this email already exists. Email: " + email);
            return false;
        }
    }

    cout << "Enter your password: ";
    hideText(password);
    cout << "Confirm your password: ";
    hideText(confirmPassword);

    if (password != confirmPassword) {
        cout << "Error: Passwords do not match." << endl;
        logHandler.log("Registration failed: Passwords do not match. Email: " + email); 
        return false;
    }

    unsigned int newId = 1;
    if (!users.empty()) {
        newId = users.back().getId() + 1;
    }

    Customer newUser(newId, firstname, lastname, email, password);
    customerTable.add(newUser); // Dodanie użytkownika do tabeli

    // Tworzenie pliku użytkownika w folderze `users_info`
    History userHistory(to_string(newId));
    userHistory.addEntry("Account created for user with ID: " + to_string(newId));
    userHistory.addEntry("Name: " + firstname + " " + lastname);
    userHistory.addEntry("Email: " + email);

    // Wyświetlanie informacji o nowym użytkowniku na ekranie
    cout << "\n=== New Account Details ===\n";
    cout << firstname << " " << lastname << endl;  // Imię i nazwisko
    cout << email << endl;                         // E-mail
    cout << "ID: " << newId << endl;               // ID użytkownika
    cout << "Account info saved in: users_info/" << newId << "_info.txt\n";
    cout << "================================\n";

    cout << "Registration successful. You can now log in." << endl;
    logHandler.log("Registration successful. New account created. Email: " + email);

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

// Sprawdzenie, czy użytkownik jest zalogowany
bool AuthService::isLoggedIn() const {
    return loggedInUser != nullptr;
}

// Pobranie aktualnie zalogowanego użytkownika
const Customer* AuthService::getLoggedInUser() const {
    return loggedInUser;
}
