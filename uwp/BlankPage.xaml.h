//
// BlankPage.xaml.h
// Declaración de la clase BlankPage.
//

#pragma once

#include "BlankPage.g.h"
#include "MainPage.xaml.h"

namespace uwp
{
	/// <summary>
	/// Una página vacía que se puede usar de forma independiente o a la que se puede navegar dentro de un objeto Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BlankPage sealed
	{
	public:
		BlankPage();
	private:
		void Return(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
