#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <string>
using namespace std;
void hideText(string& text);
string generateRandomDigits();
bool isModifiedMoreThanFiveMinutesAgo(const time_t& lastModified);
#endif // EXTENSIONS_H
