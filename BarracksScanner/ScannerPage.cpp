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

	void ScannerPage::InputHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args) {

        // this is my solution for handling all keyboard input
        // it attempts to isolate barcode scans based on time between "keystrokes"
        // it fails if a user is mashing the keyboard while scanning, but successfully disregards other keybaord input before/after a scan

        UINT scanCode = MapVirtualKey((UINT) args.Key(), MAPVK_VK_TO_CHAR);

        // record keystroke times
        charTimes.push_back(std::clock());

		// if [enter], strip buffer of non-scanner input
        if (scanCode == 13) {
            // scannerInputStartIndex tracks where scanner input starts based on key entry time
            unsigned int scannerInputStartIndex = 0;
            for (int i = 1; i < charTimes.size(); ++i) {
                float td = (float)(charTimes[i] - charTimes[i - 1]) / CLOCKS_PER_SEC;
                if (td > 0.035) {
                    scannerInputStartIndex = i;
                }
            }
            // if scanBuffer has scanner input
			if (scannerInputStartIndex < charTimes.size() - 1) {
                // if the scanner also has some kb input, remove those characters
                if (scannerInputStartIndex != 0) {
                    hstring newScanBuffer;
                    for (scannerInputStartIndex; scannerInputStartIndex < scanBuffer.size(); ++scannerInputStartIndex) {
                        newScanBuffer = newScanBuffer + scanBuffer[scannerInputStartIndex];
                    }
                    scanBuffer = newScanBuffer;
                }

                Print(scanBuffer);
            }
			ResetScanBuffer();
			BarcodeEntry().Text(scanBuffer);
            charTimes.clear();
        }

		// else if not [shift] or [tab], add char to scanBuffer
		else if (scanCode != 0 && scanCode != 9) {
			AddToScanBuffer(hstring{ static_cast<wchar_t>(scanCode) });
		}
    }
	void ScannerPage::ScannerPageObject_GotFocus(IInspectable const& sender, RoutedEventArgs const& e) {
        this->Focus(FocusState::Programmatic);
        ScannerStatus().Text(L"Ready to scan");
	}

	void ScannerPage::ScannerPageObject_LostFocus(IInspectable const& sender, RoutedEventArgs const& e) {
        this->Focus(FocusState::Programmatic);
        ScannerStatus().Text(L"Click on this window before scanning");
	}
}






