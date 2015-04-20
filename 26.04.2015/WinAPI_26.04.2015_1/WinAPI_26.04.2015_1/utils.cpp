#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" },
	{ "COMBOBOX" }
};

HWND comboboxListStr, buttonDown;

vector<string> strings;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	//RECT rect;
	HDC hdc;

	//int curSel;
	//int listSize;

	string result = "";

	static int flag = -1;

	switch (message){

	case WM_CREATE:

		comboboxListStr = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_SIMPLE,
			LIST_X, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_LIST, hinst, NULL);

		FillStrings(strings, hWnd, comboboxListStr);

		buttonDown = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "DOWN",
			WS_CHILD | WS_VISIBLE,
			LIST_X * 2 + LIST_H_SIZE, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_BTN_DOWN, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){

		case ID_BTN_DOWN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				auto curSelect = SendMessage(comboboxListStr, CB_GETCURSEL, NULL, NULL);
				auto listSize = SendMessage(comboboxListStr, CB_GETCOUNT, NULL, NULL);

				if (curSelect != -1)
				{
				if (curSelect == listSize - 1){

					MessageBox(hWnd, "This string is last", "End of list", NULL);

					Button_Enable(buttonDown, FALSE);

				}else{

					ShiftDown(comboboxListStr, strings, curSelect);
				}
				
				}

				break;

			}//case ID_BTN_DOWN

		case ID_COMBO_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				Button_Enable(buttonDown, TRUE);

				break;

			}//case ID_BTN_DOWN

		}//switch (LOWORD(wParam)){

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


void FillStrings(vector <string> &strings, const HWND &hWnd, const HWND &list)
{
	fstream fileStrings;
	string line;

	fileStrings.open("Strings.txt", ios::in);

	if (!fileStrings.is_open())
	{
		MessageBox(hWnd, "File with strings is not found", "No file", NULL);
		exit(1);
	}// if (!fileStrings.is_open())

	while (getline(fileStrings, line))
	{
		SendMessage(list, CB_ADDSTRING, NULL, (LPARAM)line.c_str());

		strings.push_back(line);

	}// while (getline(fileStrings, line))

	//sort(strings.begin(), strings.end());

	fileStrings.close();

}// void FillStrings(vector <string> &strings)

void  ShiftDown(const HWND &comboboxListStr, vector <string> &strings, const ui &curSelect)
{
	std::swap(strings[curSelect], strings[curSelect + 1]);

	SendMessage(comboboxListStr, CB_DELETESTRING, curSelect, NULL);
	SendMessage(comboboxListStr, CB_DELETESTRING, curSelect, NULL);

	SendMessage(comboboxListStr, CB_INSERTSTRING, curSelect, (LPARAM)strings[curSelect].c_str());
	SendMessage(comboboxListStr, CB_INSERTSTRING, curSelect + 1, (LPARAM)strings[curSelect+1].c_str());

}// void  ShiftDown(const HWND &comboboxListStr, vector <string> &strings)