#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" }
};

HWND listboxDigits, lisboxHundreds, buttonAdd;

vector<int> digits, hundreds;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static int flag = -1;

	switch (message){

	case WM_CREATE:

		listboxDigits = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			LIST_X, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)LIST_BOX_DIG, hinst, NULL);

		FillListbox(listboxDigits, ONE, 5, digits);

		lisboxHundreds = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			LIST_H_SIZE + LIST_X * 2, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)LIST_BOX_HUN, hinst, NULL);

		FillListbox(lisboxHundreds, TWOHUNDRED, 6, hundreds);

		buttonAdd = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "Добавить",
			WS_CHILD | WS_VISIBLE,
			LIST_H_SIZE * 2 + LIST_X * 3, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)IDENT_BTN_ADD, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){

		case IDENT_BTN_ADD:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (flag){
				case LIST_BOX_DIG:

					ChangeList(listboxDigits, digits);

					break;
				case LIST_BOX_HUN:

					ChangeList(lisboxHundreds, hundreds);

					break;

				}// switch (flag)

				flag = -1;
			}// if (HIWORD(wParam) == BN_CLICKED)

			break;

		case LIST_BOX_DIG:

			if (HIWORD(wParam) == LBN_SETFOCUS)
			{
				flag = LIST_BOX_DIG;

			}// if (HIWORD(wParam) == LBN_DBLCLK)

			break;

		case LIST_BOX_HUN:
			if (HIWORD(wParam) == LBN_SETFOCUS)
			{
				flag = LIST_BOX_HUN;

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

void ChangeList(const HWND &listbox, vector<int> &arr)
{
	string temp;

	int tmp;

	tmp = arr.back();

	arr.push_back(++tmp);

	temp = to_string(tmp);

	SendMessage(listbox, LB_INSERTSTRING, -1, (LPARAM)temp.c_str());

	SendMessage(listbox, LB_SETSEL, FALSE, -1);

}// void ChangeList(const HWND &listbox, vector<int> &arr)

void FillListbox(const HWND &listbox, const int &start, const int &iter, vector<int> &arr)
{
	string temp;

	int tmp = start;

	for (int i = 0; i < iter; i++)
	{
		arr.push_back(tmp);

		temp = to_string(tmp++);

		SendMessage(listbox, LB_INSERTSTRING, -1, (LPARAM)temp.c_str());

	}// for (int i = 0; i < iter; i++)

}// void FillListbox(const HWND listbox, const int &start, const int &iter, vector<int> &arr)

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


