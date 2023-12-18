#include "pch.h"
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
        // i don't know what args to pass to this func, but this would simplify the code ->  FilterCheckChanged(SelectAllGroups(), SelectAllGroups().)
        for (Controls::CheckBox cb : set<Controls::CheckBox>{ ResidentCheck(), RotationalUnitCheck(), HotelDivartyCheck(), ChainOfCommandCheck() })
			cb.IsChecked(true);
        RefreshPersonnel();
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

		const float spacerSize = 9;

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
			ColumnHeaders().Margin(Thickness{10, 0, 0, 10});
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


        // for (vector<string> row : result) {
        //     Person newPerson;
        //     if (row.size() == 6) {
		// 		newPerson = Person(row);
        //     }
        //     else {
        //         // no results found
        //         int i = 0;
        //     }
        //     Controls::TextBlock rank;
		// 	rank.Text(newPerson.rank);
        //     if (rank.Text().empty())
        //         rank.Text(L" ");
        //     rank.Margin(Thickness{ 0,0,8,8 });
        //     RankColumn().Children().Append(rank);

        //     Controls::TextBlock last;
        //     last.Margin(Thickness{ 0,0,8,8 });
        //     last.Text(newPerson.last);
        //     if (newPerson.last == L"") {
        //         last.Text(L" ");
        //     }
        //     LastColumn().Children().Append(last);
        //     
        //     Controls::TextBlock first;
        //     first.Text(newPerson.first);
        //     if (newPerson.first == L"") {
        //         first.Text(L" ");
        //     }
        //     first.Margin(Thickness{ 0,0,8,8 });
        //     FirstColumn().Children().Append(first);

        //     Controls::TextBlock group;
        //     group.Text(newPerson.group);
        //     group.Margin(Thickness{ 0,0,8,8 });
        //     GroupColumn().Children().Append(group);
        // }
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















