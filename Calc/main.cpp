#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<Windows.h>
#include<cstdio>
#include<iostream>
#include"resource.h"

//#define DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define g_i_INTERVAL				 2
#define g_i_BUTTON_SIZE				50
#define g_i_DOUBLE_BUTTON_SIZE		g_i_BUTTON_SIZE * 2 + g_i_INTERVAL
		  
#define g_i_START_X					10
#define g_i_START_Y					10
#define g_i_DISPLAY_WIDTH			g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4
#define g_i_DISPLAY_HEIGHT			22

#define g_i_BUTTON_START_X			g_i_START_X
#define g_i_BUTTON_START_Y			g_i_START_Y+g_i_DISPLAY_HEIGHT+g_i_INTERVAL

#define BUTTON_X_POSITION(SHIFT)	g_i_BUTTON_START_X + (g_i_BUTTON_SIZE+g_i_INTERVAL)*(SHIFT)
#define BUTTON_Y_POSITION(SHIFT)	g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE+g_i_INTERVAL)*(SHIFT)

#define g_i_WINDOW_WIDTH			g_i_DISPLAY_WIDTH + g_i_START_X*2 + 16
#define g_i_WINDOW_HEIGHT			g_i_DISPLAY_HEIGHT + g_i_START_Y*2 + (g_i_BUTTON_SIZE + g_i_INTERVAL)*4 + 38 // 38 высота строки заголовка

#define img_RESIZE(size)			(size) - 4


#define teame_SquareBlue	(LPSTR)"square_blue/"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

static LPSTR teame = teame_SquareBlue;

CONST CHAR g_OPERATORS[] = "+-*/";
CONST CHAR g_sz_WINDOW_CLASS[] = "Calc PV_522";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
HBITMAP get_image(const size_t& ResourceID, const int& width, const int& height);
void new_teame(HWND& hwnd, const LPSTR& _teame);

LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if(not RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while(GetMessage(&msg , NULL , 0 , 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//3) Запуск цикла окна сообщенией:
	return msg.wParam;
}

LRESULT WndProc(HWND hwnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
{ 
	switch(uMsg)
	{
	case WM_CREATE:
	{
#ifdef DEBUG
		AllocConsole();
#endif // DEBUG
		freopen("CONOUT$","w", stdout);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		CHAR sz_digit[2] = {};
		int but = 0;
		for(int i = 6; i >=0 ; i-=3)
		{
			for(int j = 0;j < 3;++j)
			{
				sz_digit[0] = '1' + i + j;
				HWND hButton = CreateWindowEx
				(
					NULL,"Button",NULL,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
					BUTTON_X_POSITION(j), BUTTON_Y_POSITION(2 - i / 3),
					g_i_BUTTON_SIZE,g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1+i+j),
					GetModuleHandle(NULL),
					NULL
				);
				LPARAM l_Image = (LPARAM)get_image(IDC_BUTTON_1+i+j, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE);
				SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, l_Image);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND hButton0 =CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_BUTTON_START_X ,BUTTON_Y_POSITION(3),
			g_i_DOUBLE_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		LPARAM l_Image0 = (LPARAM)get_image(IDC_BUTTON_0, g_i_DOUBLE_BUTTON_SIZE, g_i_BUTTON_SIZE);
		SendMessage(hButton0, BM_SETIMAGE, IMAGE_BITMAP, l_Image0);
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND hButtonPoint = CreateWindowEx
		(
			NULL, "Button", NULL,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_X_POSITION(2), BUTTON_Y_POSITION(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		LPARAM l_ImagePoint = (LPARAM)get_image(IDC_BUTTON_POINT, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE);
		SendMessage(hButtonPoint, BM_SETIMAGE, IMAGE_BITMAP, l_ImagePoint);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		CHAR sz_operation[2] = {};
		for(int i = 0; i < 4;++i)
		{
			sz_operation[0]= g_OPERATORS[3-i];
			HWND hButton = CreateWindowEx
			(
				NULL, "Button", sz_operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				BUTTON_X_POSITION(3), BUTTON_Y_POSITION(i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_SLASH-i),
				GetModuleHandle(NULL),
				NULL
			);
			LPARAM l_Image = (LPARAM)get_image(IDC_BUTTON_SLASH - i , g_i_BUTTON_SIZE, g_i_BUTTON_SIZE);
			SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, l_Image);
			
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND hButtonBsp = CreateWindowEx // BSP
		(
			NULL , "Button" , NULL,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_X_POSITION(4) , BUTTON_Y_POSITION(0),
			g_i_BUTTON_SIZE , g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		LPARAM l_ImageBsp = (LPARAM)get_image(IDC_BUTTON_BSP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE);
		SendMessage(hButtonBsp, BM_SETIMAGE, IMAGE_BITMAP, l_ImageBsp);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND hButtonClr = CreateWindowEx	//CLR
		(
			NULL , "Button" , NULL,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_X_POSITION(4) , BUTTON_Y_POSITION(1),
			g_i_BUTTON_SIZE,g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		LPARAM l_ImageClr = (LPARAM)get_image(IDC_BUTTON_CLR, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE);
		SendMessage(hButtonClr, BM_SETIMAGE, IMAGE_BITMAP, l_ImageClr);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND hButtonEqual = CreateWindowEx // EQUAL
		(
			NULL , "Button" , NULL ,
			WS_CHILD | WS_VISIBLE  | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_X_POSITION(4), BUTTON_Y_POSITION(2),
			g_i_BUTTON_SIZE, g_i_DOUBLE_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		LPARAM l_ImageEqual = (LPARAM)get_image(IDC_BUTTON_EQUAL, g_i_BUTTON_SIZE, g_i_DOUBLE_BUTTON_SIZE);
		SendMessage(hButtonEqual, BM_SETIMAGE, IMAGE_BITMAP, l_ImageEqual);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
		break;
	case WM_COMMAND:
	{
		static DOUBLE	a = DBL_MIN, b = DBL_MIN; // DBL_MIN = -(2^64)/2
		static INT		operation = 0;
		static BOOL		input = FALSE; // Отслеживает ввод цифр
		static BOOL		input_operation = FALSE; // Отслежвает ввод операции
		static BOOL		executed = FALSE;

		//static INT		op_buf_SIZE = 0;
		//static INT		op_buffer[MAX_PATH] = {};


		CHAR sz_digit[2] = {};
		CHAR sz_display[MAX_PATH] = {};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
		SendMessage(hEditDisplay, WM_GETTEXT, MAX_PATH, (LPARAM)sz_display);

		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			input_operation = FALSE;
			executed = FALSE;

			if (input == FALSE)ZeroMemory(sz_display, sizeof(sz_display));
			
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';

			if (sz_display[0] == '0' && sz_display[1] != '.')
				strcpy(sz_display, sz_digit);
			else
				strcat(sz_display, sz_digit);

			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
			break;
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			input_operation = FALSE;
			if (strchr(sz_display, '.'))break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
			break;
		}
		/*
		void (*add_simbol)(HWND&, CHAR*, const CHAR*) = [](HWND& hEditDisplay, CHAR* sz_display, const CHAR* str)
			{
				strcat(sz_display, str);
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			};

		
		case IDC_BUTTON_ASTER:	add_simbol(hEditDisplay, sz_display, "*");	break;
		case IDC_BUTTON_SLASH:	add_simbol(hEditDisplay, sz_display, "/");	break;
		case IDC_BUTTON_PLUS:	add_simbol(hEditDisplay, sz_display, "+");	break;
		case IDC_BUTTON_MINUS:	add_simbol(hEditDisplay, sz_display, "-");	break;
		*/
		if(LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			sz_display[lstrlen(sz_display) - 1] = 0;
			if (sz_display[0] == 0)sz_display[0] = '0';
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			break;
		}
		if(LOWORD(wParam) ==  IDC_BUTTON_CLR)
		{
			a = DBL_MIN, b = DBL_MIN; // -(2^64)/2
			operation = 0;
			input = FALSE;
			input_operation = FALSE;
			executed = FALSE;

			/*op_buf_SIZE = 0;
			for (int i = 0; i < op_buf_SIZE; ++i)
				op_buffer[i] = 0;*/

			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
#ifdef DEBUG
			std::cout << "------------------------------------------------\n\n";
			std::cout << "OPERATION BUTTONS:\n";
			std::cout << "a = " << a << "\tb = " << b << std::endl;
			std::cout << "Input:\t\t" << input << std::endl;
			std::cout << "InputOperation:\t" << input_operation << std::endl;
			std::cout << "Executed:\t" << executed << std::endl;
			std::cout << "\n------------------------------------------------\n";
#endif // DEBUG
			if(input)
			{
				(a == DBL_MIN ? a : b) = atof(sz_display);
				input = FALSE;
			}
			if(not input_operation && not executed)SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			operation = LOWORD(wParam);
			//op_buffer[op_buf_SIZE++] = LOWORD(wParam);
			input_operation = TRUE;
			
		}
		if(LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
#ifdef DEBUG
			std::cout << "------------------------------------------------\n\n";
			std::cout << "EQUAL BUTTON:\n";
			std::cout << "a = " << a << "\tb = " << b << std::endl;
			std::cout << "Input:\t\t" << input << std::endl;
			std::cout << "InputOperation:\t" << input_operation << std::endl;
			std::cout << "Executed:\t" << executed << std::endl;
			std::cout << "\n------------------------------------------------\n";
#endif // DEBUG

			if(input)
			{
				(a == DBL_MIN ? a : b) = atof(sz_display);
				input = FALSE;
			}

			//if(operation && a == DBL_MIN)a = atof(sz_display);
			
			//for (int i = 0; i < op_buf_SIZE; ++i)
			//{
			if (a != DBL_MIN && operation != 0)
			{
				if (b == DBL_MIN)b = a;
				//for (int i = 0; i < op_buf_SIZE; ++i)
				//
				switch (operation)//switch (op_buffer[i])
				{
				case IDC_BUTTON_PLUS:	a += b;	break;
				case IDC_BUTTON_MINUS:	a -= b;	break;
				case IDC_BUTTON_ASTER:	a *= b;	break;
				case IDC_BUTTON_SLASH:	a /= b;	break;
				}
				//}
				/*op_buffer[0] = op_buffer[op_buf_SIZE - 1];
				for (op_buf_SIZE; op_buf_SIZE > 1; --op_buf_SIZE)
					op_buffer[op_buf_SIZE-1] = 0;*/

				input_operation = FALSE;
				executed = TRUE;
				if (a != DBL_MIN)
				{
					sprintf(sz_display, "%g", a);
					SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
				}
			}
			//}
			/*op_buffer[0] = op_buffer[op_buf_SIZE - 1];
			for (op_buf_SIZE; op_buf_SIZE > 1; --op_buf_SIZE)
				op_buffer[op_buf_SIZE-1] = 0;*/

			input_operation = FALSE;
			executed = TRUE;
			if (a != DBL_MIN) 
			{
				sprintf(sz_display, "%g", a);
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}
		}
		SetFocus(hwnd);
	}
	break;
	case WM_KEYDOWN:
	{
#ifdef DEBUG
		CHAR sz_key[8] = {};
		sprintf(sz_key, "%i", wParam);
		std::cout << sz_key << '\n';
#endif // DEBUG

		if (GetKeyState(VK_LSHIFT) < 0)
		{
			if (wParam == '8')
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, NULL);
				break;
			}
			if (wParam == VK_OEM_PLUS)
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, NULL);
				break;
			}
		}
		if (wParam >= '0' &&  wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, NULL);
			break;
		}
		if (wParam >= VK_NUMPAD0 && wParam <= VK_NUMPAD9)
		{
			SendMessage(GetDlgItem(hwnd, wParam - VK_NUMPAD0 + IDC_BUTTON_0), BM_SETSTATE, TRUE, NULL);
			break;
		}
		
		switch(wParam)
		{
		case VK_BACK:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, NULL);		break;
		case VK_ESCAPE:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0);		break;
		case VK_MULTIPLY:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);		break;
		case VK_DIVIDE:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0);		break;
		case VK_OEM_PLUS:
		case VK_RETURN:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0);		break;
		case VK_ADD:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0);		break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0);		break;
		case VK_OEM_PERIOD:
		case VK_DECIMAL:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0);		break;
		}
		
	}
	break;
	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == '8')
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, NULL);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
				break;
			}
			if (wParam == VK_OEM_PLUS)
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, NULL);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
				break;
			}
		}
		if(wParam >= '0' && wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, NULL);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - '0' + IDC_BUTTON_0), 0);
			break;
		}
		if (wParam >= VK_NUMPAD0 && wParam <= VK_NUMPAD9)
		{
			SendMessage(GetDlgItem(hwnd, wParam - VK_NUMPAD0 + IDC_BUTTON_0), BM_SETSTATE, FALSE, NULL);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - VK_NUMPAD0 + IDC_BUTTON_0), 0);
			break;
		}
		void (*sendCommand)(HWND&, const size_t) = [](HWND& hwnd, const size_t ResourceID)
			{
				SendMessage(GetDlgItem(hwnd, ResourceID), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(ResourceID), 0);
			};
		switch (wParam)
		{
		case VK_BACK:		sendCommand(hwnd, IDC_BUTTON_BSP);		break;
		case VK_ESCAPE:		sendCommand(hwnd , IDC_BUTTON_CLR);		break;
		case VK_MULTIPLY:	sendCommand(hwnd, IDC_BUTTON_ASTER);	break;
		case VK_OEM_2:
		case VK_DIVIDE:		sendCommand(hwnd, IDC_BUTTON_SLASH);	break;
		case VK_OEM_PLUS:
		case VK_RETURN:		sendCommand(hwnd, IDC_BUTTON_EQUAL);	break;
		case VK_ADD:		sendCommand(hwnd, IDC_BUTTON_PLUS);		break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:	sendCommand(hwnd, IDC_BUTTON_MINUS);	break;
		case VK_OEM_PERIOD:
		case VK_DECIMAL:	sendCommand(hwnd, IDC_BUTTON_POINT);	break;
		}
		if (wParam == VK_SPACE)
		{
			CHAR sz_display[MAX_PATH] = {};
			HWND hEditDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
			SendMessage(hEditDisplay, WM_GETTEXT, MAX_PATH, (LPARAM)sz_display);
			strcat(sz_display, " ");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			break;
		}
	}
	break;
	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}
