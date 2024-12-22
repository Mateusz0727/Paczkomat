#include "extensions.h"
#include <iostream>
#include <conio.h>  
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
