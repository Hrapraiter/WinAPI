#undef UNICODE

#include<Windows.h>
#include<vector>
#include<functional>
#include<string>::std::stoi
#include"algorithm"::std::for_each

#include"PointCollection.h"
#include"resource.h"



std::vector<CHAR*> debug_messages = {};
void clearDebug();
void addMessage(CHAR* message);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = LPSTR("Calculate");
	wClass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	CONST INT DISPLAY_WIDTH = GetSystemMetrics(SM_CXSCREEN);
	CONST INT DISPLAY_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

	CONST INT WIDTH = 380,
			 HEIGHT = 600,
			 X = (DISPLAY_WIDTH - WIDTH)/2,
			 Y = (DISPLAY_HEIGHT - HEIGHT)/2;

	HWND hwnd = CreateWindowEx
	(
		NULL,
		wClass.lpszClassName,
		wClass.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		X , Y,
		WIDTH , HEIGHT ,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	clearDebug();
	return msg.wParam;
}
enum WndElem
{
	EDIT = 1001 ,
	
	BUTTON_NULL = 1002, 
	BUTTON_ONE = 1003,
	BUTTON_TWO  = 1004,
	BUTTON_THREE  = 1005,
	BUTTON_FOUR  = 1006,
	BUTTON_FIVE = 1007,
	BUTTON_SIX = 1008,
	BUTTON_SEVEN = 1009,
	BUTTON_EIGHT = 1010,
	BUTTON_NINE = 1011,

	BUTTON_PLUS = 1020, BUTTON_MINUS = 1021,
	BUTTON_MULTIPLY = 1022 , BUTTON_DIVIDE = 1023,

	BUTTON_RESULT = 1024,
	
	BUTTON_BACKSPACE = 1030, BUTTON_CLEAR = 1031,

	BUTTON_DEBUG
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_CREATE:
	{

		PointCollection number_points;
		number_points.addPoint("Button_Null", 80, 270);

		number_points.addPoint("Button_One", 30, 120);
		number_points.addPoint("Button_Two", 80, 120);
		number_points.addPoint("Button_Three", 130, 120);
		number_points.addPoint("Button_Four", 30, 170);
		number_points.addPoint("Button_Five", 80, 170);
		number_points.addPoint("Button_Six", 130, 170);
		number_points.addPoint("Button_Seven", 30, 220);
		number_points.addPoint("Button_Eight", 80, 220);
		number_points.addPoint("Button_Nine", 130, 220);

		number_points.SelectX([](int x) { return x + 30; });
		number_points.SelectY([](int y) { return y; });
		//Edit			-> Edit
		CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE,
			30, 30,
			300, 25,
			hwnd,
			(HMENU)EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Null		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[0]->x, number_points[0]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_NULL,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_One		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"1",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[1]->x, number_points[1]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_ONE,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Two		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"2",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[2]->x, number_points[2]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_TWO,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Tree		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"3",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[3]->x, number_points[3]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_THREE,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Four		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"4",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[4]->x, number_points[4]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_FOUR,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Five		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"5",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[5]->x, number_points[5]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_FIVE,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Six		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"6",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[6]->x, number_points[6]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_SIX,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Seven		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"7",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[7]->x, number_points[7]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_SEVEN,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Eight		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"8",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[8]->x, number_points[8]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_EIGHT,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Nine		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"9",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[9]->x, number_points[9]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_NINE,
			GetModuleHandle(NULL),
			NULL
		);

		PointCollection operators_points;
		operators_points.addPoint("Button_Divide", 50, 50);
		operators_points.addPoint("Button_Multiply", 50, 100);
		operators_points.addPoint("Button_Minus", 50, 150);
		operators_points.addPoint("Button_Plus", 50, 200);
		operators_points.addPoint("Button_Result", 50, 250);

