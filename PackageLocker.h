#ifndef PACKAGELOCKER_H
#define PACKAGELOCKER_H

#include<iostream>
#include "Paczka.h"

class PackageLocker
{
private:
	int smallSlots;
	int mediumSlots;
	int largeSlots;
public:
	PackageLocker(int smallSlots=0, int mediumSlots=7, int largeSlots=5)
		: smallSlots(smallSlots), mediumSlots(mediumSlots), largeSlots(largeSlots)
	{
	};
	~PackageLocker();
	bool canFitPackage(const Gabaryt& gabaryt) const;
	void reserveSlot(const Gabaryt& gabaryt);

	

	

};


#endif