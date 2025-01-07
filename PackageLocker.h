#ifndef PACKAGELOCKER_H
#define PACKAGELOCKER_H

#include<iostream>
#include "Paczka.h"

class PackageLocker
{
private:
	 int id;
	 int smallSlots;
	 int mediumSlots;
	 int largeSlots;
	 int MAXsmallSlots;
	 int MAXmediumSlots;
	 int MAXlargeSlots;
public:
	PackageLocker(int id, int smallSlots, int mediumSlots, int largeSlots)
		: id(id),smallSlots(smallSlots),mediumSlots(mediumSlots),largeSlots(largeSlots),MAXsmallSlots(smallSlots),MAXmediumSlots(mediumSlots),MAXlargeSlots(largeSlots)
	{
	}

	// Konstruktor domyœlny
	PackageLocker()
		: id(0), smallSlots(0), mediumSlots(0), largeSlots(0),MAXsmallSlots(0), MAXmediumSlots(0), MAXlargeSlots(0)
	{
	}
	bool canFitPackage(const Gabaryt& gabaryt) const;

	

	unsigned int getId() const { return id; }

	void setId(unsigned int _id) { id = _id; }

	int getSmallSlots() const { return smallSlots; }

	void setSmallSlots(int _smallSlots) { smallSlots = _smallSlots; }

	int getMediumSlots() const { return mediumSlots; }

	void setMediumSlots(int _mediumSlots) { mediumSlots = _mediumSlots; }

	int getLargeSlots() const { return largeSlots; }

	void setLargeSlots(int _largeSlots) { largeSlots = _largeSlots; }

	friend istream& operator>>(istream& in, PackageLocker& obj);

	friend ostream& operator<<(ostream& os, const PackageLocker& customer);

	

};


#endif