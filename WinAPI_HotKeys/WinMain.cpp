#include <windows.h>
#include "resource.h"
#include <Richedit.h> 
#include <string>

BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char WinName[] = "MainFrame";

long double font=-1;
long double size=-1;

CHOOSECOLOR clr;

HWND hEdit=(HWND)(LoadLibrary("riched32.dll"));

static COLORREF acrCustClr[16];
static DWORD rgbCurrent;

//HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE This,			// Дескриптор текущего приложения
	HINSTANCE Prev,							// В современных системах всегда 0
	LPTSTR cmd,								// Командная строка
	int mode)								// Режим отображения окна
{
	
	HACCEL hAccel;  

	hAccel = LoadAccelerators(This , MAKEINTRESOURCE(IDR_ACCELERATOR1) );

	HWND hWnd;									// Дескриптор главного окна программы
	MSG msg;									// Структура для хранения сообщения
	WNDCLASS wc;								// Класс окна

													// Определение класса окна	
	wc.hInstance = This;		
	wc.lpszClassName = WinName;						// Имя класса окна
	wc.lpfnWndProc = WndProc;						// Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW;				// Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// Стандартная иконка
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);		// Стандартный курсор
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	
	wc.cbClsExtra = 0;								// Нет дополнительных данных класса
	wc.cbWndExtra = 0;								// Нет дополнительных данных окна


	//============ Заполнение окна цветом===============
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	if(!RegisterClass(&wc)) return 0;		// Регистрация класса окна 


											//Создание окна


	hWnd = CreateWindow(WinName,			// Имя класса окна
	"PPV 23-01 First WinApi APP",			// Заголовок окна
	WS_OVERLAPPEDWINDOW,					// Стиль окна
	CW_USEDEFAULT,							// x
	CW_USEDEFAULT,							// y	Размеры окна
	CW_USEDEFAULT,							// Width
	CW_USEDEFAULT,							// Height
	HWND_DESKTOP,							// Дескриптор родительского окна
	NULL,									// Нет меню
	This,									// Дескриптор приложения
	NULL);									// Дополнительной информации нет
		
	ShowWindow(hWnd, mode);					//Показать окно

	//============ Цикл обработки сообщений============

	clr.lStructSize=sizeof(clr);
	clr.hwndOwner=hWnd;
	clr.lpCustColors = (LPDWORD) acrCustClr;
	clr.Flags = CC_FULLOPEN | CC_RGBINIT;
	clr.rgbResult=rgbCurrent;

	while (GetMessage(&msg, NULL, 0, 0))  {
		// Если сообщение не от быстрой клавиши,
		// то выполнить стандартную обработку
		if (!TranslateAccelerator(hWnd, hAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//while(GetMessage(&msg, NULL, 0, 0))
	//{
	//	TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши
	//	DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	//}
	return 0;
}


// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CHARFORMAT cf;
	switch (uMsg) 
	{
		case WM_INITDIALOG:{
			SendDlgItemMessage(hDlg, IDC_COMBO1, (UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) "+"); 
			SendDlgItemMessage(hDlg, IDC_COMBO1, (UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) "-"); 
			SendDlgItemMessage(hDlg, IDC_COMBO1, CB_SETCURSEL,(WPARAM) -1,(LPARAM) 0); 
			SendDlgItemMessage(hDlg, IDC_COMBO2, (UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) "bold"); 
			SendDlgItemMessage(hDlg, IDC_COMBO2, (UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) "italic"); 
			SendDlgItemMessage(hDlg, IDC_COMBO2, CB_SETCURSEL,(WPARAM) -1,(LPARAM) 0); 
			break;
		}
		case WM_CREATE:{

			break;
		}
		case WM_PAINT:{
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam)) 
			{
				case IDOK:	{
					EndDialog(hDlg, NULL); 
					return 1;
				}
				 case IDCANCEL:{
					EndDialog(hDlg, NULL); 
					return 0;
				 }
				case IDC_BUTTON1:{
					cf.cbSize=sizeof(cf);
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					cf.dwMask=CFE_ITALIC;
					cf.dwEffects ^=CFE_ITALIC;
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					break;
				}
				case IDC_BUTTON2:{
					cf.cbSize=sizeof(cf);
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					cf.dwMask=CFE_BOLD;
					cf.dwEffects ^=CFE_BOLD;
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					break;
				}
				case IDC_BUTTON3:{
					cf.cbSize=sizeof(cf);
					/*SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD , (LPARAM)&cf);*/
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETFONTSIZE, 1, NULL);
					break;
				}
				case IDC_BUTTON4:{
					cf.cbSize=sizeof(cf);
					/*SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD , (LPARAM)&cf);*/
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETFONTSIZE, -1, NULL);
					break;
				}
				case IDC_BUTTON5:{
					cf.cbSize=sizeof(cf);
					char buff[MAX_PATH];
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, WM_GETTEXT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					GetDlgItemText(hDlg, IDC_RICHEDIT21, buff, 256);
					MessageBox(0, buff, "buffer", MB_OK);
					break;
				}
				case IDC_BUTTON6:{
					if(font==0){
						/*MessageBox(0, "bold", "BOLD", 0);*/
						cf.cbSize=sizeof(cf);
						SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
						cf.dwMask=CFE_BOLD;
						cf.dwEffects ^=CFE_BOLD;
						SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					}
					if(size==0){
						/*MessageBox(0, "-", "-", 0);*/
						cf.cbSize=sizeof(cf);
						SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETFONTSIZE, -1, NULL);
					}
					if(font==1){
						/*MessageBox(0, "italic", "ITALIC", 0);*/
						cf.cbSize=sizeof(cf);
						SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
						cf.dwMask=CFE_ITALIC;
						cf.dwEffects ^=CFE_ITALIC;
						SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					}
					if(size==1){
						/*MessageBox(0, "+", "+", 0);*/
						cf.cbSize=sizeof(cf);
						SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETFONTSIZE, 1, NULL);
					}
					break;
				}
				case IDC_BUTTON7:{
					cf.cbSize=sizeof(cf);
					ChooseColor(&clr);
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_GETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					cf.dwMask=CFM_COLOR;		
					cf.dwEffects=!CFE_AUTOCOLOR;
					cf.crTextColor=clr.rgbResult;
					SendDlgItemMessage(hDlg, IDC_RICHEDIT21, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD ,(LPARAM)&cf);
					break;
				}
				case WM_CLOSE: {  
					SendMessage(hDlg, WM_COMMAND, IDCANCEL, 0);   
					return 1;
				}
			}
			if(HIWORD(wParam) == CBN_SELCHANGE){
				//std::string str;
				//str=std::to_string((long double)HIWORD(lParam));
				//MessageBox(0, str.c_str(), "lParam", 0);
				//str=std::to_string((long double)uMsg);
				//MessageBox(0, str.c_str(), "uMsg", 0);
				//str=std::to_string((long double)HIWORD(wParam));	
				//MessageBox(0, str.c_str(), "wParam", 0);
				switch (LOWORD(wParam)){
					case IDC_COMBO1:{
						size=SendDlgItemMessage(hDlg, IDC_COMBO1, (UINT) CB_GETCURSEL,(WPARAM) 0,(LPARAM) 0); 
						//std::string str=std::to_string((long double)size);
						//MessageBox(0, str.c_str(), "size", 0);
						//break;
									}
					case IDC_COMBO2:{
						font=SendDlgItemMessage(hDlg, IDC_COMBO2, (UINT) CB_GETCURSEL,(WPARAM) 0,(LPARAM) 0); 
						//std::string str=std::to_string((long double)font);
						//MessageBox(0, str.c_str(), "font", 0);
						break;
									}
				}
			}
		}
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
				 WPARAM wParam, LPARAM lParam)
{	
	static HINSTANCE hInst;
	// Обработчик сообщений
	switch(message)
	{
		
		case WM_DESTROY :           // Завершение программы
			PostQuitMessage(0); 
			break; 
		
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_ACCELERATOR40001:
					MessageBox(NULL, "HOT KEYS SPACE", "HOT KEYS", MB_OK);
					break;

				
				case ID_ACCELERATOR40004:
					MessageBox(NULL, "HOT KEYS B'", "HOT KEYS", MB_OK);
					break;

				case ID_ACCELERATOR40005:
					MessageBox(NULL, "Create New File", "New File", MB_OK);
					break;
				case ID_ACCELERATOR40007:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
					break;

				case ID_EDITOR:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
					break;
			}
		}
		case WM_LBUTTONDOWN:

			//SetWindowPos(hWnd, HWND_TOP, 10,10,200,200, SWP_SHOWWINDOW);
		
			break; 

		case WM_RBUTTONDOWN:
			MessageBox(NULL, "Hello, World", "SIMPLE_M_BOX", MB_OK);
			SetWindowText(hWnd, "NEW TEXT");
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
	//return 0;
}

//Undo-Redo