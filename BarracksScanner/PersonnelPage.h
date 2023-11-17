#pragma once

#include "PersonnelPage.g.h"

namespace winrt::BarracksScanner::implementation
{
    struct PersonnelPage : PersonnelPageT<PersonnelPage>
    {
        PersonnelPage() 
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
    struct PersonnelPage : PersonnelPageT<PersonnelPage, implementation::PersonnelPage>
    {
    };
}
