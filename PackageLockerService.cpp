#include <string>
#include "PackageLockerService.h"
#include "Paczka.h"

void PackageLockerService::reserveSlot(const Gabaryt& gabaryt) {
    string size = gabaryt.getSize();
    PackageLocker locker= lockerTable.getById(1);
    if (size == "S") {
        int s = locker.getSmallSlots();
        
        locker.setSmallSlots(s - 1);
        lockerTable.update(locker);
       
    }
    else if (size == "M") {
        int m = locker.getMediumSlots();
       
        locker.setMediumSlots(m - 1);
        lockerTable.update(locker);
       
    }
    else if (size == "L") {
        int l = locker.getLargeSlots();
       
        locker.setLargeSlots(l - 1);
        lockerTable.update(locker);
       
    }
}
bool PackageLockerService::canFitPackage(const Gabaryt& gabaryt) const
{
    PackageLocker locker = lockerTable.getById(1);
    string size = gabaryt.getSize();
    if (size == "S")
    {
        return locker.getSmallSlots() > 0;

    }
    else if (size == "M")
    {
        return locker.getMediumSlots() > 0;
    }
    else if (size == "L")
    {
        return locker.getLargeSlots() > 0;
    }
    return false;

}