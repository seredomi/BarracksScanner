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

        groupMatches.clear();
		if (ResidentCheck().IsChecked())
			groupMatches.insert("Resident");
		else
			groupMatches.erase("Resident");
		if (RotationalUnitCheck().IsChecked())
			groupMatches.insert("Rotational Unit");
		else
			groupMatches.erase("Rotational Unit");
		if (HotelDivartyCheck().IsChecked())
			groupMatches.insert("Hotel Divarty");
		else
			groupMatches.erase("Hotel Divarty");
		if (ChainOfCommandCheck().IsChecked())
			groupMatches.insert("COC");
		else
			groupMatches.erase("COC");
        RefreshPersonnel();
	}

	void PersonnelPage::PageLoaded(IInspectable const&, RoutedEventArgs const&) {
        idMatch = "";
        firstMatch = "";
        lastMatch = "";
        groupMatches = set<string>{ "Resident", "Rotational Unit", "Hotel Divarty", "COC" };
        roomMatch = "";
	}

    void PersonnelPage::RefreshPersonnel() {

        BuildQuery();
        Database db = Database(query);
        db.executeQuery();
        vector<vector<string>> result = db.result;

        ClearColumns();

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

    void PersonnelPage::ClearColumns() {

        RankColumn().Children().Clear();
        Controls::TextBlock rankHeader;
        rankHeader.Margin(Thickness{ 0,8,8,8 });
        rankHeader.FontSize(20);
        rankHeader.FontWeight(Windows::UI::Text::FontWeight{ 600 });
        rankHeader.Text(L"Rank");
        RankColumn().Children().Append(rankHeader);

        FirstColumn().Children().Clear();
        Controls::TextBlock firstHeader;
        firstHeader.Margin(Thickness{ 0,8,8,8 });
        firstHeader.FontSize(20);
        firstHeader.FontWeight(Windows::UI::Text::FontWeight{ 600 });
        firstHeader.Text(L"First");
        FirstColumn().Children().Append(firstHeader);

        LastColumn().Children().Clear();
        Controls::TextBlock lastHeader;
        lastHeader.Margin(Thickness{ 0,8,8,8 });
        lastHeader.FontSize(20);
        lastHeader.FontWeight(Windows::UI::Text::FontWeight{ 600 });
        lastHeader.Text(L"Last");
        LastColumn().Children().Append(lastHeader);

        GroupColumn().Children().Clear();
        Controls::TextBlock groupHeader;
        groupHeader.Margin(Thickness{ 0,8,8,8 });
        groupHeader.FontSize(20);
        groupHeader.FontWeight(Windows::UI::Text::FontWeight{ 600 });
        groupHeader.Text(L"Group");
        GroupColumn().Children().Append(groupHeader);
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
		res = res.substr(0, res.size() - 1) + ")"; // strip final ',' before adding ')'
        res += ";";

        query = res;
    }

	void winrt::BarracksScanner::implementation::PersonnelPage::ResidentCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (ResidentCheck().IsChecked()) {
            groupMatches.insert("Resident");
        }
        else {
            groupMatches.erase("Resident");
        }
        RefreshPersonnel();
	}

	void winrt::BarracksScanner::implementation::PersonnelPage::RotationalUnitCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (RotationalUnitCheck().IsChecked()) {
            groupMatches.insert("Rotational Unit");
        }
        else {
            groupMatches.erase("Rotational Unit");
        }
        RefreshPersonnel();

	}

	void winrt::BarracksScanner::implementation::PersonnelPage::HotelDivartyCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (HotelDivartyCheck().IsChecked()) {
            groupMatches.insert("Hotel Divarty");
        }
        else {
            groupMatches.erase("Hotel Divarty");
        }
		RefreshPersonnel();
	}

	void winrt::BarracksScanner::implementation::PersonnelPage::ChainOfCommandCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {

        if (ChainOfCommandCheck().IsChecked()) {
            groupMatches.insert("COC");
        }
        else {
            groupMatches.erase("COC");
        }
        RefreshPersonnel();
	}
}











