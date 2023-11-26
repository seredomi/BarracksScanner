#include "pch.h"
#include "ScannerPage.h"
#if __has_include("ScannerPage.g.cpp")
#include "ScannerPage.g.cpp"
#endif
#include "Database.h"
#include <string>
#include <vector>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace std;

namespace winrt::BarracksScanner::implementation
{

    ScannerPage::ScannerPage()
	{
        ResetScanBuffer();
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

    void ScannerPage::SearchPersonnel() {

        string query = "SELECT rank,lastName,firstName,groupName FROM personnel WHERE id LIKE '%" + to_string(scanBuffer) + "%'";
        Database db = Database(query);
        db.executeQuery();
        vector<vector<string>> result = db.result;

        hstring textResult = L"";

        if (result.size() < 1) {
            textResult = scanBuffer + L" was not found in the database\n";
        }
        else {
            textResult = L"Name: " + to_hstring(result[0][0] + " " + result[0][1] + "\nGroup: " + result[0][3] + "\n");
        }

        Controls::TextBlock tb;
        tb.Text(textResult);
        CardStack().Children().Append(tb);
    }

    void ScannerPage::ResultNotFound() {
    }

    void ScannerPage::ResultFound(vector<vector<string>> result) {
    }

    void ScannerPage::Print(hstring text) {
        Controls::TextBlock newTB;
        newTB.Text(text);
        CardStack().Children().Append(newTB);
    }

	void ScannerPage::InputHandler(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args) {

        // this is my solution for handling all keyboard input
        // it attempts to isolate barcode scans based on time between "keystrokes"
        // it fails if a user is mashing the keyboard while scanning, but successfully disregards other keybaord input before/after a scan

        UINT scanCode = MapVirtualKey((UINT) args.Key(), MAPVK_VK_TO_CHAR);

        // record keystroke times
        charTimes.emplace_back(std::clock());

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

                SearchPersonnel();
            }
			ResetScanBuffer();
            charTimes.clear();
        }

		// else if not [shift] or [tab], add char to scanBuffer
		else if (scanCode != 0 && scanCode != 9) {
			AddToScanBuffer(hstring{ static_cast<wchar_t>(scanCode) });
		}
    }
	void ScannerPage::ScannerPageObject_GotFocus(IInspectable const&, RoutedEventArgs const&) {
        this->Focus(FocusState::Programmatic);
        ScannerStatus().Text(L"Ready to scan");
	}

	void ScannerPage::ScannerPageObject_LostFocus(IInspectable const&, RoutedEventArgs const&) {
        this->Focus(FocusState::Programmatic);
        ScannerStatus().Text(L"Click on this window before scanning");
	}
}






