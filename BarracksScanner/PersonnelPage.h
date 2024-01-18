#pragma once

#include "PersonnelPage.g.h"
#include <set>

namespace winrt::BarracksScanner::implementation
{
    struct PersonnelPage : PersonnelPageT<PersonnelPage>
    {
        std::string query;
        std::string match;
        std::set<std::string> groupMatches;
        std::string order;

        PersonnelPage() {
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void FilterCheckChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PageLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RefreshPersonnel();
        void BuildQuery();
        void BuildCreate();
        void VerifyInput();
        void ResidentCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ResidentCheck_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RotationalUnitCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RotationalUnitCheck_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void HotelDivartyCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void HotelDivartyCheck_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ChainOfCommandCheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ChainOfCommandCheck_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        static void PersonButtonPointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void PersonnelSearch_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
        void SortRadioChecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void NewPerson_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PersonInfo_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void PersonInfo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void PersonInfo_DateChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::DatePickerValueChangedEventArgs const& e);
        void PersonnelPage::PersonInfoError(Microsoft::UI::Xaml::Controls::Control, hstring);
        void PersonInfo_Closed(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogClosedEventArgs const& args);
        void PersonInfo_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
    };
}

namespace winrt::BarracksScanner::factory_implementation
{
    struct PersonnelPage : PersonnelPageT<PersonnelPage, implementation::PersonnelPage> {
    };
}
