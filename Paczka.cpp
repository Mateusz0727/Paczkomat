#include <iostream>
#include "Paczka.h"
using namespace std;

istream& operator>>(istream& in, Paczka& obj) {
    in >> obj.id >> obj.telefon >> obj.kodOdbioru >> obj.u_id;
    return in;
}
ofstream& operator<<(ofstream& os, const Paczka& paczka) {
    // Zapisujemy dane oddzielone spacjami
    os << paczka.id << " " << paczka.telefon << " " << paczka.kodOdbioru << " " << paczka.u_id << endl;
    return os;
}