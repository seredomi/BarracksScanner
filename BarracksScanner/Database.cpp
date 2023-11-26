#include "pch.h"
#include "Database.h"
#include <sstream>

using namespace std;

Database::Database(string aQuery, string dbPath) :
	db(nullptr), errorMsg(nullptr), query(aQuery) {

	int rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc) {
		result[0][0] = "can't open database: " + string(sqlite3_errmsg(db));
		sqlite3_close(db);
		db = nullptr;
	}
}
Database::~Database() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

void Database::executeQuery() {

	if (!db) {
		result[0][0] = "database not opened";
		return;
	}

	errorMsg = nullptr;
	int rc = sqlite3_exec(db, query.c_str(), callback, &result, &errorMsg);

	if (rc != SQLITE_OK) {
		result[0][0] = "sql error : " + string(errorMsg);
		sqlite3_free(errorMsg);
	}
}

int Database::callback(void* ptr, int numCols, char** colVals, char** colNames) {
	auto* table = static_cast<vector<vector<string>> *>(ptr);
	vector<string> row;

	for (int i = 0; i < numCols; ++i) {
		row.emplace_back(colVals[i] ? colVals[i] : "NULL");
	}

	table->emplace_back(row);
	return 0;
}
