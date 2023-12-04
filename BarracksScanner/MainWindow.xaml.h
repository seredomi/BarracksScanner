#pragma once

#include "MainWindow.g.h"
#include "pch.h"

namespace winrt::BarracksScanner::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
			AppWindow().SetIcon(L"transparent-square.ico");
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
