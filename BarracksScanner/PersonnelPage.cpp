#include "pch.h"
#include "PersonnelPage.h"
#include "Database.h"
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
        Button().Content(box_value(L"Personnel Clicked"));

        string query = "SELECT * FROM personnel INNER JOIN logs ON personnel.id = logs.id WHERE personnel.firstName LIKE '%sereno%'";
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
}
