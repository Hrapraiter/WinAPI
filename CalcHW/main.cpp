#undef UNICODE

#include<Windows.h>
#include<vector>
#include<functional>
#include<string>
#include<strsafe.h>

#include"PointCollection.h"
#include"resource.h"

/////////////////////////////////////////////////////////////////////////////////
#define BUTTON_SIZE			  40
#define isNumber(elem)  ( (elem) >= '0' && (elem) <= '9' )
/////////////////////////////////////////////////////////////////////////////////

#define	EDIT				1001

#define	BUTTON_NULL			1002
#define	BUTTON_ONE			1003
#define	BUTTON_TWO			1004
#define	BUTTON_THREE		1005
#define	BUTTON_FOUR			1006
#define	BUTTON_FIVE			1007
#define	BUTTON_SIX			1008
#define	BUTTON_SEVEN		1009
#define	BUTTON_EIGHT		1010
#define	BUTTON_NINE			1011

#define BUTTON_POINT		1018
//#define BUTTON_PRIORITY		1019

#define	BUTTON_PLUS			1020
#define BUTTON_MINUS		1021
#define	BUTTON_MULTIPLY		1022
#define BUTTON_DIVIDE		1023

#define BUTTON_RESULT		1025

#define BUTTON_BACKSPACE	1030
#define BUTTON_CLEAR		1031
#define BUTTON_DEBUG		1032


/////////////////////////////////////////////////////////////////////////////////

CONST CHAR valid_values[] = "+-/*. ";
CONST CHAR operators_validate[] = "+-/*";
CONST CHAR int_operators[] = "+-";

/////////////////////////////////////////////////////////////////////////////////
std::vector<CHAR*> debug_messages = {};

void clearDebug();
void addMessage(CHAR* message);

bool isValue(CONST CHAR valid_vales[], const CHAR value);
void add_edit_value(HWND& hEdit, char value);

CHAR* match_str_algo(CHAR* str);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
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
		number_points.addPoint("Button_Point", 130, 270);

		number_points.SelectX([](int x) { return x + 30; });
		number_points.SelectY([](int y) { return y; });
		//////////////////////////////////////////////////////////////////////////
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
		//Button_point		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points["Button_Point"]->x, number_points["Button_Point"]->y,
			BUTTON_SIZE, BUTTON_SIZE,
			hwnd,
			(HMENU)BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		//////////////////////////////////////////////////////////////////////////
		//Button_Null		-> Button
		CreateWindowEx
		(
			NULL,
			"Button",
			"0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
			number_points[0]->x, number_points[0]->y,
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
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
			BUTTON_SIZE, BUTTON_SIZE,
			hwnd,
			(HMENU)BUTTON_NINE,
			GetModuleHandle(NULL),
			NULL
		);
		
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
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

		int sz_buffer_edit_len = lstrlen(sz_buffer_edit);

		CHAR last_elem = sz_buffer_edit[sz_buffer_edit_len-1];

		
		switch (LOWORD(wParam))
		{
		
		case BUTTON_NULL: add_edit_value(hEdit ,'0');break;
		case BUTTON_ONE:  add_edit_value(hEdit ,'1');break;
		case BUTTON_TWO:  add_edit_value(hEdit ,'2');break;
		case BUTTON_THREE:add_edit_value(hEdit ,'3');break;
		case BUTTON_FOUR: add_edit_value(hEdit, '4');break;
		case BUTTON_FIVE: add_edit_value(hEdit, '5');break;
		case BUTTON_SIX:  add_edit_value(hEdit ,'6');break;
		case BUTTON_SEVEN:add_edit_value(hEdit ,'7');break;
		case BUTTON_EIGHT:add_edit_value(hEdit ,'8');break;
		case BUTTON_NINE: add_edit_value(hEdit ,'9');break;

		case BUTTON_POINT: add_edit_value(hEdit, '.');break;

		case BUTTON_DIVIDE:  add_edit_value(hEdit ,'/');break;
		case BUTTON_MULTIPLY:add_edit_value(hEdit ,'*');break;
		case BUTTON_PLUS:    add_edit_value(hEdit ,'+');break;
		case BUTTON_MINUS:   add_edit_value(hEdit ,'-');break;


		case BUTTON_RESULT:// без скобок логика пока такая
		{
			CHAR* str = match_str_algo(sz_buffer_edit);
			
			if (not str)
				break;

			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)str);
			
			delete[] str;
			str = nullptr;	
		}
		break;
		case BUTTON_BACKSPACE:
			if (sz_buffer_edit_len < 1)break;
			sz_buffer_edit[--sz_buffer_edit_len] = 0;
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer_edit);
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isValue(CONST CHAR valid_vales[], const CHAR value)
{
		int len = lstrlen(valid_vales);
		for (int i = 0; i < len; ++i)
			if (value == valid_vales[i])
				return true;
		return false;
};

