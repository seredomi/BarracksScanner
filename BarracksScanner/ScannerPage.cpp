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

    hstring ScannerPage::ScanBuffer() const& {
        return scanBuffer;
    }

    void ScannerPage::ScanBuffer(const hstring str) {
        scanBuffer = scanBuffer + str;
    }

    void ScannerPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
        ScannerPage::InsertBlankCard();
    }

    void ScannerPage::InsertBlankCard() {

        Controls::Border card;
        card.Width(600);
        card.Height(400);
        card.VerticalAlignment(VerticalAlignment::Top);

        Controls::TextBlock header;
        header.Text(L"Scanner");
        header.FontSize(30);

        ScannerPage::CardStack().Children().Append(header);

    }

    void ScannerPage::WaitForScan() {

        while (1) {

        }
        

    }

    void ScannerPage::ScanHandler(Windows::UI::Core::CoreWindow, Windows::UI::Core::CharacterReceivedEventArgs) {
        // Microsoft::UI::Xaml::Window::Current().CoreWindow().
    }
}
