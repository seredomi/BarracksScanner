#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#include "ScannerPage.g.h"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::BarracksScanner::implementation
{

	void MainWindow::NavView_Loaded(IInspectable const&, RoutedEventArgs const) {
		ContentFrame().Navigate(winrt::xaml_typename<BarracksScanner::ScannerPage>());
		// not sure why this doesnt work
		NavView().SelectedItem() = NavView().MenuItems().GetAt(0);
		ContentFrame().Focus(FocusState::Programmatic);
	}

    void MainWindow::NavView_SelectionChanged(Controls::NavigationView const&,
        Controls::NavigationViewSelectionChangedEventArgs const& args) {

        auto navItemTag = winrt::unbox_value<hstring>(args.SelectedItemContainer().Tag());

		if (navItemTag == L"scanner") {
			ContentFrame().Navigate(winrt::xaml_typename<BarracksScanner::ScannerPage>(), NULL, Microsoft::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
		}
		if (navItemTag == L"personnel") {
			ContentFrame().Navigate(winrt::xaml_typename<BarracksScanner::PersonnelPage>(), NULL, Microsoft::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
		}
		if (navItemTag == L"logs") {
			ContentFrame().Navigate(winrt::xaml_typename<BarracksScanner::LogsPage>(), NULL, Microsoft::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
		}

		ContentFrame().Focus(FocusState::Programmatic);
    }
	
	void MainWindow::scanner_GotFocus(Windows::Foundation::IInspectable sender, RoutedEventArgs const&) {
		ContentFrame().Focus(FocusState::Programmatic);
	}
	void MainWindow::personnel_GotFocus(Windows::Foundation::IInspectable sender, RoutedEventArgs const&) {
		ContentFrame().Focus(FocusState::Programmatic);
	}
	void MainWindow::logs_GotFocus(Windows::Foundation::IInspectable sender, RoutedEventArgs const&) {
		ContentFrame().Focus(FocusState::Programmatic);
	}
}



