#include "pch.h"
#include "ScannerPage.h"
#if __has_include("ScannerPage.g.cpp")
#include "ScannerPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::BarracksScanner::implementation
{

    ScannerPage::ScannerPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            scanBuffer = L"test";
            // this->Focus(Windows::UI::Xaml::FocusState());
        }


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
        ScannerPage::DisplayScanbuffer();
    }

    void ScannerPage::DisplayScanbuffer() {

        Controls::Border card;
        card.Width(600);
        card.Height(400);
        card.VerticalAlignment(VerticalAlignment::Top);

        Controls::TextBlock header;
        header.Text(scanBuffer);
        header.FontSize(30);

        ScannerPage::CardStack().Children().Append(header);

    }

    void ScannerPage::WaitForScan() {

        while (1) {

        }
        

    }

	void ScannerPage::ScanHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args) {
        /*
        if char is not enter, add to scanBuffer
        else, insertblankpage for now 
        */
        UINT scanCode = MapVirtualKey((UINT) args.Key(), MAPVK_VK_TO_CHAR);
        
        // if its enter, display scanbuffer
        if ((UINT) scanCode == 13) {
            DisplayScanbuffer();
        }
        // else if its not a shift, add it to scanBuffer
        else if ((UINT) scanCode != 0) {
            ScanBuffer(hstring{ static_cast<wchar_t>(scanCode) });
        }
    }

}
