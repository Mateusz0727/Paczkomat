#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <conio.h>  
#include <cstdlib>
#include <time.h>
#include "EnumStatus.h"
using namespace std;
void hideText(string& text);

string generateRandomDigits();

bool isModifiedMoreThanFiveMinutesAgo(const time_t& lastModified);

string statusToString(const Status& status);
#endif // EXTENSIONS_H
