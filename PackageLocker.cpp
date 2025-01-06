#include <string>
#include "PackageLocker.h"
using namespace std;
bool PackageLocker::canFitPackage(const Gabaryt& gabaryt) const
{
    string size = gabaryt.getSize();
    if (size == "S")
    {
        return smallSlots > 0;
       
    }
    else if (size == "M")
    {
        return mediumSlots > 0;
    }
    else if (size == "L")
    {
        return largeSlots > 0;
    }
    return false;

}

void PackageLocker::reserveSlot(const Gabaryt& gabaryt) {
    string size = gabaryt.getSize();
    if (size == "S") {
        --smallSlots;
    }
    else if (size == "M") {
        --mediumSlots;
    }
    else if (size == "L") {
        --largeSlots;
    }
}
