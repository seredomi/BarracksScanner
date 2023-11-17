#include "pch.h"
#include "LogsPage.h"
#if __has_include("LogsPage.g.cpp")
#include "LogsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::BarracksScanner::implementation
{
    int32_t LogsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void LogsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void LogsPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"LOGS!"));
    }
}
