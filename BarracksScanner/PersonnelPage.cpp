﻿#include "pch.h"
#include "PersonnelPage.h"
#include "Database.h"
#include "Person.h"
#if __has_include("PersonnelPage.g.cpp")
#include "PersonnelPage.g.cpp"
#endif
#include <string>
#include <vector>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace std;

namespace winrt::BarracksScanner::implementation
{
    int32_t PersonnelPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PersonnelPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void PersonnelPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Database db = Database(query);
        db.executeQuery();
        vector<vector<string>> result = db.result;

        hstring hresult = L"";
		for (vector<string> row : result) {
			for (string item : row) {
				hresult = hresult + to_hstring(item) + L", ";
			}
			hresult = hresult + L"\n";
		}


        Controls::TextBlock tb;
        tb.Text(hresult);
        CardStack().Children().Append(tb);

    }
	void PersonnelPage::FilterTextChanged(IInspectable const&, Controls::TextChangedEventArgs const&) {
        lastMatch = to_string(LastNameFilter().Text());
        firstMatch = to_string(FirstNameFilter().Text());
        RefreshPersonnel();
	}
    
	void PersonnelPage::FilterCheckChanged(winrt::Windows::Foundation::IInspectable const& sender, RoutedEventArgs const& e) {

        set<Controls::CheckBox> groupCheckBoxes = { ResidentCheck(), RotationalUnitCheck(), HotelDivartyCheck(), ChainOfCommandCheck() };

        if (sender == SelectAllGroups())
            for (Controls::CheckBox cb : groupCheckBoxes)
                cb.IsChecked(true);
        if (sender == RemoveAllGroups())
            for (Controls::CheckBox cb : groupCheckBoxes)
                cb.IsChecked(false);

	}

	void PersonnelPage::PageLoaded(IInspectable const&, RoutedEventArgs const&) {
        idMatch = "";
        firstMatch = "";
        lastMatch = "";
        groupMatches = set<string>{};
        roomMatch = "";
        // FilterCheckChanged(SelectAllGroups(), SelectAllGroups().)
        for (Controls::CheckBox cb : set<Controls::CheckBox>{ ResidentCheck(), RotationalUnitCheck(), HotelDivartyCheck(), ChainOfCommandCheck() })
			cb.IsChecked(true);
        RefreshPersonnel();
	}

    void PersonnelPage::RefreshPersonnel() {

        BuildQuery();
        Database db = Database(query);
        db.executeQuery();
        vector<vector<string>> result = db.result;

        for (Controls::StackPanel col : set<Controls::StackPanel>{ RankColumn(), LastColumn(), FirstColumn(), GroupColumn(), ButtonColumn() })
            col.Children().Clear();

        for (vector<string> row : result) {
            Person newPerson;
            if (row.size() == 6) {
				newPerson = Person(row);
            }
            Controls::TextBlock rank;
			rank.Text(newPerson.rank);
            if (rank.Text().empty())
                rank.Text(L" ");
            rank.Margin(Thickness{ 0,0,8,8 });
            RankColumn().Children().Append(rank);

            Controls::TextBlock last;
            last.Margin(Thickness{ 0,0,8,8 });
            last.Text(newPerson.last);
            if (newPerson.last == L"") {
                last.Text(L" ");
            }
            LastColumn().Children().Append(last);
            
            Controls::TextBlock first;
            first.Text(newPerson.first);
            if (newPerson.first == L"") {
                first.Text(L" ");
            }
            first.Margin(Thickness{ 0,0,8,8 });
            FirstColumn().Children().Append(first);

            Controls::TextBlock group;
            group.Text(newPerson.group);
            group.Margin(Thickness{ 0,0,8,8 });
            GroupColumn().Children().Append(group);
        }
    }

    void PersonnelPage::BuildQuery() {

        string res = "SELECT id,rank,lastName,firstName,room,groupName FROM personnel";
        res += " WHERE id LIKE '%" + idMatch + "%'";
        res += " AND firstName LIKE '%" + firstMatch + "%' and lastName LIKE '%" + lastMatch + "%'";
        res += " AND room LIKE '%" + roomMatch + "%'";
        res += " AND groupName IN (";
        for (string group : groupMatches) {
            res += "'" + group + "',";
        }
        if (groupMatches.size() != 0) // strip final ',' before adding ')'
			res = res.substr(0, res.size() - 1); 
        res += ");";

        query = res;
    }

    void PersonnelPage::ResidentCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("Resident"); RefreshPersonnel(); }
	void PersonnelPage::ResidentCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("Resident"); RefreshPersonnel();}
	void PersonnelPage::RotationalUnitCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("Rotational Unit"); RefreshPersonnel();}
	void PersonnelPage::RotationalUnitCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("Rotational Unit"); RefreshPersonnel();}
	void PersonnelPage::HotelDivartyCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("Hotel Divarty"); RefreshPersonnel();}
	void PersonnelPage::HotelDivartyCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("Hotel Divarty"); RefreshPersonnel();}
	void PersonnelPage::ChainOfCommandCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("COC"); RefreshPersonnel();}
	void PersonnelPage::ChainOfCommandCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("COC"); RefreshPersonnel();}
}











