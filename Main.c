/*This line is needed to make it possible to launch a win32 window and launch it from a
main() function instead of a wWinMain() function*/
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

/*The includes*/
#include <stdio.h>
#include <Windows.h>

/*the window device context, which is needed so you can draw on the window*/
static HDC hdc;

/*The drawing function*/
void DrawMyText(HDC hdc)
{
	/*Set the text color and it's background color*/
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 200, 0));

	/*The lines, put the amount of lines in the first brackets and the maximum amount
	of characters in the second brackets*/
	char lines[7][64] =
	{
		{"Hi.\n"},
		{"Me is ANMThijs\n" },
		{"Coding is me hobby\n"},
		{"Dis is an creation\n"},
		{"What does you think?\n"},
		{"I thinks it's relly cool\n"},
		{"Se end\n"}
	};
	
	/*Get the amount of lines into a variable*/
	int size = sizeof(lines) / sizeof(lines[0]);

	/*Make a loop which executes with every line*/
	for (int i = 0; i < size; i++)
	{
		/*the y position of the text*/
		int y = 20 + i * 20;

		/*Amount of chars in a lines (always returns 64 and I have no fix for that yet)*/
		int size2 = sizeof(lines[i]) / sizeof(lines[i][0]);

		/*Loop for each character*/
		for (int j = 0; j < size2; j++)
		{
			/*Put the text on screen and set the amount of visible characters to the
			value of j*/
			TextOut(hdc, 20, y, lines[i], j);
			Sleep(40);
		}
	}
}

/*The window procedure, for explanation see this link:
https://docs.microsoft.com/en-us/windows/win32/learnwin32/learn-to-program-for-windows*/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
	case WM_PAINT:
		Sleep(500);
		hdc = GetDC(hwnd);
		/*The custom drawing function*/
		DrawMyText(hdc);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

/*Create the window. Again, see the microsoft docs for an explanation*/
HWND CreateWin(HINSTANCE hInst)
{
	WNDCLASS wc = { 0 };

	HBRUSH bg = CreateSolidBrush(RGB(0, 0, 0));

	wc.hbrBackground = bg;
	wc.hInstance = hInst;
	wc.lpfnWndProc = MainWndProc;
	wc.lpszClassName = "Main class";
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(NULL, wc.lpszClassName, "Main",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE,
		0, 0, 0, 0,
		NULL, NULL, hInst, NULL);

	return hwnd;
}

/*Main function*/
int main(int argc, char* argv[]) {
	/*Create the window*/
	HWND hwnd = CreateWin(GetModuleHandle(NULL));

	/*Message loop*/
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}