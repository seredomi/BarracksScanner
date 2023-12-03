#pragma once
#include "pch.h"

class Person {

public:
	winrt::hstring id;
	winrt::hstring rank;
	winrt::hstring last;
	winrt::hstring first;
	winrt::hstring name;
	winrt::hstring room;
	winrt::hstring group;

public:
	Person() = default;
	Person(winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring);
	Person(std::vector<std::string>);

	void SetPerson(winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring, winrt::hstring);

	bool operator==(const Person&) const;
	bool operator!=(const Person&) const;
	bool operator<=(const Person&) const;

	winrt::hstring to_string() const;
	winrt::hstring print_name() const;
};

