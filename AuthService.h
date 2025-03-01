#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>

#include "Customer.h"
#include "Database.h"
#include "Handlers.h"

class AuthService {
private:
 
    Table<Customer>& customerTable; // Referencja do tabeli użytkowników
    const Customer* loggedInUser;   // Wskaźnik do zalogowanego użytkownika (tylko do odczytu)
    const LogHandler logHandler;
public:
    explicit AuthService(Database& db) : customerTable(db.getTable<Customer>()), loggedInUser(nullptr) {}

    bool registration();
    bool login(const string& email, const string& password);

    void logout();

    bool isLoggedIn() const;

    const Customer* getLoggedInUser() const;
};

#endif // AUTH_SERVICE_H
