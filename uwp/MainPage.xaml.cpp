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
using namespace concurrency;
using namespace Windows::UI::Text;
using namespace Microsoft::UI::Xaml::Controls;


// La plantilla de elemento Página en blanco está documentada en https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0xc0a

MainPage::MainPage()
{
	InitializeComponent();
	this->NavigationCacheMode = Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled;
}

String^ mainfilename = "null";
constexpr int sizeOfpp = 5;
String^ pp[sizeOfpp];
unsigned int counter = 0;
StorageFile^ f;


StorageFile^ files[9];
unsigned int counterOfFile = 0;

//auto files = ref new Platform::Collections::Vector<StorageFile^ >;
 //StorageFile^ files[10];


void uwp::MainPage::a(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	TabViewItem^ tst = ref new TabViewItem();
	//tst->Content  = Frame->Navigate(Interop::TypeName(BlankPage::typeid));
	
	tst->Header = "abcd";
	
	tab->TabItems->Append(tst);
	/*
	* Test button for code
	* Down are trash lines
	* 
	Windows::UI::Color^ a = pickcolor->Color;
	SolidColorBrush^ aa = a;
	//textBox1->Background = pickcolor->Color;
	richEditBox->BorderBrush = aa;
	
	ITextSelection^ s = richEditBox->Document->Selection;
	//TextSetOptions a; 
	//ITextDocument^ ss = richEditBox->Document; ss->SetText(a,"aaa");
	//ITextDocument^ textt = richEditBox->TextDocument;
	//String^ aa = "a";
	//Documents::TextElement x;
	//directorio->Text =aa;

	ITextCharacterFormat^ txt = s->CharacterFormat;
	txt->ForegroundColor = pickcolor->Color;
	*/ 
}



