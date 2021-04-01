//
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

using namespace Windows::Storage;

// La plantilla de elemento Página en blanco está documentada en https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0xc0a

MainPage::MainPage()
{
	InitializeComponent();
	
}

String^ mainfilename = "null";
constexpr int sizeOfpp = 5;
String^ pp[sizeOfpp];
int counter = 0;

void uwp::MainPage::a(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	textBox1->Text = "osoaosoo";
	
}



void uwp::MainPage::ClickA(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{ 
	dialogbox_pro1->ShowAsync();
	
}


void uwp::MainPage::OnClickPrm1(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
	String^ a = filename->Text;
	
	StorageFolder^ storageFolder = ApplicationData::Current->LocalFolder;
	concurrency::create_task(storageFolder->CreateFileAsync(a, CreationCollisionOption::ReplaceExisting));
	
	textBlock->Text = a;
	directorio->Text = storageFolder->Path;

	//StorageFolder^ ss = KnownFolders::DocumentsLibrary;
	//KnownFolders::DocumentsLibrary->CreateFileAsync("aaaa");
	mainfilename = a;
}


void uwp::MainPage::OnClickSaveFile(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (mainfilename == "null") {
		
	}
	else {

		String^ ffile = textBox1->Text;

		StorageFolder^ storageFolder = ApplicationData::Current->LocalFolder;
		concurrency::create_task(storageFolder->GetFileAsync(mainfilename)).then([ffile](StorageFile^ sampleFile)
			{
			
				concurrency::create_task(FileIO::WriteTextAsync(sampleFile, ffile));
			});
	}
}


void uwp::MainPage::OnClickOpenFile(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	open_file_popup->ShowAsync();
}


void uwp::MainPage::OnClickOpenPopup(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
	mainfilename = filename2->Text;
	
	StorageFolder^ storageFolder = ApplicationData::Current->LocalFolder;
	try {
		
		String^ real;

		concurrency::create_task(storageFolder->GetFileAsync(mainfilename)).then([](StorageFile^ sampleFile)
			{
				return FileIO::ReadTextAsync(sampleFile);

			});
		
		
        textBox1->Text = real;
	}
	catch (Exception^ a) {

	}

	textBlock->Text = mainfilename;
	directorio->Text = storageFolder->Path;
	
	
}



void uwp::MainPage::OnClickCopy(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if(counter >= sizeOfpp)
	{
		counter = 0;
	}
	pp[counter] = textBox1->SelectedText;
	counter++;
}


void uwp::MainPage::OnClickPaste(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	double SelectedNum = slider->Value;
	int SelectedNumInInt = 0;
	for (int i = 0; i <= sizeOfpp; i++) {

		if (SelectedNum == i) {
			SelectedNumInInt = i;
		}
	}
	String^ txt = textBox1->Text + " " + pp[SelectedNumInInt];
	dtext->Text = "Selected num: " + SelectedNum + " Selected num in int: " + SelectedNumInInt + " pp: " + pp[SelectedNumInInt] + " counter: " + counter;
	textBox1->Text = txt;
}


void uwp::MainPage::OnClickCut(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (counter >= sizeOfpp)
	{
		counter = 0;
	}
	pp[counter] = textBox1->SelectedText;

	textBox1->Text = " ";
	counter++;
}
