#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<tchar.h>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<Windowsx.h>

using namespace std;

static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("Game");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

typedef unsigned int ui;

enum INIT {
	FIRST_TIMER = 1, SECOND_TIMER, REDUCE = 5,
	HALF = 2, TIME_MOVE = 10, TIME_MOVE2 = 200,
	POSX = 300, POSY = 250, WIDTH = 750, HEIGHT = 500,
	BTN_H_SIZE = 150, BTN_V_SIZE = 25, X_FIRSTBTN_POZ = 10, Y_FIRSTBTN_POZ = 10,
	V_SHIFT = 5, H_SHIFT = 10, STOP_SIZE = 200, EDIT_BOX_V_SIZE = 30, EDIT_BOX_H_SIZE = 250,
	EDIT_BOX_SINGLE_V_SIZE = 30, NAME_SIZE = 100, FEE_SIZE = 8,
	LIST_X = 20, LIST_Y = 20, LIST_H_SIZE = 280, LIST_V_SIZE = 400,
	ONE = 1, TWOHUNDRED = 200
};

//void MoveExitWindow(const HWND& parentWindow, const HWND& replaceWindow);

enum CTRLSNMS { 
	BUTTON, EDIT, LISTBOX, COMBOBOX, STATIC
};

enum IDENT {
	ID_BTN_HIT = 1000, ID_LIST_BOX_INFO, ID_COMBO_ARM, ID_COMBO_DIRECT, 
	ID_BTN_START, ID_STATIC_ARM, ID_STATIC_DIRECT, ID_COMBO_BLOCK, ID_STATIC_BLOCK

	
};

int FindCenterDesktopH(void);
int FindCenterDesktopV(void);


void SendInfo(const HWND &listboxInfo, const string &result);
string GetInfo(const HWND &comboboxArms, const HWND &comboboxDirection);


int GetPlayerShield(const HWND &combobox);

void EnableAll(vector<HWND> &wndws, const BOOL &enable);