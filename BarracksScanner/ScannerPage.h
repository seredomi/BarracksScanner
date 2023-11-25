#pragma once

#include "ScannerPage.g.h"

namespace winrt::BarracksScanner::implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage>
    {
        hstring scanBuffer;
        bool readyToScan;
        bool scanning;
        clock_t lastChar;

        ScannerPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        hstring ScanBuffer() const&;
        void ResetScanBuffer();
        void AddToScanBuffer(const hstring);

        void ClickHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);

        void TextHandler(Microsoft::UI::Xaml::Controls::TextBox const&, Microsoft::UI::Xaml::Controls::TextBoxTextChangingEventArgs const&);
        void ScanHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const&);

        void DisplayScanbuffer();

        void ReadyToScan(bool);

        void Print(winrt::hstring);

        void ScannerPageObject_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ScannerPageObject_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void BarcodeEntry_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void BarcodeEntry_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage, implementation::ScannerPage>
    {
    };
}
