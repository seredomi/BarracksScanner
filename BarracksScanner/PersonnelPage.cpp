#include "pch.h"
#include "PersonnelPage.h"
#if __has_include("PersonnelPage.g.cpp")
#include "PersonnelPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

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
    }
}
