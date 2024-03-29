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
        TitleStack().Children().Append(tb);

    }

	void PersonnelPage::PersonButtonPointerEntered(IInspectable const& sender, Input::PointerRoutedEventArgs const&) {
        Controls::StackPanel sp = sender.try_as<Controls::StackPanel>();
        Controls::TextBlock tb; tb.Text(L"test");
        sp.Children().Append(tb);
	}

	void PersonnelPage::PersonnelSearch_TextChanged(Controls::AutoSuggestBox const&, Controls::AutoSuggestBoxTextChangedEventArgs const&) {
        match = to_string(PersonnelSearch().Text());
        RefreshPersonnel();
	}
    
	void PersonnelPage::FilterCheckChanged(winrt::Windows::Foundation::IInspectable const& sender, RoutedEventArgs const&) {

        set<Controls::CheckBox> groupCheckBoxes = { ResidentCheck(), RotationalUnitCheck(), HotelDivartyCheck(), ChainOfCommandCheck() };

        if (sender == SelectAllGroups())
            for (Controls::CheckBox cb : groupCheckBoxes)
                cb.IsChecked(true);
        if (sender == RemoveAllGroups())
            for (Controls::CheckBox cb : groupCheckBoxes)
                cb.IsChecked(false);

	}

	void PersonnelPage::PageLoaded(IInspectable const&, RoutedEventArgs const&) {
        match = "";
        groupMatches = set<string>{};
        order = "";
        // i don't know what args to pass to this func, but this would simplify the code ->  FilterCheckChanged(SelectAllGroups(), SelectAllGroups().)
        for (Controls::CheckBox cb : set<Controls::CheckBox>{ ResidentCheck(), RotationalUnitCheck(), HotelDivartyCheck(), ChainOfCommandCheck() })
			cb.IsChecked(true);
        LastAsc().IsChecked(true);
        RefreshPersonnel();
	}

    void PersonnelPage::BuildCreate() {
        hstring res = L"INSERT INTO personnel (id, rank, lastName, firstName, room, groupName, leaveDate) VALUES ";
        res = res + L"('" + IDInput().Text();
        // res += "', '" + to_string(RankInput().SelectedValue().try_as<Controls::ComboBox>().Text());
        // res = res + unbox_value<hstring>(RankInput().Items().GetAt(RankInput().SelectedIndex()));
        res = res + L"', '" + LastInput().Text();
        res = res + L"', '" + FirstInput().Text();
        res = res + L"', '" + RoomInput().Text();
        // res += "', '" + to_string(GroupInput().SelectedValue().try_as<Controls::ComboBox>().Text());

        Windows::Foundation::DateTime dt = DateInput().Date(); Windows::Globalization::Calendar cal; cal.SetDateTime(dt);
		res = res + L"', '" + cal.YearAsString() + L"-" + cal.MonthAsNumericString() + L"-" + cal.DayAsString();
        res = res + L"');";


        Controls::TextBlock tb;
        tb.Text(to_hstring(res));
        TitleStack().Children().Append(tb);

    }
    void PersonnelPage::BuildQuery() {

        string res = "SELECT id,rank,lastName,firstName,room,groupName FROM personnel";
        res += " WHERE ( id LIKE '%" + match + "%'";
        res += " OR firstName LIKE '%" + match + "%' OR lastName LIKE '%" + match + "%'";
        res += " OR room LIKE '%" + match + "%' )";
        res += " AND groupName IN (";
        for (string group : groupMatches) {
            res += "'" + group + "',";
        }
        if (groupMatches.size() != 0) // strip final ',' before adding ')'
			res = res.substr(0, res.size() - 1); 
        res += ")";
        if (order != "") {
            res += " ORDER BY " + order;
        }

        query = res + " ;";
    }

    void PersonnelPage::RefreshPersonnel() {


        BuildQuery();
        Database db = Database(query);
        db.executeQuery();
        vector<vector<string>> result = db.result;

        DataStack().Children().Clear();
        ColumnHeaders().Children().Clear();

        float minRankWidth = 0;
        float minLastWidth = 0;
        float minFirstWidth = 0;
        float minGroupWidth = 0;

        vector<Person> personnel;

		const float spacerSize = 11;

        // fill personnel vector and calculates minimum width per column
        for (vector<string> row : result) {
            Person newPerson;
            if (row.size() == 6) { newPerson = Person(row); }
            personnel.push_back(newPerson);

            Controls::TextBlock rankTB; rankTB.Text(newPerson.rank); rankTB.Measure(Windows::Foundation::Size{ (double) INFINITY, (double) INFINITY });
            if (rankTB.DesiredSize().Width > minRankWidth) minRankWidth = rankTB.DesiredSize().Width + spacerSize;
            Controls::TextBlock lastTB; lastTB.Text(newPerson.last); lastTB.Measure(Windows::Foundation::Size{ (double) INFINITY, (double) INFINITY });
            if (lastTB.DesiredSize().Width > minLastWidth) minLastWidth = lastTB.DesiredSize().Width + spacerSize;
            Controls::TextBlock firstTB; firstTB.Text(newPerson.first); firstTB.Measure(Windows::Foundation::Size{ (double) INFINITY, (double) INFINITY });
            if (firstTB.DesiredSize().Width > minFirstWidth) minFirstWidth = firstTB.DesiredSize().Width + spacerSize;
            Controls::TextBlock groupTB; groupTB.Text(newPerson.group); groupTB.Measure(Windows::Foundation::Size{ (double) INFINITY, (double) INFINITY });
            if (groupTB.DesiredSize().Width > minGroupWidth) minGroupWidth = groupTB.DesiredSize().Width;

        }

        // column headers + no results message
        if (result.size() == 0) {
            Controls::TextBlock errMsg; errMsg.Text(L"No results found..."); errMsg.Margin(Thickness{ 8 });
            errMsg.FontStyle(Windows::UI::Text::FontStyle::Italic);  errMsg.FontWeight(Windows::UI::Text::FontWeight{ 600 }); 
            ColumnHeaders().Children().Append(errMsg);
        }
        else {
			Controls::TextBlock rankHeader; rankHeader.Text(L"Rank"); minRankWidth = 45; rankHeader.MinWidth(minRankWidth); 
			Controls::TextBlock lastHeader; lastHeader.Text(L"Last"); lastHeader.MinWidth(minLastWidth);
			Controls::TextBlock firstHeader; firstHeader.Text(L"First"); firstHeader.MinWidth(minFirstWidth);
			Controls::TextBlock groupHeader; groupHeader.Text(L"Group"); groupHeader.MinWidth(minGroupWidth);
			for (Controls::TextBlock tb : vector<Controls::TextBlock>{ rankHeader, lastHeader, firstHeader, groupHeader }) {
				tb.FontSize(17);
				tb.FontWeight(Windows::UI::Text::FontWeight{ 600 });
				ColumnHeaders().Children().Append(tb);
			}
        }

        for (Person person : personnel) {

            Controls::TextBlock rankTB; rankTB.Text(person.rank); rankTB.MinWidth(minRankWidth);
            Controls::TextBlock lastTB; lastTB.Text(person.last); lastTB.MinWidth(minLastWidth);
            Controls::TextBlock firstTB; firstTB.Text(person.first); firstTB.MinWidth(minFirstWidth);
            Controls::TextBlock groupTB; groupTB.Text(person.group); groupTB.MinWidth(minGroupWidth);

            Controls::StackPanel personInfoStack;
            personInfoStack.Orientation(Controls::Orientation::Horizontal);
            personInfoStack.Children().Append(rankTB); personInfoStack.Children().Append(lastTB); personInfoStack.Children().Append(firstTB); personInfoStack.Children().Append(groupTB); 

			Controls::Button personButton;
            personButton.Content(personInfoStack);
            personButton.Margin(Thickness{ 0,0,0,7 });
            personButton.BorderThickness(Thickness{ 0 });
            personButton.MinHeight(10);


            Controls::StackPanel personStack;
            personStack.Orientation(Controls::Orientation::Horizontal);
            // not sure why this doesnt work... personStack.PointerEntered(PersonnelPage::PersonButtonPointerEntered);

            DataStack().Children().Append(personButton);
        }

    }

    void PersonnelPage::ResidentCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("Resident"); RefreshPersonnel(); }
	void PersonnelPage::ResidentCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("Resident"); RefreshPersonnel();}
	void PersonnelPage::RotationalUnitCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("Rotational Unit"); RefreshPersonnel();}
	void PersonnelPage::RotationalUnitCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("Rotational Unit"); RefreshPersonnel();}
	void PersonnelPage::HotelDivartyCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("Hotel Divarty"); RefreshPersonnel();}
	void PersonnelPage::HotelDivartyCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("Hotel Divarty"); RefreshPersonnel();}
	void PersonnelPage::ChainOfCommandCheck_Checked(IInspectable const&, RoutedEventArgs const&) { groupMatches.insert("COC"); RefreshPersonnel();}
	void PersonnelPage::ChainOfCommandCheck_Unchecked(IInspectable const&, RoutedEventArgs const&) { groupMatches.erase("COC"); RefreshPersonnel();}

	void PersonnelPage::SortRadioChecked(IInspectable const& sender, RoutedEventArgs const&) {
        if (sender == IDAsc()) order = "id ASC";
        else if (sender == IDDesc()) order = "id DESC";
        else if (sender == RankAsc()) order = "rank ASC";
        else if (sender == RankDesc()) order = "rank DESC";
        else if (sender == LastAsc()) order = "lastName ASC";
        else if (sender == LastDesc()) order = "lastName DESC";
        else if (sender == FirstAsc()) order = "firstName ASC";
        else if (sender == FirstDesc()) order = "firstName DESC";
        else if (sender == GroupAsc()) order = "groupName ASC";
        else if (sender == GroupDesc()) order = "groupName DESC";
        else if (sender == RoomAsc()) order = "room ASC";
        else if (sender == RoomDesc()) order = "room DESC";

        RefreshPersonnel();
	}
	void PersonnelPage::NewPerson_Click(IInspectable const&, RoutedEventArgs const&) {

        Controls::ContentDialog dialog = PersonInfo();
        Controls::TextBlock title; title.FontWeight(Windows::UI::Text::FontWeight{ 600 }); title.Text(L"Create New Person"); 
        dialog.Title(title);
        dialog.XamlRoot(this->XamlRoot());

        auto res = dialog.ShowAsync();
	}

    void PersonnelPage::PersonInfo_TextChanged(IInspectable const&, Controls::TextChangedEventArgs const&) { VerifyInput(); }
    void PersonnelPage::PersonInfo_SelectionChanged(IInspectable const&, Controls::SelectionChangedEventArgs const&) { VerifyInput(); }
	void PersonnelPage::PersonInfo_DateChanged(IInspectable const&, Controls::DatePickerValueChangedEventArgs const&) { VerifyInput(); }
    void PersonnelPage::PersonInfoError(Controls::Control control, hstring message) { PersonInfoErrMsg().Text(message); }

    void PersonnelPage::VerifyInput() {
        bool pass = true;

        // empty inputs
        for (Controls::TextBox t : vector<Controls::TextBox>{ IDInput(), FirstInput(), LastInput(), }) {
            string in = to_string(t.Text());
            if (in == "") PersonInfo().IsPrimaryButtonEnabled(false);
        }
        for (Controls::ComboBox c : vector<Controls::ComboBox>{ GroupInput(), RankInput() })
            if (c.SelectedIndex() == -1) pass = false;
		if (DateInput().SelectedDate() == NULL) pass = false;

        // bad chars
        for (Controls::TextBox t : vector<Controls::TextBox>{ IDInput(), FirstInput(), LastInput(), RoomInput() }) {
            string in = to_string(t.Text());
            if (in.find(';') != -1 || in.find('\'') != -1 || in.find('"') != -1 || in.find('.') != -1) {
                PersonInfoErrMsg().Text(L"Text fields cannot contain the following characters: ' \" ., ;");
                pass = false;
            }
		}

        if (pass) {
            PersonInfoErrMsg().Text(L"");
            PersonInfo().IsPrimaryButtonEnabled(true);
        }
    }

	void PersonnelPage::PersonInfo_Closed(Controls::ContentDialog const&, Controls::ContentDialogClosedEventArgs const&) {
        // clears the dialog
        IDInput().Text(L"");
        RankInput().SelectedIndex(-1);
        GroupInput().SelectedIndex(-1);
        FirstInput().Text(L"");
        LastInput().Text(L"");
        RoomInput().Text(L"");
        DateInput().SelectedDate(NULL);
	}


	void PersonnelPage::PersonInfo_PrimaryButtonClick(Controls::ContentDialog const&, Controls::ContentDialogButtonClickEventArgs const&) {
        BuildCreate();
	}
}


