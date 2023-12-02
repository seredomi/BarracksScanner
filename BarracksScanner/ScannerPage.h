#pragma once

#include "ScannerPage.g.h"
#include <vector>
#include <string>

namespace winrt::BarracksScanner::implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage>
    {
        hstring scanBuffer;
        std::vector<clock_t> charTimes;

        ScannerPage();

        hstring ScanBuffer() const&;
        void ResetScanBuffer();
        void AddToScanBuffer(const hstring);

        void InputHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const&);
        void SearchPersonnel();
        void ResultNotFound();
        void ResultFound(std::vector<std::vector<std::string>>);

        void Print(winrt::hstring);

        void ScannerPageObject_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ScannerPageObject_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ScannerStatus_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct ScannerPage : ScannerPageT<ScannerPage, implementation::ScannerPage> {
    };
}
