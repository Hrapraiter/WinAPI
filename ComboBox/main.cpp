#undef UNICODE
#include <Windows.h>
#include"resource.h"

CONST CHAR* g_sz_buffer[] = {"This" , "is" , "Combo" , "Box"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1) , NULL , (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO_BOX);
	INT i = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

	switch(uMsg)
	{
	case WM_INITDIALOG:
	{
		for (int i = 0; i < sizeof(g_sz_buffer) / sizeof(g_sz_buffer[0]); ++i)
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)g_sz_buffer[i]);
	}
		break;
	case WM_COMMAND:
		switch(LPARAM(wParam))
		{
		case IDC_BUTTON_DELETE:
			SendMessage(hComboBox, CB_DELETESTRING, i, 0);
			break;
		case IDOK:
		{
			if(i != -1)
			{
				CHAR lb_buffer[MAX_PATH] = {};
				CHAR i_str[MAX_PATH] = {};
				SendMessage(hComboBox, CB_GETLBTEXT, i, (LPARAM)lb_buffer);
								
				wsprintf(lb_buffer, "%s%s%d", lb_buffer, " : ", i);

				MessageBox(hwnd, lb_buffer , "Info", MB_OK | MB_ICONINFORMATION);
				break;
			}
			MessageBox(hwnd, "элемент не выбран.", "Warning", MB_OK | MB_ICONWARNING);
		}
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}


	return FALSE;
}