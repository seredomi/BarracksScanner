#pragma once
#include "pch.h"

class Person {

private:
	winrt::hstring id;
	winrt::hstring rank;
	winrt::hstring last;
	winrt::hstring first;
	winrt::hstring room;
	winrt::hstring group;

public:
	Person() = default;
	Person(winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring);

	void SetPerson(winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring);

	bool operator==(const Person&) const;
	bool operator!=(const Person&) const;
	bool operator<=(const Person&) const;

	winrt::hstring to_string() const;
};

