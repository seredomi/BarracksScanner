#include "pch.h"
#include "Person.h"

Person::Person(winrt::hstring id, winrt::hstring rank, winrt::hstring last, winrt::hstring first, winrt::hstring room, winrt::hstring group) :
	id(id), rank(rank), last(last), first(first), room(room), group(group) {};

void Person::SetPerson(winrt::hstring anId, winrt::hstring aRank, winrt::hstring aLast, winrt::hstring aFirst, winrt::hstring aRoom, winrt::hstring aGroup) {
	id = anId;
	rank = aRank;
	last = aLast;
	first = aFirst;
	room = aRoom;
	group = aGroup;
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

