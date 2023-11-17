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
        }

        hstring ScannedID();
        void ScannedID(hstring);

        void NavView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender,
            Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

        // void ContentFrame_NavigationFailed(Microsoft::UI::Xaml::Controls::NavigationView const& sender,
        //     Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
