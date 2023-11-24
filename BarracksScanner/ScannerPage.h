#pragma once

#include "ScannerPage.g.h"

namespace winrt::BarracksScanner::implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage>
    {
        hstring scanBuffer;

        ScannerPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            scanBuffer = L"";
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        hstring ScanBuffer() const&;
        void ScanBuffer(const hstring);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void ScanHandler(Windows::UI::Core::CoreWindow, Windows::UI::Core::CharacterReceivedEventArgs);

        void InsertBlankCard();

        void WaitForScan();
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage, implementation::ScannerPage>
    {
    };
}