void add_edit_value(HWND& hEdit ,char value)
{
	CHAR sz_buffer_edit[MAX_PATH] = {};
	SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer_edit);
	int sz_buffer_edit_len = lstrlen(sz_buffer_edit);

	CHAR last_elem = sz_buffer_edit[sz_buffer_edit_len - 1];

	if (not isNumber(last_elem) && value == '.')return;

	if (last_elem == '.' && not isNumber(value))
	{
		sz_buffer_edit[sz_buffer_edit_len++] = '0';
		sz_buffer_edit[sz_buffer_edit_len++] = '0';
		sz_buffer_edit[sz_buffer_edit_len++] = ' ';
	}

	if (isNumber(last_elem) && isValue(operators_validate, value) ||
		isValue(operators_validate, last_elem) && last_elem != '-' && isNumber(value))

		sz_buffer_edit[sz_buffer_edit_len++] = ' ';

	sz_buffer_edit[sz_buffer_edit_len++] = value;
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer_edit);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////


CHAR* match_str_algo(CHAR* str)
{// реализованно как отдельный метод для добавления  логики под () в калькуляторе
	///////////////////////////////сбор и инициализация данных////////////////////////////////////////////////
	int str_len = lstrlen(str);
	if (str_len <= 0)
	{
		MessageBox(NULL, "Строка пуста.", "Error", MB_ICONERROR);
		return nullptr;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////


	bool isFind_warning_value = false;
	for (int i = 0; i < str_len; ++i)
	{
		if (not(str[i] >= '0' && str[i] <= '9' || isValue(valid_values, str[i])))
		{
			MessageBox(NULL, "В строке присутсвуют буквы или запрещенные символы", "Error", MB_ICONERROR);
			isFind_warning_value = true;
			return nullptr;
		}
	}

	std::vector<long double> numbers;
	std::vector<CHAR> operators;

	//////////////////////////////////блок разборки строки на символы/////////////////////////////////////////
	bool isStart = isNumber(str[0]) || (isValue(int_operators, str[0]) && isNumber(str[1]));
	for (int i = 0, start_num_point = isStart ? 0 : -1, end_num_point = -1; i < str_len - 1; ++i)
	{

		if (isValue(operators_validate, str[i]) && not isNumber(str[i + 1]))
		{
			// оператор на конце строки условие не считает но оно и не нужно  пример "66 + 66 +" 
			// в итоге плюс на самом конце строки несчитает 
			// а если "66 + 66 + " то считает но выдаст ошибку через условие ниже
			operators.push_back(str[i]);

			CHAR* message = new CHAR[MAX_PATH];
			wsprintf(message, "operators [ %d ] -> %c", operators.size() - 1, operators[operators.size() - 1]);
			addMessage(message);
			message = nullptr;
		}

		if (not isNumber(str[i]) && str[i] != '.' && isNumber(str[i + 1]))
			start_num_point = isValue(int_operators, str[i]) ? i : i + 1;

		else if (isNumber(str[i]) && not isNumber(str[i + 1]) && str[i + 1] != '.')
			end_num_point = i;

		if (

			start_num_point != -1 &&
			end_num_point != -1


			||


			start_num_point != -1 &&
			end_num_point == -1 &&
			i + 1 == str_len - 1 &&
			isNumber(str[i + 1]) &&
			(end_num_point = i + 1) == i + 1


			)

		{
			CHAR number_buffer[MAX_PATH] = {};
			int number_buffer_len = lstrlen(number_buffer);

			for (int point = start_num_point; point <= end_num_point; ++point)
				number_buffer[number_buffer_len++] = str[point];

			start_num_point = -1;
			end_num_point = -1;

			numbers.push_back(std::stod(number_buffer));

			CHAR* message = new CHAR[MAX_PATH];
			//StringCchPrintf(message,MAX_PATH, "numbers  -> %s", number_buffer);
			StringCchPrintf(message, MAX_PATH, "numbers [ %d ] -> %.2f", numbers.size() - 1, numbers[numbers.size() - 1]);
			addMessage(message);
			message = nullptr;
		}

	}
	str = nullptr;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (not(numbers.size() - 1 == operators.size()))
	{
		MessageBox(NULL, "Пропущена цифра или оператор", "Error", MB_ICONERROR);
		return nullptr;
	}

	long double result = numbers[0];
	for (int i = 1; i < numbers.size(); ++i)
	{
		switch (operators[i - 1])
		{
		case '+':result += numbers[i]; break;
		case '-':result -= numbers[i]; break;
		case '*':result *= numbers[i]; break;
		case '/':result /= numbers[i]; break;
		}
	}
	CHAR* result_output = new CHAR[MAX_PATH];

	StringCchPrintf(result_output, MAX_PATH, "%.2f", result);
	return result_output;
}