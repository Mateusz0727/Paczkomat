#include "extensions.h"
#include <ctime>
#include <cstdio>
#include "EnumStatus.h"
using namespace std;
void hideText(string& text) {
    char ch;

    while ((ch = _getch()) != '\r') {  
        if (ch == '\b') {  
            if (!text.empty()) {
                text.pop_back();
                cout << "\b \b";  
            }
        }
        else {
            text.push_back(ch);
            cout << "*";  
        }
    }
    cout << endl;
}
string generateRandomDigits() {
    string digits;
    srand(static_cast<unsigned int>(time(nullptr))); 
    for (int i = 0; i < 6; ++i) {
        digits += to_string(rand() % 10); 
    }
    return digits;
}
bool isModifiedMoreThanFiveMinutesAgo(const time_t& lastModified) {

    time_t currentTime = time(nullptr);

    double secondsDifference = difftime(currentTime, lastModified);

    return secondsDifference > 300;
}

string statusToString(const Status& status) {
    switch (status) {
    case nadana:
        return "nadana";
    case doOdebrania:
        return "do odebrania";
    case odebrana:
        return "odebrana";
    default:
        return "nieznany status";
    }
}