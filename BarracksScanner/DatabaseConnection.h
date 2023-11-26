#pragma once
#include "sqlite3.h"
#include <iostream>
#include <vector>

class DatabaseConnection {

private:
	sqlite3* db;
	char* errorMsg;
	std::string select;
	std::string table;
	std::string where;
	std::vector<std::vector<std::string>> result;
	std::string assembleQuery() const;
	int callback(std::vector<std::vector<std::string>>*, int, char**, char**);

public:
	DatabaseConnection(std::string aPath = "barracks.db", std::string aSelect = "*",
					   std::string aTable = "logs", std::string aWhere = "ORDER BY date DESC LIMIT 10");
	~DatabaseConnection();

	void executeQuery(std::string);
};

