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

        winrt::hstring ScannedID();
        void ScannedID(winrt::hstring);

    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
