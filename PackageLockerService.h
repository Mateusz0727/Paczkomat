#ifndef PACKAGELCOKER_SERVICE_H
#define PACKAGELCOKER_SERVICE_H
#include "PackageLocker.h"
#include "Database.h"
class PackageLockerService
{
private:
	Table<PackageLocker>& lockerTable;
public:
	explicit PackageLockerService(Database& db) :lockerTable(db.getTable<PackageLocker>()) {};
	void reserveSlot(const Gabaryt& gabaryt);

	bool canFitPackage(const Gabaryt& gabaryt) const;


};


#endif