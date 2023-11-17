#include "pch.h"
#include "ScannerPage.h"
#if __has_include("ScannerPage.g.cpp")
#include "ScannerPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::BarracksScanner::implementation
{
    int32_t ScannerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ScannerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ScannerPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
