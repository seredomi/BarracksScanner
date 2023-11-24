#pragma once

#include "ScannerPage.g.h"

namespace winrt::BarracksScanner::implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage>
    {
        hstring scanBuffer;

        ScannerPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        hstring ScanBuffer() const&;
        void ScanBuffer(const hstring);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void ScanHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);

        void DisplayScanbuffer();

        void WaitForScan();
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage, implementation::ScannerPage>
    {
    };
}
