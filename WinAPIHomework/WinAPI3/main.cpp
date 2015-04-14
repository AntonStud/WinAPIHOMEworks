#pragma once

#include "Utils.h"

HINSTANCE hinst;





int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	
	
	
	WNDCLASSEX wcex;

	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	/*wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));*/
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Call failed!", Title, NULL);
		return 1;
	}

	hinst = hinstance;

	// Получаем центр рабочего стола
	int center = FindCenterDesktopH();

	int xPosWnd = center - WIDTH / 2;

	center = FindCenterDesktopV();

	int yPosWnd = center - HEIGHT / 2;

	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		xPosWnd,
		yPosWnd,
		WIDTH,
		HEIGHT,
		HWND_DESKTOP,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Create window failed!"), Title, NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	

	MSG msg;

	BOOL bRet;

	while (bRet = GetMessage(&msg, NULL, 0, 0))
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}// while (bRet = GetMessage(&msg, NULL, 0, 0))

	return(int)msg.wParam;

}// int WINAPI WinMain





