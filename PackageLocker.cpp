#include <string>
#include "PackageLocker.h"
using namespace std;




istream& operator>>(istream& in, PackageLocker& obj)
{

    return in>>obj.id>>obj.MAXsmallSlots>>obj.MAXmediumSlots>>obj.MAXlargeSlots>>obj.smallSlots>>obj.mediumSlots>>obj.largeSlots;
}

ostream& operator<<(ostream& os, const PackageLocker& locker)
{
    return os << locker.id<<" " << locker.MAXsmallSlots << " " << locker.MAXmediumSlots << " " << locker.MAXlargeSlots << " " << locker.smallSlots << " " << locker.mediumSlots << " " << locker.largeSlots;

}
