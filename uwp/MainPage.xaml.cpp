﻿//
// MainPage.xaml.cpp
// Implementación de la clase MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace uwp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// La plantilla de elemento Página en blanco está documentada en https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0xc0a

MainPage::MainPage()
{
	InitializeComponent();
	
}


void uwp::MainPage::a(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textBox1->Text = "osoaosoo";
	//ContentDialog a;
	//ContentDialog^ e = ref new ContentDialog(); 
}



void uwp::MainPage::ClickA(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{ 
	dialogbox_pro1->ShowAsync();
	
}
