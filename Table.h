#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class Table {
private:
	string _fileName;
public:
	explicit Table();
	
	void add(T entity);

	vector<T> getAll();

	T getById(unsigned int id);

	void update( const T& updatedEntity);

};

#endif