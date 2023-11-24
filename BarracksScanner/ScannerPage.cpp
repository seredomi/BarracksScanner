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
        ResetScanBuffer();
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
    void ScannerPage::ResetScanBuffer() {
        scanBuffer = L"";
    }
    void ScannerPage::AddToScanBuffer(const hstring str) {
        scanBuffer = scanBuffer + str;
    }

    void ScannerPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
        // ScannerPage::DisplayScanbuffer();
    }

    void ScannerPage::DisplayScanbuffer() {

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

        UINT scanCode = MapVirtualKey((UINT) args.Key(), MAPVK_VK_TO_CHAR);
        
        // if enter, display scanbuffer and reset it
        if (scanCode == 13) {
            DisplayScanbuffer();
            ResetScanBuffer();
        }
        // else if not shift, add it to scanBuffer
        else if (scanCode != 0 && scanCode != 9) {
            AddToScanBuffer(hstring{ static_cast<wchar_t>(scanCode) });
        }
    }

}
