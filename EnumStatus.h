#ifndef ENUMSTATUS_H
#define ENUMSTATUS_H

#include <iostream>
using namespace std;

enum Status {
    nadana = 0,
    doOdebrania = 1,
    odebrana = 2,
};

inline istream& operator>>(istream& in, Status& status) {
    int value;
    if (in >> value && value >= 0 && value <= 2) { 
        status = static_cast<Status>(value);
    }
    else {
        in.setstate(ios::failbit);
    }
    return in;
}

inline ostream& operator<<(ostream& os, const Status& status) {
    os << static_cast<int>(status);
    return os;
}

#endif // ENUMSTATUS_H
