#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" },
	{ "COMBOBOX" }
};

HWND comboboxArms, comboboxDirection, buttonHit, listboxInfo;


vector<string> arms = {"Fist" , "Leg"};
vector<string> direction = { "Head", "Body", "Legs" };
vector<string> history;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	//RECT rect;
	HDC hdc;

	string result = "";

	static int flag = -1;

	switch (message){

	case WM_CREATE:

		comboboxArms = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			LIST_X, LIST_Y, BTN_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_ARM, hinst, NULL);

		for (ui i = 0; i < arms.size(); i++)
		{
			SendMessage(comboboxArms, CB_ADDSTRING, NULL, (LPARAM)arms[i].c_str());

			//SetWindowText(hWnd, arms[i].c_str());
		}// for (ui i = 0; i < arms.size(); i++)

		//SendMessage(comboboxArms, CB_SELECTSTRING, -1, (LPARAM)arms[0].c_str());

		ComboBox_SetText(comboboxArms, "Choose arm");


		comboboxDirection = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_NOINTEGRALHEIGHT,
			LIST_X, LIST_Y + LIST_Y * 2, BTN_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_DIRECT, hinst, NULL);

		for (ui i = 0; i < direction.size(); i++)
		{
			
			SendMessage(comboboxDirection, CB_ADDSTRING, NULL, (LPARAM)direction[i].c_str());

		}// for (ui i = 0; i < arms.size(); i++)

		ComboBox_SetText(comboboxDirection, "Choose level");

		listboxInfo = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			BTN_H_SIZE + LIST_X * 2, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_LIST_BOX_INFO, hinst, NULL);

		buttonHit = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "HIT",
			WS_CHILD | WS_VISIBLE,
			LIST_X, LIST_Y * 2 + LIST_Y * 3, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_BTN_HIT, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){

		case ID_BTN_HIT:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				try{

				result = GetInfo(comboboxArms, comboboxDirection);

				}
				catch (char* s){

				MessageBox(hWnd, s, s, NULL);

				break;
				}
				
				SendInfo(listboxInfo, result);
				
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

}

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


void SendInfo(const HWND &listboxInfo, const string &result)
{

	SendMessage(listboxInfo, LB_ADDSTRING, NULL, (LPARAM)result.c_str());

}//void SendInfo(const HWND &listboxInfo)

string GetInfo(const HWND &comboboxArms, const HWND &comboboxDirection)
{
	
	string result = "Hit: ";

	auto pos = ComboBox_GetCurSel(comboboxArms);

	if (pos == CB_ERR)
	{
		throw "Choose arm";
	}// if (pos == CB_ERR)

	result += arms[pos];

	result += " in: ";

	pos = ComboBox_GetCurSel(comboboxDirection);

	if (pos == CB_ERR)
	{
		throw "Choose level";
	}// if (pos == CB_ERR)


	result += direction[pos];

	return result;
}// string GetInfo(const HWND &comboboxArms, const HWND &comboboxDirection)

