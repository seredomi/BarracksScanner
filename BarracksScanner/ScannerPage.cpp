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
        readyToScan = true;
        scanning = false;
        lastChar = 0;
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
        BarcodeEntry().Text(scanBuffer);
    }

    void ScannerPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }

    void ScannerPage::DisplayScanbuffer() {

        Controls::TextBlock header;
        header.Text(scanBuffer);
        header.FontSize(30);

        CardStack().Children().Append(header);
    }

    void ScannerPage::Print(hstring text) {
        Controls::TextBlock newTB;
        newTB.Text(text);
        CardStack().Children().Append(newTB);
    }

	void ScannerPage::TextHandler(Controls::TextBox const& sender, Controls::TextBoxTextChangingEventArgs const& args) {
    }

	void ScannerPage::ScanHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args) {

        float timeDelta;

        UINT scanCode = MapVirtualKey((UINT) args.Key(), MAPVK_VK_TO_CHAR);


        if (!scanning) {
            scanning = true;
            timeDelta = 0;
            lastChar = std::clock();
        }
        else {
			timeDelta = (float) (std::clock() - lastChar) / CLOCKS_PER_SEC;
            lastChar = std::clock();
        }
        Print(to_hstring(timeDelta));

        // only take input if it seems like its fast enough to be from a scanner
        if (timeDelta < 0.035) {
			// if enter, display scanbuffer and reset it
			if (scanCode == 13) {
				DisplayScanbuffer();
				ResetScanBuffer();
				BarcodeEntry().Text(scanBuffer);
				scanning = false;
			}
			// else if not shift, add it to scanBuffer
			else if (scanCode != 0 && scanCode != 9) {
				AddToScanBuffer(hstring{ static_cast<wchar_t>(scanCode) });
			}
        }
        else {
            ResetScanBuffer();
			BarcodeEntry().Text(scanBuffer);
            scanning = false;
        }
        
    }
	void ScannerPage::ScannerPageObject_GotFocus(IInspectable const& sender, RoutedEventArgs const& e) {
        BarcodeEntry().Focus(FocusState::Programmatic);
	}

	void ScannerPage::ScannerPageObject_LostFocus(IInspectable const& sender, RoutedEventArgs const& e) {
        BarcodeEntry().Focus(FocusState::Programmatic);
	}

	void ScannerPage::BarcodeEntry_GotFocus(Windows::Foundation::IInspectable const& sender, RoutedEventArgs const& e) {
        BarcodeEntry().PlaceholderText(L"Ready to scan");
	}
	void ScannerPage::BarcodeEntry_LostFocus(Windows::Foundation::IInspectable const& sender, RoutedEventArgs const& e) {
        BarcodeEntry().PlaceholderText(L"Click here before scanning");
	}
}






