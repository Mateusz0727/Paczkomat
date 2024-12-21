#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"
#include "Customer.h"
#include "Database.h"
using namespace std;

int main()
{
	Database db;
	vector<Customer> d= db._customer.getAll();
	
	
	for (const Customer record  : d)
		cout << record.id<<record.firstname << endl;
	int a;
	cin >> a;
}

