#include<Windows.h>


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow) 
{
	
	
	MessageBox
	(
		NULL,
		"Hello World !",
		"MessageBox",
		MB_OK | MB_ICONERROR
	);
	
	return 0;
}