void uwp::MainPage::ClickA(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{ 
	if (mode_pro->IsOn == true) {
		//ITextDocument^ textt = richEditBox->TextDocument;
		//auto textbox = textt->ToString();
		ITextSelection^ temptext = richEditBox->Document->Selection;
		String^ tempptext = temptext->Text;

		Pickers::FileSavePicker^ p = ref new Pickers::FileSavePicker();
		p->SuggestedFileName = "My best file ever and a super name of the word xD";
		//p->SuggestedStartLocation = KnownFolders::DocumentsLibrary;
	
		
		auto x = ref new Platform::Collections::Vector<String^>;
		x->Append(".txt");
		x->Append(".rtf");
      //  x->Append(".rtf");
		//x->Append(".cpp");
		//x->Append(".py");
		//x->Append(".js");
		//x->Append(".html");
         p->FileTypeChoices->Insert("text file and more (.txt , .rtf)", x);
		 
		create_task(p->PickSaveFileAsync()).then([this,tempptext](StorageFile^ file) {
			if (file != nullptr || counterOfFile <= 9) {
				f = file;
				CachedFileManager::DeferUpdates(file);
				if (new_fileTS->IsOn == false) {
					create_task(FileIO::WriteTextAsync(file, tempptext)).then([this, file]() {

						create_task(CachedFileManager::CompleteUpdatesAsync(file)).then([this, file](Provider::FileUpdateStatus status) {
							if (status == Provider::FileUpdateStatus::Complete) {
								//good
								textBlock->Text = file->Name;
								directorio->Text = file->Path;
								mainfilename = file->Name;

								files[counterOfFile] = file;
								tab->TabItems->Append(file->Name);
								counterOfFile++;

							}
							else {
								//bad
								//textBlock->Text = "error!";
								errormsg->Text = "Something go wrong";
								error_dialog->ShowAsync();
							}
							});
						});
				}
				else {
					textBlock->Text = file->Name;
					directorio->Text = file->Path;
					create_task(file->OpenAsync(FileAccessMode::ReadWrite)).then([this](Streams::IRandomAccessStream^ randd) {
						richEditBox->Document->SaveToStream(TextGetOptions::FormatRtf,randd);
						});
				}
			}
			else {
				//no file
				errormsg->Text = "Operation cancelled or the counter or files is max";
				error_dialog->ShowAsync();
				
			}

			});
	}
	else {
		dialogbox_pro1->ShowAsync();
	}
	
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
	if (mode_pro->IsOn == false) {
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
	else {
		if (f != nullptr) {
			try {
				//f
				create_task(files[tab->SelectedIndex]->OpenAsync(FileAccessMode::ReadWrite)).then([this](Streams::IRandomAccessStream^ randd) {
					richEditBox->Document->SaveToStream(TextGetOptions::FormatRtf, randd);
					
					});
			}
			catch (Exception^ e) {
				errormsg->Text = e->Message;
				error_dialog->ShowAsync(); 
				//if a file is open causes a error
				//class Exception did not work
			}
		}
		else {
			error_dialog->ShowAsync();
		}
	}
}


void uwp::MainPage::OnClickOpenFile(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (mode_pro->IsOn == true) {
		Pickers::FileOpenPicker^ opn = ref new Pickers::FileOpenPicker();
		opn->ViewMode = Pickers::PickerViewMode::Thumbnail;
		opn->SuggestedStartLocation = Pickers::PickerLocationId::DocumentsLibrary;
		opn->FileTypeFilter->Append(".txt");
		opn->FileTypeFilter->Append(".rtf");

		create_task(opn->PickSingleFileAsync()).then([this](StorageFile^ file) {
			if (file || counterOfFile <= 9) {
				
				textBlock->Text = file->Name;
				directorio->Text = file->Path;
				create_task(file->OpenAsync(FileAccessMode::Read)).then([file, this](Streams::IRandomAccessStream^ randd) {
					f = file;

					files[counterOfFile] = file;
				
					
						tab->TabItems->Append(file->Name);
						counterOfFile++;
					

					 richEditBox->Document->LoadFromStream(TextSetOptions::FormatRtf,randd);
					mainfilename = file->Name;
					
					
					//files->Append(file);

					});
			}
			else {
				//textBlock->Text = "error, cancelled operation";
				errormsg->Text = "Operation cancelled or the counter of files is max";
				error_dialog->ShowAsync();
			}
			});
	}
	else {
		open_file_popup->ShowAsync();
       }
}


void uwp::MainPage::OnClickOpenPopup(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
	mainfilename = filename2->Text;
	
	StorageFolder^ storageFolder = ApplicationData::Current->LocalFolder;
	try {
		
		String^ real = "null";
		
		/*
		 concurrency::create_task(storageFolder->GetFileAsync(mainfilename)).then([real](StorageFile^ sampleFile)
			{
				return FileIO::ReadTextAsync(sampleFile);
				
				 concurrency::create_task(FileIO::ReadTextAsync(sampleFile)).then([sampleFile , real](task<String^> task)
					{
						// real = task.get();
					});
					
			});
			*/
		
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
	if (mode_pro->IsOn == false) {
		pp[counter] = textBox1->SelectedText;
	}
	else {
		ITextSelection^ textS = richEditBox->Document->Selection;
		pp[counter] = textS->Text;
	}
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
	if (mode_pro->IsOn == false) {
		String^ txt = textBox1->Text + " " + pp[SelectedNumInInt];
		//dtext->Text = "Selected num: " + SelectedNum + " Selected num in int: " + SelectedNumInInt + " pp: " + pp[SelectedNumInInt] + " counter: " + counter;
		textBox1->Text = txt;
	}
	else {
		ITextSelection^ textS = richEditBox->Document->Selection;
		if (textS) {
			textS->Text = pp[SelectedNumInInt];
		}
		else {
			ITextDocument^ dd = richEditBox->Document;
			//String^ bbb = "sss";
			richEditBox->Document->SetText(TextSetOptions::FormatRtf, pp[SelectedNumInInt]);
			
		}
	}
}


void uwp::MainPage::OnClickCut(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (counter >= sizeOfpp)
	{
		counter = 0;
	}
	if (mode_pro->IsOn == false) {
		pp[counter] = textBox1->SelectedText;

		textBox1->Text = " ";
	}
	else {
		ITextSelection^ textS = richEditBox->Document->Selection;
		pp[counter] = textS->Text;
		textS->Text = "";
	}
	counter++;
}


void uwp::MainPage::OnClickBold(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;
		format->Bold = FormatEffect::Toggle;
		textS->CharacterFormat = format;
		
	}

}


void uwp::MainPage::OnClickItalic(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;
		format->Italic = FormatEffect::Toggle;
		textS->CharacterFormat = format;
	
	}
}


void uwp::MainPage::OnClickUnderline(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;

		
		//20
		double d = sliderUnd->Value;
		int ddd = d;
		
		/* for (int i = 0; i <= 20; i++) {
			if (slider->Value == i) {
				ddd = i;
			}
		}
		*/
		switch (ddd) {
		case(0):
			if (format->Underline == UnderlineType::None) {
				format->Underline = UnderlineType::Single;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(1): 
			if (format->Underline == UnderlineType::None)
			{
               format->Underline = UnderlineType::Dash;
			   
			}
			else {
				format->Underline = UnderlineType::None;
			}
			
			break;
		case(2):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::DashDot;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(3):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::DashDotDot;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(4):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Dotted;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(5):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Double;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(6):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::DoubleWave;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(7): 
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::HeavyWave;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(8):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::LongDash;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(9):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Thick;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(10): 
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::ThickDash;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(11):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::ThickDashDot;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(12):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::ThickDashDotDot;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(13):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::ThickDotted;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(14):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::ThickLongDash;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(15): 
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Thin;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(16): 
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Undefined;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(17): 
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Wave;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		case(18):
			if (format->Underline == UnderlineType::None)
			{
				format->Underline = UnderlineType::Words;
			}
			else {
				format->Underline = UnderlineType::None;
			}
			break;
		default: 
			format->Underline = UnderlineType::None;
			break;
			   
		}
		textS->CharacterFormat = format;
	}
}
/*
	if (format->Underline == UnderlineType::None)
		{

		}
		else {
			format->Underline = UnderlineType::None;
		}
*/

void uwp::MainPage::OnClickTxtColor(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;

		format->ForegroundColor = pickcolor->Color;
		textS->CharacterFormat = format;
	}
}


