//
// AddPerson.xaml.h
// Declaration of the AddPerson class
//

#pragma once

#include "AddPerson.g.h"

namespace BarracksScanner
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AddPerson sealed
	{
	public:
		AddPerson();
	private:
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
	};
}
