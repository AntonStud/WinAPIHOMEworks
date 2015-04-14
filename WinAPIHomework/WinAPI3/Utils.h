#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<tchar.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm> 


using namespace std;

typedef unsigned int ui;

static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("WinAPI3");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

enum INIT {
	FIRST_TIMER = 1, SECOND_TIMER, REDUCE = 5,
	HALF = 2, TIME_MOVE = 10, TIME_MOVE2 = 200,
	POSX = 300, POSY = 250, WIDTH = 750, HEIGHT = 500,
	BTN_H_SIZE = 150, BTN_V_SIZE = 25, X_FIRSTBTN_POZ = 10, Y_FIRSTBTN_POZ = 10,
	V_SHIFT = 5, H_SHIFT = 10, STOP_SIZE = 200, EDIT_BOX_V_SIZE = 30, EDIT_BOX_H_SIZE = 250,
	EDIT_BOX_SINGLE_V_SIZE = 30, NAME_SIZE = 100, FEE_SIZE = 8,
	LIST_X = 20, LIST_Y = 20, LIST_H_SIZE = 300, LIST_V_SIZE = 400,
	ONE = 1, TWOHUNDRED = 200
};

//void MoveExitWindow(const HWND& parentWindow, const HWND& replaceWindow);

enum CTRLSNMS { 
	BUTTON, EDIT, LISTBOX 
};

enum IDENT {
	IDENT_BTN_SEARCH = 1000, IDENT_LISTBOX, IDENT_EDITBOX
};

enum QUAL{
	BTNSEARCH, LIST, EDITBOX, TERMINATE
};

int FindCenterDesktopH(void);
int FindCenterDesktopV(void);

string GetTextFromEdit(const HWND &hWndCtrl);


void FindPositOfStringInListBox(const string &result, vector<int> &positArray, const vector<string> &strings, const HWND &hWnd);
void FillStrings(vector <string> &strings, const HWND &hWnd, const HWND &list);