void uwp::MainPage::OnClickBackColor(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;

		format->BackgroundColor = pickcolor->Color;
		textS->CharacterFormat = format;
	}
}


void uwp::MainPage::OnClickIncrease(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;
		format->AllCaps = FormatEffect::Toggle;
		
		textS->CharacterFormat = format;
	}
}


void uwp::MainPage::OnClickDecrease(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		ITextCharacterFormat^ format = textS->CharacterFormat;
		format->SmallCaps = FormatEffect::Toggle;
		
		textS->CharacterFormat = format;
	}
}

//starts of weight text

void uwp::MainPage::click100(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 100;
}


void uwp::MainPage::click200(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 200;
}


void uwp::MainPage::click300(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 300;
}


void uwp::MainPage::click400(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 400;
}


void uwp::MainPage::click500(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 500;
}


void uwp::MainPage::click600(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 600;
}


void uwp::MainPage::click700(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 700;
}


void uwp::MainPage::click800(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 800;
}


void uwp::MainPage::click900(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	richEditBox->Document->Selection->CharacterFormat->Weight = 900;
}

//end of weight text

void uwp::MainPage::OnClickLink(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	ITextSelection^ textS = richEditBox->Document->Selection;
	if (textS != nullptr) {
		
		//try {
			Uri^ xd = ref new Uri("https://google.com");
			textS->Text = xd->DisplayUri;
		/*}
		catch (Platform::InvalidArgumentException^ ee) {
			errormsg->Text = ee->Message;
			error_dialog->ShowAsync();
			
		}
		*/
			
	}
}


void uwp::MainPage::OnClickRedo(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (richEditBox->Document->CanRedo() == true) {
		richEditBox->Document->Redo();
	}
	
}


void uwp::MainPage::OnClickUndo(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (richEditBox->Document->CanUndo() == true) {
		richEditBox->Document->Undo();
	}
}


void uwp::MainPage::OnClickAddTab(Microsoft::UI::Xaml::Controls::TabView^ sender, Platform::Object^ args)
{
	//Microsoft::UI::Xaml::Controls::TabViewItem^ tab = ref new Microsoft::UI::Xaml::Controls::TabViewItem();
	//tab->Header = "baxfsd";
	//sender->TabItems->SetAt(1, args); 
	
	sender->TabItems->Append("abc");
	
	
}


void uwp::MainPage::TabClose(Microsoft::UI::Xaml::Controls::TabView^ sender, Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs^ args)
{
	sender->TabItems->RemoveAt(sender->SelectedIndex);
}


void uwp::MainPage::OnSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (files[tab->SelectedIndex] != nullptr) {
		//put file text on richtextbox
		create_task(files[tab->SelectedIndex]->OpenAsync(FileAccessMode::Read)).then([this](Streams::IRandomAccessStream^ randd) {
			richEditBox->Document->LoadFromStream(TextSetOptions::FormatRtf, randd);
			});
		textBlock->Text = files[tab->SelectedIndex]->Name;
		directorio->Text = files[tab->SelectedIndex]->Path;
	} 
}
