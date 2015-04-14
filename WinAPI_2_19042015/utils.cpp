#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" }
};

vector<HWND> ctrls(TERMINATE);

vector<string> qualities = { "Сильный", "Смелый", "Добрый", "Умный", "Добавить" };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	string result;

	switch (message){

	case WM_CREATE: 

		ctrls[ADD] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], qualities[ADD].c_str(),
			WS_CHILD | WS_VISIBLE, 
			LIST_H_SIZE*2 + LIST_X * 3, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)IDENT_BTN_ADD, hinst, NULL);

		ctrls[STRONG]= CreateWindowEx(NULL, controlNames[BUTTON], qualities[STRONG].c_str(),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX,
			LIST_X, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)IDENT_STRONG, hinst, NULL);

		ctrls[BRAVE] = CreateWindowEx(NULL, controlNames[BUTTON], qualities[BRAVE].c_str(),
			WS_CHILD | WS_VISIBLE | /*BS_CHECKBOX |*/ BS_AUTOCHECKBOX,
			LIST_X * 2 + BTN_H_SIZE, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)IDENT_BRAVE, hinst, NULL);

		ctrls[KIND] = CreateWindowEx(NULL, controlNames[BUTTON], qualities[KIND].c_str(),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX,
			LIST_X, LIST_Y * 2 + BTN_V_SIZE, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)IDENT_KIND, hinst, NULL);

		ctrls[CLEVER] = CreateWindowEx(NULL, controlNames[BUTTON], qualities[CLEVER].c_str(),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX,
			LIST_X * 2 + BTN_H_SIZE, LIST_Y * 2 + BTN_V_SIZE, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)IDENT_CLEVER, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){
			
		case IDENT_BTN_ADD:
			if (HIWORD(wParam) == BN_CLICKED)
			{

				result = "";

				CheckStates(result);
			
				MessageBox(hWnd, result.c_str(), result.c_str(), NULL);
				
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

void CheckStates(string &result)
{
	LRESULT tmp;
	
	for (int i = STRONG; i != ADD; i++)
	{
		tmp = SendMessage(ctrls[i], BM_GETCHECK, NULL, NULL);
		
		if (tmp == BST_CHECKED)
		{
			result += qualities[i];

			result += " ";

		}//if (tmp == BST_CHECKED)
			
	}// for (int i = STRONG; i != ADD; i++)

}// void CheckStates(string &result)

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


