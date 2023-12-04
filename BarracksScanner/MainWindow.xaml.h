#pragma once

#include "MainWindow.g.h"
#include "pch.h"

namespace winrt::BarracksScanner::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
			AppWindow().SetIcon(L"transparent-square.ico");
            // not sure why this doesn't work
            AppWindow().MoveAndResize(Windows::Graphics::RectInt32{ 100, 300, 700, 900 });
        }


        void NavView_Loaded(Windows::Foundation::IInspectable const&,
            Microsoft::UI::Xaml::RoutedEventArgs const);
        void NavView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const&,
            Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const&);

        void scanner_GotFocus(winrt::Windows::Foundation::IInspectable, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void personnel_GotFocus(winrt::Windows::Foundation::IInspectable, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void logs_GotFocus(winrt::Windows::Foundation::IInspectable, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
