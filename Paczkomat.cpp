#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"
#include "Customer.h"
#include "Database.h"
#include "AuthService.h"
#include "Extensions.h"

using namespace std;

Database db;
AuthService _authService(db);

int main() {
    
    for (;;) {
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
                    user->displayMenu(); 
                }
                else {
                    cerr << "No user is logged in." << endl;
                    break;
                }

                if (!(cin >> choice)) {  // Sprawdzenie, czy użytkownik wpisał liczbę
                    choice = 9999;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;  
                }

                switch (choice) {
                case 1:
                    //TODO:zamienić to na funkcje np. klasy menu aby kod był bardziej czytelny
                    cout << "Profile:\n";
                    cout << *user << endl;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    break;
                
                case 2:
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
    }
    return 0;
}
