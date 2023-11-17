#pragma once

#include "LogsPage.g.h"

namespace winrt::BarracksScanner::implementation
{
    struct LogsPage : LogsPageT<LogsPage>
    {
        LogsPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct LogsPage : LogsPageT<LogsPage, implementation::LogsPage>
    {
    };
}
