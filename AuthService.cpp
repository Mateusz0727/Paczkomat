#include "AuthService.h"
#include <iostream>
#include "Extensions.h"
#include "History.h"

using namespace std;

// Funkcja logowania u¿ytkownika
bool AuthService::login(const string& email, const string& password) {
    if (loggedInUser != nullptr) {
        cout << "Error: A user is already logged in." << endl;
        logHandler.log("Login attempt failed: A user is already logged in.");
        return false;
    }

    auto users = customerTable.getAll(); // Pobierz wszystkich u¿ytkowników
    for (auto& user : users) {
        if (user.getEmail() == email && user.getPassword() == password) {
            // Zaloguj (zrób kopiê obiektu, aby 'loggedInUser' by³o w pamiêci dynamicznej)
            loggedInUser = new Customer(user);
            system("cls");
            cout << "Login successful. Welcome, "
                << loggedInUser->getFirstname() << "!" << endl;
            logHandler.log("Login successful. Email: " + email
                + ", User: " + loggedInUser->getFirstname());
            return true;
        }
    }
    // Jeœli pêtla siê zakoñczy bez znalezienia u¿ytkownika:
    cout << "Invalid email or password." << endl;
    logHandler.log("Login attempt failed: Invalid email or password. Email: " + email);
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

    // Sprawdzenie, czy taki email ju¿ istnieje
    auto users = customerTable.getAll();
    for (const auto& user : users) {
        if (user.getEmail() == email) {
            cout << "Error: An account with this email already exists." << endl;
            logHandler.log("Registration failed: An account with this email already exists. Email: " + email);
            return false;
        }
    }

    cout << "Enter your password: ";
    hideText(password);          // Ukryte wprowadzanie has³a
    cout << "Confirm your password: ";
    hideText(confirmPassword);

    if (password != confirmPassword) {
        cout << "Error: Passwords do not match." << endl;
        logHandler.log("Registration failed: Passwords do not match. Email: " + email);
        return false;
    }

    // Ustalenie ID
    unsigned int newId = 1;
    if (!users.empty()) {
        // Zwiêkszamy ID o 1 wzglêdem najwy¿szego
        newId = users.back().getId() + 1;
    }

    // Tworzymy obiekt Customer
    Customer newUser(newId, firstname, lastname, email, password);

    // Dodajemy u¿ytkownika do tabeli
    customerTable.add(newUser);

    // Tworzenie pliku u¿ytkownika w folderze users_info (historia)
    History userHistory(to_string(newId));
    userHistory.addEntry("Account created for user with ID: " + to_string(newId));
    userHistory.addEntry("Name: " + firstname + " " + lastname);
    userHistory.addEntry("Email: " + email);

    // Wyœwietlanie informacji o nowym u¿ytkowniku na ekranie
    cout << "\n=== New Account Details ===\n";
    cout << firstname << " " << lastname << endl;  // Imiê i nazwisko
    cout << email << endl;                         // E-mail
    cout << "ID: " << newId << endl;               // ID u¿ytkownika
    cout << "Account info saved in: users_info/" << newId << "_info.txt\n";
    cout << "================================\n";

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
    // Usuwamy obiekt z pamiêci (opcjonalnie, ale warto).
    delete loggedInUser;
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
