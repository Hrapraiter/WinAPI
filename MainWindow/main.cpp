#undef UNICODE
#include<Windows.h>


CONST CHAR g_sz_CLASS_NAME[] = "Main Window PV_522";// Имя класса окна

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, INT nCmdShow)
{
	/*
	--------------------------------------------------------
	hInstance - это экземпляр  *.exe-файла нашей программы, загруженный в ОЗУ;
	hPrevInst - предыдущий загруженный экземпляр. В современный OC Windows этот параметр НЕ используется;
	LPSTR - LongPointer to STRing;
	lpCmdLine - это командная строка с которой запустилась программа. При запуске без параметров
				в lpCmdLine хранится только имя исполняемого файла программы.
				через этот параметр в программу можно передать начальные данные,
				например, в текстовый редактор - имя открываемого файла, в браузер,
				URL открываемого ресурса , в проигрыватель - файл с фильмом или музыкой.
	nCmdShow - режим отображения окна: развёрнуто на весь экран, свёрнуто в окно, свёрнуто на панель задачь
	
	--------------------------------------------------------
	*/
	//			Главное окно программы
	
	//1) Регистрация класса окна: 
	//1.1) Объявить имя класса окна;
	//1.2) Создать и проинициализировать экземпляр структуры WNDCLASSEX:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0; //cb - Count Bytes;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL; //Главное меню
	wClass.lpszClassName = g_sz_CLASS_NAME;
	wClass.lpfnWndProc = WndProc;
	
	//1.3) Зарегистрировать этот класс OC;
	if(!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	
	
	CONST INT MONITOR_WIDTH = GetSystemMetrics(SM_CXSCREEN);
	CONST INT MONITOR_HEIGTH = GetSystemMetrics(SM_CYSCREEN);
	CONST INT MONITOR_SQUARE = MONITOR_WIDTH * MONITOR_HEIGTH;

	CONST INT HWND_SQUARE = MONITOR_SQUARE * 0.75;
	CONST INT HWND_WIDTH = HWND_SQUARE / MONITOR_HEIGTH;
	CONST INT HWND_HEIGTH = HWND_SQUARE / MONITOR_WIDTH;

	CHAR title_buffer[MAX_PATH] = {};

	wsprintf(title_buffer, "%s%d%s%d%s%d%s%d",
		"x : " ,
		(MONITOR_WIDTH - HWND_WIDTH) / 2 ,
		" , y : ",
		(MONITOR_HEIGTH - HWND_HEIGTH) / 2,
		"      w : ",
		HWND_WIDTH,
		" , h : ",
		HWND_HEIGTH);

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL, //exStyles
		g_sz_CLASS_NAME, // ClassName
		title_buffer, //Window title
		WS_OVERLAPPEDWINDOW, // Стиль окна. НАбор стилей всегда зависит от класса окна.
							 //Стиль главного окна всегда WS_OVERLAPPEDWINDOW
		(MONITOR_WIDTH - HWND_WIDTH) / 2, (MONITOR_HEIGTH - HWND_HEIGTH)/2, // Начальная позиция окна (при запуске)
		HWND_WIDTH, HWND_HEIGTH, // Размер окна
		NULL,		// Parent Window
		NULL,       // hMenu. Для главного окна этот параметр определяет главное меню.
					//		  Для дочернего окна (Control) этот параметр содержит ResourseID
					// Благодаря hMenu, дочернее окно всегда можно найти при помощи функции GetDlgItem();
		hInstance,
		NULL
	);
	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);

	//3) Запуск цикла сообщений:
	MSG msg;
	while(GetMessage(&msg , NULL , 0 ,0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	

	switch(uMsg)
	{
	
	case WM_CREATE:
	{
		
		HWND hStatic = CreateWindowEx
		(
			NULL,					//exStyle
			"Static",				//Window class
			"Этот текст создан функцией CreateWindowEx()", // Window text 
			WS_CHILD | WS_VISIBLE, // Window styles
			10, 10, //Position
			500, 25, //Size
			hwnd,  //Parent Window
			(HMENU)1000, //ResourceID
			GetModuleHandle(NULL),//hInstance
			NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE,
			10 , 40,
			500 , 25,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		//100..999 - Окна , значки
		//1000..40000 - элелементы управления окном
		CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			430 , 70,
			80 , 25,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_MOVING:
	case WM_SIZING:
	{
		LPRECT WinRect = (LPRECT)lParam;
		CHAR title_buffer[MAX_PATH] = {};
		wsprintf(title_buffer, "%s%d%s%d%s%d%s%d",
			"x : ",
			WinRect->left,
			" , y : ",
			WinRect->top,
			"      w : ",
			WinRect->right - WinRect->left,
			" , h : ",
			WinRect->bottom - WinRect->top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)title_buffer);
	}
	
	break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 1002:
		{
			CHAR sz_buffer[MAX_PATH] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			SendMessage(hEdit , WM_GETTEXT , MAX_PATH , (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;

		}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}