#include "pch.h"
#include "Person.h"

using namespace std;
using namespace winrt;

Person::Person(winrt::hstring id, winrt::hstring rank, winrt::hstring last, winrt::hstring first, winrt::hstring room, winrt::hstring group) :
	id(id), rank(rank), last(last), first(first), room(room), group(group) {};

Person::Person(vector<string> dbResult) :
	id(to_hstring(dbResult[0])), rank(to_hstring(dbResult[1])), last(to_hstring(dbResult[2])),
	first(to_hstring(dbResult[3])), room(to_hstring(dbResult[4])), group(to_hstring(dbResult[5])) {};

void Person::SetPerson(winrt::hstring anId, winrt::hstring aRank, winrt::hstring aLast, winrt::hstring aFirst, winrt::hstring aRoom, winrt::hstring aGroup) {
	id = anId;
	rank = aRank;
	last = aLast;
	first = aFirst;
	room = aRoom;
	group = aGroup;
	name = rank + L" " + last + L", " + first;
}


bool Person::operator==(const Person& rhs) const {
	return id == rhs.id;
}

bool Person::operator!=(const Person& rhs) const {
	return !(*this == rhs);
}

bool Person::operator<=(const Person& rhs) const {
	return id <= rhs.id;
}

winrt::hstring Person::to_string() const {
	return id + L" " + rank + L" " + last + L" " + first + L" " + room + L" " + group;
}

winrt::hstring Person::print_name() const {
	return rank + L" " + last + L", " + first;
}

