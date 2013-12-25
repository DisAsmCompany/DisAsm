/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     19/12/2013
*
* Description: main file to run GUI DisAsm
*
*
*
*/

#include "../DisAsm/DisAsm"
#include "../StrAsm/StrAsm"

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return result;
}

static const int ClientWidth = 640;
static const int ClientHeight = 480;

int main(int argc, char * const argv[])
{
	WNDCLASSEX wc;
	DWORD style = WS_POPUP | WS_CAPTION | WS_SYSMENU;
	DWORD styleex = 0;
	HWND hWnd = 0;
	MSG msg;
	RECT bounds = {0, 0, ClientWidth, ClientHeight};
	int Width = ClientWidth;
	int Height = ClientHeight;

	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = wc.cbWndExtra = 0;
	wc.hInstance     = NULL;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = L"DisAsmSampe";
	wc.hIconSm       = 0;
	if (!RegisterClassEx(&wc))
	{
		return EXIT_FAILURE;
	}
	if (AdjustWindowRectEx(&bounds, style, 0, styleex))
	{
		Width = bounds.right - bounds.left;
		Height = bounds.bottom - bounds.top;
	}

	if (NULL == (hWnd = CreateWindowEx(styleex, wc.lpszClassName, wc.lpszClassName, style,
		(GetSystemMetrics(SM_CXSCREEN) - Width) / 2, (GetSystemMetrics(SM_CYSCREEN) - Height) / 2, Width, Height,
		0, 0, 0, 0)))
	{
		return EXIT_FAILURE;
	}
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}
