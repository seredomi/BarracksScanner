#include "pch.h"
#include "DatabaseConnection.h"
#include <sstream>

using namespace std;

DatabaseConnection::DatabaseConnection(string dbPath, string aSelect, string aTable, string aWhere) :
	db(nullptr), errorMsg(nullptr), select(aSelect), table(aTable), where(aWhere) {

	int rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc) {
		cerr << "can't open database: " << sqlite3_errmsg(db) << '\n';
		sqlite3_close(db);
		db = nullptr;
	}
}
DatabaseConnection::~DatabaseConnection() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

std::string DatabaseConnection::assembleQuery() const {
	return "SELECT " + select + " FROM " + table + " " + where + ";";
}

void DatabaseConnection::executeQuery(string query) {

	if (!db) {
		cerr << "database not opened\n";
		return;
	}

	errorMsg = nullptr;

	int rc = sqlite3_exec(db, query.c_str(), callback(), &result, &errorMsg);
}

int DatabaseConnection::callback(&result, )
