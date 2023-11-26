#pragma once
#include "sqlite3.h"
#include <iostream>
#include <vector>

class Database {

private:
	sqlite3* db;
	char* errorMsg;
	std::string query;
	std::vector<std::vector<std::string>> result;
	static int callback(void *, int, char**, char**);

public:
	Database(std::string aPath = "barracks.db",
		std::string aQuery = "SELECT * FROM logs ORDER BY date DESC LIMIT 10");
	~Database();

	void executeQuery();
};

