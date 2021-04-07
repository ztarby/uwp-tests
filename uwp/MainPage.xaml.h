//
// MainPage.xaml.h
// Declaración de la clase MainPage.
//

#pragma once

#include "MainPage.g.h"



namespace uwp
{
	/// <summary>
	/// Página vacía que se puede usar de forma independiente o a la que se puede navegar dentro de un objeto Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void a(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ClickA(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickPrm1(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		
		void OnClickSaveFile(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickOpenFile(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickOpenPopup(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void OnClickCopy(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickPaste(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickCut(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickBold(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickItalic(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickUnderline(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickTxtColor(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickBackColor(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickIncrease(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickDecrease(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
