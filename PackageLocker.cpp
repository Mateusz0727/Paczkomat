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