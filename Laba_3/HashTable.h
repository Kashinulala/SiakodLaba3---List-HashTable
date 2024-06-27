#pragma once
#include "List.h"

class hashTable {
	
private:

	list* arr;
	int N;

public:

	hashTable(int _N) {
		N = _N;
		arr = new list[N];
	}


};