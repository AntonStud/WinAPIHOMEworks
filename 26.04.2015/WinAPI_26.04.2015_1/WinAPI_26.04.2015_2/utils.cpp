#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" },
	{ "COMBOBOX" },
	{ "STATIC" }
};

HWND comboboxSpecialty,staticLabel, buttonRecord, editSurname, listConcat;

vector <string> specialty;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	//RECT rect;
	HDC hdc;

	HDC hdcControl;

	string result = "";

	const int limitEdit = 100;

	static HBRUSH hBrush = CreateSolidBrush(RGB(230, 230, 230));

	DWORD CtrlID;

	//static int flag = -1;

	switch (message){

	case WM_CTLCOLORSTATIC:
	{
		if (staticLabel == (HWND)lParam)

			//OR if the handle is unavailable to you, get ctrl ID

		CtrlID = GetDlgCtrlID((HWND)lParam); //Window Control ID
		if (CtrlID == ID_STATIC_LBL) //If desired control
			{
				HDC hdcStatic = (HDC)wParam;
				SetTextColor(hdcStatic, RGB(0, 0, 0));
				SetBkColor(hdcStatic, RGB(230, 230, 230));
				return (INT_PTR)hBrush;
			}
	}

	
	case WM_CREATE:

		staticLabel = CreateWindowEx(NULL, controlNames[STATIC], "Surname",
			WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			LIST_X, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_LBL, hinst, NULL);
		


		editSurname = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			LIST_X, LIST_Y + BTN_V_SIZE, EDIT_BOX_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_EDIT_SURNAME, hinst, NULL);

		Edit_LimitText(editSurname, limitEdit);

		comboboxSpecialty = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			LIST_X, LIST_Y + BTN_V_SIZE + EDIT_BOX_V_SIZE, BTN_H_SIZE, COMBO_V_SIZE, hWnd, 
			(HMENU)ID_COMBO_BOX_SPEC, hinst, NULL);

		FillStrings(specialty, hWnd, comboboxSpecialty);

		buttonRecord = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "Record",
			WS_CHILD | WS_VISIBLE,
			LIST_X * 2 + BTN_H_SIZE, LIST_Y + BTN_V_SIZE + EDIT_BOX_V_SIZE, BTN_H_SIZE, BTN_V_SIZE, hWnd, 
			(HMENU)ID_BTN_REC, hinst, NULL);

		listConcat = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE,
			LIST_X * 2 + EDIT_BOX_H_SIZE, LIST_Y + BTN_V_SIZE, LIST_H_SIZE, LIST_V_SIZE, hWnd,
			(HMENU)ID_LIST_CONCAT, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){

		case ID_BTN_REC:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				try{

					result = GetInfo(comboboxSpecialty, editSurname, hWnd);

				}
				catch (char* s){

				MessageBox(hWnd, s, s, NULL);

				break;
				}
				
				SendInfo(listConcat, result);
				
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


void FillStrings(vector <string> &strings, const HWND &hWnd, const HWND &combo)
{
	fstream fileStrings;
	string line;

	fileStrings.open("Specialty.txt", ios::in);

	if (!fileStrings.is_open())
	{
		MessageBox(hWnd, "File with specialties is not found", "No file", NULL);
		exit(1);
	}// if (!fileStrings.is_open())

	while (getline(fileStrings, line))
	{
		SendMessage(combo, CB_ADDSTRING, NULL, (LPARAM)line.c_str());

		strings.push_back(line);

	}// while (getline(fileStrings, line))

	//sort(strings.begin(), strings.end());

	fileStrings.close();

}// void FillStrings(vector <string> &strings)


void SendInfo(const HWND &listbox, const string &result)
{

	SendMessage(listbox, LB_ADDSTRING, NULL, (LPARAM)result.c_str());

}//void SendInfo(const HWND &listboxInfo)

string GetInfo(const HWND &combobox, const HWND &edit , const HWND &hWnd)
{
	char *buffer;
	int buffSize;
	string result;

	buffSize = GetWindowTextLength(edit);

	buffer = new char[buffSize + 1];

	GetWindowText(edit, (LPTSTR)buffer, buffSize + 1);

	result = buffer;

	if (result.length() == 0){

		throw "Enter surname";

	}// if (!result.length()){

	result += " : ";

	auto pos = ComboBox_GetCurSel(combobox);

	if (pos == CB_ERR){

		throw "Choose specialty";

	}// if (pos == CB_ERR)

	result += specialty[pos];

	//delete[]buffer;

	return result;
}// string GetInfo(const HWND &comboboxArms, const HWND &comboboxDirection)

