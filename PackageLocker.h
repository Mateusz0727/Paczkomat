#include<iostream>
#include "Paczka.h"

class PackageLocker
{
public:
	PackageLocker(int smallSlots, int mediumSlots, int largeSlots)
		: smallSlots(smallSlots), mediumSlots(mediumSlots), largeSlots(largeSlots)
	{
	};
	~PackageLocker();
	bool canFitPackage(const Gabaryt& gabaryt) const;

private:
	int smallSlots;
	int mediumSlots;
	int largeSlots;
	

	

};


