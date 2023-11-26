#pragma once
#include "sqlite3.h"
#include <iostream>
#include <vector>

class PersonQuery {

	sqlite3* db;

	void openDB();
	void closeDB();

};

