#include<Windows.h>
#include"resource.h"


CONST CHAR g_sz_INVITE[] = "Введите имя пользователя.";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstace , HINSTANCE hPrevInst , LPSTR lpCmdLine , INT nCmdShow)
{
	DialogBoxParam(hInstace, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	
	switch (uMsg)
	{	
	case WM_INITDIALOG:// Инициализация окна диалога . Эта секция отрабатывает 1 раз при  запуске окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);

		SendMessage(hwnd , WM_SETICON , 0 , (LPARAM)hIcon);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"Введите имя пользователя.");
	}
		break;
	case WM_COMMAND: // В этой секции обрабытывается нажатия кнопок , клавиш и другие события

		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			INT textLength = GetWindowTextLength(hEditLogin);
			
			/*
			CONST INT SIZE = 256;
			CHAR text[SIZE] = {};
			GetWindowText(hEditLogin, text, SIZE);
			*/

			if (textLength == 0)
			{
				if (HIWORD(wParam) == EN_SETFOCUS)
					SendMessage(hEditLogin, WM_SETTEXT, 0 ,(LPARAM)"");

				else if (HIWORD(wParam) == EN_KILLFOCUS)
					SendMessage(hEditLogin, WM_SETTEXT, 0 , (LPARAM)"Введите имя пользователя.");
			}
			
		}
		break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};

			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			
			SendMessage(hEditLogin, WM_GETTEXT , SIZE , (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;

		case IDOK: break; //MessageBox(hwnd, "была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0);
		
		}

		break;
	case WM_CLOSE: // Отрабатывает 1 раз при закрытии окна
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
