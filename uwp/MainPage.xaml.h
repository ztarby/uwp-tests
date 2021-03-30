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
	};
}
