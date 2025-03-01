﻿#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"
#include "Customer.h"
#include "Database.h"
#include "AuthService.h"
#include "Extensions.h"
#include "Paczka.h"
#include "History.h"
#include "PackageService.h"
#include "AdminService.h"
using namespace std;

Database db;
AuthService _authService(db);
PackageService _packageService(db);
AdminService _adminService(db);
const Customer* user;
int main() {
    for (;;) {
        system("cls");
        cout << "Welcome to the System!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";

        int mainChoice;
        if (!(cin >> mainChoice)) { // Sprawdzenie, czy użytkownik wpisał liczbę
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mainChoice = -1; // Nieprawidłowy wybór
        }

        switch (mainChoice) {
        case 1: { // Logowanie
            system("cls");
            string email, password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            hideText(password);
            if (_authService.login(email, password)) {
                int choice;
                do {
                    const Customer* user = _authService.getLoggedInUser();
                    if (user) {
                        ::user = user;
                        user->displayMenu();
                    }
                    else {
                        cout << "No user is logged in." << endl;
                        break;
                    }

                    if (!(cin >> choice)) { // Sprawdzenie, czy użytkownik wpisał liczbę
                        choice = 9999;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    switch (choice) {
                    case 1: // View Profile
                        if (user) {
                            // Wyświetlanie informacji o koncie
                            cout << "\n=== Account Information ===\n";

                            // Wyświetlanie szczegółów użytkownika
                            cout << "User ID: " << user->getId() << endl;
                            cout << "Name: " << user->getFirstname() << " " << user->getSurname() << endl;
                            cout << "Email: " << user->getEmail() << endl;
                            cout << "User/Admin: " << (user->getIsAdmin() ? "Admin" : "User") << endl;

                            // Wyświetlanie historii paczek (jeśli istnieje)
                            History history(to_string(user->getId())); // Historia na podstawie ID
                            auto entries = history.getHistory();

                            if (entries.size() > 3) {
                                cout << "\n=== Package History ===\n";
                                for (size_t i = 3; i < entries.size(); ++i) { // Historia zaczyna się od czwartej linii
                                    cout << entries[i] << endl;
                                }
                            }

                            cout << "======================\n";

                            cin.ignore();
                            cin.get();
                            system("cls");
                        }
                        break;
                    case 2:
                        _packageService.nadaj(*::user);
                        break;
                    case 3:

                        
                        _packageService.pickUp(*::user);
                        break;
                    case 4:
                        if (user->getIsAdmin()) {
                            cout << "All Users:\n";
                            for (const auto& customer : db.getTable<Customer>().getAll()) {
                                cout << customer << endl;
                            }
                        }
                        else {
                            cout << "Invalid option.\n";
                        }
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    case 5:
                        if (user->getIsAdmin()) {
                            _adminService.generateRaport();
                        }
                        else {
                            cout << "Invalid option.\n";
                        }
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;

                    case 0:
                        _authService.logout();
                        break;

                    default:
                        cout << "Invalid choice. Please try again.\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                    }
                } while (_authService.isLoggedIn() && choice != 0);
            }
            else {
                cout << "Login failed. Please try again." << endl;
                cin.ignore();
                cin.get();
                system("cls");
            }
            break;
        }
        case 2: { // Rejestracja
            system("cls");
            if (_authService.registration()) {
                cout << "Registration successful! You can now log in." << endl;
            }
            else {
                cout << "Registration failed. Please try again." << endl;
            }
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 0: // Wyjście
            cout << "Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            cin.ignore();
            cin.get();
            system("cls");
        }
    }

    return 0;
}