		operators_points.SelectX([](int x) {return x + 180; });
		operators_points.SelectY([](int y) {return y + 20; });
		//Button_Multiply   -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"*",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			operators_points["Button_Multiply"]->x, operators_points["Button_Multiply"]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_MULTIPLY,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Divide    -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"/",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			operators_points["Button_Divide"]->x, operators_points["Button_Divide"]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_DIVIDE,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Minus     -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			operators_points["Button_Minus"]->x, operators_points["Button_Minus"]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_MINUS,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_Plus      -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"+",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			operators_points["Button_Plus"]->x, operators_points["Button_Plus"]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_PLUS,
			GetModuleHandle(NULL),
			NULL
		);

		//Button_Result    -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			operators_points["Button_Result"]->x, operators_points["Button_Result"]->y,
			40, 40,
			hwnd,
			(HMENU)BUTTON_RESULT,
			GetModuleHandle(NULL),
			NULL
		);
		// ниже отдельные кнопки без объединения
		// -------------------------------------------------------------------------------------
		// Button_Clear     -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			50, 70,
			70, 30,
			hwnd,
			(HMENU)BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL
		);
		//Button_BackScape  -> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"<-BS",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			130, 70,
			70, 30,
			hwnd,
			(HMENU)BUTTON_BACKSPACE,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			"Debug",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			250, 400,
			80, 40,
			hwnd,
			(HMENU)BUTTON_DEBUG,
			GetModuleHandle(NULL),
			NULL
		);

	}
	break;

	case WM_COMMAND:
	{
		HWND hEdit = GetDlgItem(hwnd, EDIT);
		CHAR sz_buffer_edit[MAX_PATH] = {};
		SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer_edit);

		std::function<void(char value)> add_edit_value = [&hEdit , &sz_buffer_edit](char value)
			{
				/*
				
				if(GetFocus() == hEdit)
				{
					int index = SendMessage(hEdit, EM_GETSEL, 0, 0);
					CHAR part1[MAX_PATH] = {};
					CHAR part2[MAX_PATH] = {};

					int sz_buffer_edit_len = lstrlen(sz_buffer_edit);
					for(int i = 0; i < sz_buffer_edit_len;++i)
					{
						if(i <= index)
						{
							wsprintf(part1, "%s%c", part1, sz_buffer_edit[i]);
							continue;
						}
						wsprintf(part2, "%s%c", part2, sz_buffer_edit[i]);
					}
					wsprintf(sz_buffer_edit, "%s%c%s", part1, value, part2);
				}

				*/
				wsprintf(sz_buffer_edit, "%s%c", sz_buffer_edit, value);
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer_edit);
			};
		switch (LOWORD(wParam))
		{
		
		case BUTTON_NULL: add_edit_value('0');break;
		case BUTTON_ONE:  add_edit_value('1');break;
		case BUTTON_TWO:  add_edit_value('2');break;
		case BUTTON_THREE:add_edit_value('3');break;
		case BUTTON_FOUR: add_edit_value('4');break;
		case BUTTON_FIVE: add_edit_value('5');break;
		case BUTTON_SIX:  add_edit_value('6');break;
		case BUTTON_SEVEN:add_edit_value('7');break;
		case BUTTON_EIGHT:add_edit_value('8');break;
		case BUTTON_NINE: add_edit_value('9');break;


		case BUTTON_DIVIDE:  add_edit_value('/');break;
		case BUTTON_MULTIPLY:add_edit_value('*');break;
		case BUTTON_PLUS:    add_edit_value('+');break;
		case BUTTON_MINUS:   add_edit_value('-');break;


		case BUTTON_RESULT:
		{
			CHAR sz_buffer[MAX_PATH] = {};
			SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer);
			int sz_buffer_len = lstrlen(sz_buffer);

			if (sz_buffer_len <= 0)
			{
				MessageBox(hwnd, "Строка пуста.", "Error", MB_ICONERROR);
				break;
			}

			// проверка является ли елемент одним из группы символов
			bool(*isValue)(CHAR valid_vales[], CHAR value) = [](CHAR valid_vales[], CHAR value)
				{
					int len = lstrlen(valid_vales);
					for (int i = 0; i < len; ++i)
						if (value == valid_vales[i])
							return true;
					return false;
				};
			// сокращение через лямбду
			bool(*isNumber)(CHAR elem) = [](CHAR elem) {return elem >= '0' && elem <= '9'; };
			
			CHAR valid_values[MAX_PATH] = "+-/* ";

			// валидация на буквы и запрещенные символы
			bool isFind_warning_value = false;
			for (int i = 0; i < sz_buffer_len; ++i)
			{
				if (not(sz_buffer[i] >= '0' && sz_buffer[i] <= '9' || isValue(valid_values, sz_buffer[i])))
				{
					MessageBox(hwnd, "В строке присутсвуют буквы или запрещенные символы", "Error", MB_ICONERROR);
					isFind_warning_value = true;
					break;
				}
			}
			if (isFind_warning_value)break;

			std::vector<int> numbers;
			std::vector<CHAR> operators;
			
			CHAR operators_validate[MAX_PATH] = "+-/*";
			CHAR int_operators[MAX_PATH] = "+-";

			bool isStart = isNumber(sz_buffer[0]) || isValue(int_operators, sz_buffer[0]) && isNumber(sz_buffer[1]);
			// тут косяк
			for (int i = 0, start_num_point = isStart ? 0 : -1, end_num_point = -1; i < sz_buffer_len - 1; ++i)
			{
				
				if (isValue(operators_validate, sz_buffer[i]) && not isNumber(sz_buffer[i + 1])) 
				{
					// оператор на конце строки условие не считает но оно и не нужно  пример "66 + 66 +" 
					// в итоге плюс на самом конце строки несчитает 
					// а если "66 + 66 + " то считает но выдаст ошибку через условие ниже
					operators.push_back(sz_buffer[i]);

					CHAR* message = new CHAR[MAX_PATH];
					wsprintf(message, "operators [ %d ] -> %c", operators.size() - 1, operators[operators.size()-1]);
					addMessage(message);
					message = nullptr;
				}
				if (
					start_num_point != -1 &&
					end_num_point != -1
					
					||

					end_num_point == -1 &&
					i+1 == sz_buffer_len-1 &&
					isNumber(sz_buffer[i+1]) &&
					(end_num_point = i + 1) == i + 1
					
					)
				
				{
					//тут косяк 
					CHAR number_buffer[MAX_PATH] = {};
					
					for (int point = start_num_point; point <= end_num_point; ++point)
						wsprintf(number_buffer, "%s%c", number_buffer, sz_buffer[point]);

					start_num_point = -1;
					end_num_point = -1;

					//numbers.push_back(std::stoi(number_buffer));

					CHAR* message = new CHAR[MAX_PATH];
					wsprintf(message, "numbers  -> %s", number_buffer);
					//wsprintf(message, "numbers [ %d ] -> %d", numbers.size() - 1, numbers[numbers.size() - 1]);
					addMessage(message);
					message = nullptr;
				}

				if (not isNumber(sz_buffer[i]) && not isValue(int_operators , sz_buffer[i]) && isNumber(sz_buffer[i + 1]))
					start_num_point = i + 1;

				else if (isNumber(sz_buffer[i]) && not isNumber(sz_buffer[i + 1]) && not isValue(int_operators , sz_buffer[i+1]))
					end_num_point = i;
			}
			if (not(numbers.size() - 1 == operators.size()))
			{
				MessageBox(hwnd, "Пропущена цифра или оператор", "Error", MB_ICONERROR);
				break;
			}
		}
		break;



		case BUTTON_BACKSPACE:
		{
			CHAR sz_buffer[MAX_PATH] = {};
			CHAR sz_new_text[MAX_PATH] = {};

			SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer);
			int sz_buffer_len = lstrlen(sz_buffer);

			if (sz_buffer_len <= 0)break;

			sz_buffer[sz_buffer_len - 1] = NULL;
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
			
		case BUTTON_CLEAR:
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
			break;

			
		case BUTTON_DEBUG:
		{
			DialogBoxParam(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)DlgProc, 0);
		}
		break;
		
		}
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

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < debug_messages.size(); ++i)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)debug_messages[i]);
	}
	break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDEXIT:
			clearDebug();
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		clearDebug();
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
void clearDebug()
{
	for(CHAR* elem : debug_messages)
		delete elem;
	debug_messages.clear();
}
void addMessage(CHAR* message)
{
	debug_messages.push_back(message);
	message = nullptr;
}