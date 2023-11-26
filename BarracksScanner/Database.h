#pragma once
#include "sqlite3.h"
#include <iostream>
#include <vector>

class Database {

private:
	sqlite3* db;
	char* errorMsg;
	static int callback(void *, int, char**, char**);

public:
	Database(std::string aQuery = "SELECT * FROM logs ORDER BY date DESC LIMIT 10",
		std::string aPath = "barracks.db");
	~Database();
	std::string query;
	std::vector<std::vector<std::string>> result;

	void executeQuery();
};

