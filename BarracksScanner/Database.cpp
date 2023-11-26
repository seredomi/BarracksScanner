#include "pch.h"
#include "Database.h"
#include <sstream>

using namespace std;

Database::Database(string dbPath, string aQuery) :
	db(nullptr), errorMsg(nullptr), query(aQuery) {

	int rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc) {
		cerr << "can't open database: " << sqlite3_errmsg(db) << '\n';
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
		cerr << "database not opened\n";
		return;
	}

	errorMsg = nullptr;
	int rc = sqlite3_exec(db, query.c_str(), callback, &result, &errorMsg);

	if (rc != SQLITE_OK) {
		cerr << "sql error: " << errorMsg << '\n';
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
