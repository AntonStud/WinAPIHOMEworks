#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" }
};

vector<HWND> ctrls(TERMINATE);
vector<string> strings;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	string result;

	vector<int> positArray;

	switch (message){

	case WM_CREATE: 

		
		ctrls[LIST] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			LIST_X, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)IDENT_LISTBOX, hinst, NULL);

		FillStrings(strings, hWnd, ctrls[LIST]);

		ctrls[EDITBOX] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			LIST_X * 2 + LIST_H_SIZE, LIST_Y, EDIT_BOX_H_SIZE, EDIT_BOX_V_SIZE, hWnd, (HMENU)IDENT_EDITBOX, hinst, NULL);

		ctrls[BTNSEARCH] = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "Search",
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
				result = GetTextFromEdit(ctrls[EDITBOX]);

				SendMessage(ctrls[LIST], LB_SETSEL, FALSE, -1);
				
				if (result.size())
				{
				//SetWindowText(hWnd, result.c_str());
				FindPositOfStringInListBox(result, positArray, strings, hWnd);

				if (positArray.size())
				{
					for (ui i = 0; i < positArray.size(); i++)
					{
						SendMessage(ctrls[LIST], LB_SETSEL, TRUE, positArray[i]);

					}//for (int i = 0; i < positArray.size(); i++) 
					
				}else{

					MessageBox(hWnd, "Nothing found","Empty",NULL);

				}// if else

				}// if (result.size())

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

string GetTextFromEdit(const HWND &hWndCtrl)
{
	char *buffer;
	int buffSize;
	string result;

	buffSize = GetWindowTextLength(hWndCtrl);
	buffer = new char[buffSize + 1];

	GetWindowText(hWndCtrl, (LPTSTR)buffer, buffSize + 1);

	//SetWindowText(hWnd, buffer);

	result = buffer;

	delete[]buffer;

	return result;

}// string GetTextFromEdit(HWND hWndCtrl)

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


void FindPositOfStringInListBox(const string &result, vector<int> &positArray, const vector<string> &strings, const HWND &hWnd)
{
	size_t pos;/* = -1;*/

	//string someString = to_string(strings.size());

	//SetWindowText(hWnd, someString.c_str());
	
	for (ui i = 0; i < strings.size(); i++)
	{
		pos = strings[i].find(result);

		if (pos != std::string::npos)
		{
			positArray.push_back(i);

		}// if (pos != std::string::npos)

	}// for (ui i = 0; i < strings.size(); i++)


}// void FindPositOfStringInListBox(const string &result, vector<int> &positArray)

void FillStrings(vector <string> &strings, const HWND &hWnd, const HWND &list)
{
	fstream fileStrings;
	string line;

	fileStrings.open("Strings.txt", ios::in);

	if (!fileStrings.is_open())
	{
		MessageBox(hWnd, "File with strings is not found", "No file", NULL);
		//exit(1);
	}// if (!fileStrings.is_open())

	while (getline(fileStrings, line))
	{
		SendMessage(list, LB_ADDSTRING, NULL, (LPARAM)line.c_str());

		strings.push_back(line);

	}// while (getline(fileStrings, line))

	std::sort(strings.begin(), strings.end());

	fileStrings.close();

}// void FillStrings(vector <string> &strings)