HBITMAP get_image(const size_t& ResourceID, const int& width, const int& height)
{
	CHAR directory[MAX_PATH] = "images/";
	strcat(directory, teame);

	CHAR resource[MAX_PATH] = {};

	if (ResourceID >= IDC_BUTTON_0 && ResourceID <= IDC_BUTTON_9)
		wsprintf(resource, "button_%d.bmp", ResourceID - IDC_BUTTON_0);

	else
		switch (ResourceID)
		{
		case IDC_BUTTON_POINT:	strcpy(resource, "button_point.bmp");	break;
		case IDC_BUTTON_PLUS:	strcpy(resource, "button_plus.bmp");	break;
		case IDC_BUTTON_MINUS:	strcpy(resource, "button_minus.bmp");	break;
		case IDC_BUTTON_ASTER:	strcpy(resource, "button_aster.bmp");	break;
		case IDC_BUTTON_SLASH:	strcpy(resource, "button_slash.bmp");	break;

		case IDC_BUTTON_BSP:	strcpy(resource, "button_bsp.bmp");		break;
		case IDC_BUTTON_CLR:	strcpy(resource, "button_clr.bmp");		break;
		case IDC_BUTTON_EQUAL:	strcpy(resource, "button_equal.bmp");	break;
		}

	CHAR path[MAX_PATH] = {};
	wsprintf(path, "%s%s", directory, resource);

	return (HBITMAP)LoadImage
	(
		GetModuleHandle(NULL),
		path,
		IMAGE_BITMAP,
		img_RESIZE(width),
		img_RESIZE(height),
		LR_LOADFROMFILE
	);
}
void new_teame(HWND& hwnd,const LPSTR& _teame)
{
	teame = _teame;
	for (int i = 0; i <= IDC_BUTTON_9 - IDC_BUTTON_1; ++i)
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_1 + i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)get_image(IDC_BUTTON_1 + i , g_i_BUTTON_SIZE , g_i_BUTTON_SIZE));
	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)get_image(IDC_BUTTON_0 , g_i_DOUBLE_BUTTON_SIZE , g_i_BUTTON_SIZE));
	
	for(int i =0;i<=IDC_BUTTON_CLR - IDC_BUTTON_POINT;++i)
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT + i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)get_image(IDC_BUTTON_POINT+i, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE));
	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)get_image(IDC_BUTTON_EQUAL , g_i_BUTTON_SIZE  , g_i_DOUBLE_BUTTON_SIZE));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////