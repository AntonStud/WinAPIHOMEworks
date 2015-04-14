#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" }
};

vector<HWND> ctrls(TERMINATE);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	string result;

	switch (message){

	case WM_CREATE: 

		
		ctrls[LIST] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			LIST_X, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)IDENT_LISTBOX, hinst, NULL);

		ctrls[EDITBOX] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE ,
			LIST_X * 2 + LIST_H_SIZE, LIST_Y, EDIT_BOX_H_SIZE, EDIT_BOX_V_SIZE, hWnd, (HMENU)IDENT_EDITBOX, hinst, NULL);

		ctrls[BTNSEARCH] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "Найти",
			WS_CHILD | WS_VISIBLE,
			LIST_X * 2 + LIST_H_SIZE, LIST_Y * 2 + EDIT_BOX_V_SIZE, BTN_H_SIZE, BTN_V_SIZE, 
			hWnd, (HMENU)IDENT_BTN_SEARCH, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){
			
		case IDENT_BTN_SEARCH:
			if (HIWORD(wParam) == BN_CLICKED)
			{

				
				
			}// if (HIWORD(wParam) == BN_CLICKED)

			break;

		}//switch (LOWORD(wParam)){

	}// case WM_COMMAND:

	break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);

		break;
	
	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);

		break;

	}//switch (message)

	return 0;

}// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)


int FindCenterDesktopH(void)
{
	// Получаем хэндл рабочего стола
	HWND hDesktop = GetDesktopWindow();

	// Переменная для хранения координат углов рабочего стола
	RECT rectDesktop;

	// Записываем углы рабочего стола в переменную
	GetWindowRect(hDesktop, &rectDesktop);

	return (rectDesktop.right - rectDesktop.left) / 2;

}// int FindCenterDesktopH(void)

int FindCenterDesktopV(void)
{
	// Получаем хэндл рабочего стола
	HWND hDesktop = GetDesktopWindow();

	// Переменная для хранения координат углов рабочего стола
	RECT rectDesktop;

	// Записываем углы рабочего стола в переменную
	GetWindowRect(hDesktop, &rectDesktop);

	return (rectDesktop.bottom - rectDesktop.top) / 2;
}// int FindCenterDesktopV(void


