#pragma once

#include "PersonnelPage.g.h"

namespace winrt::BarracksScanner::implementation
{
    struct PersonnelPage : PersonnelPageT<PersonnelPage>
    {
        std::string query;

        PersonnelPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void FilterTextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void PageLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RefreshPersonnel();
        void ClearColumns();
        void FilterCheckChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct PersonnelPage : PersonnelPageT<PersonnelPage, implementation::PersonnelPage> {
    };
}
