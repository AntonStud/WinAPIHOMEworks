#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<tchar.h>
#include<iostream>
#include<iomanip>
#include<sstream>
#include"Employee.h"



using namespace std;

static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("Worker 0.1");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

enum INIT {
	FIRST_TIMER = 1, SECOND_TIMER, REDUCE = 5,
	HALF = 2, TIME_MOVE = 10, TIME_MOVE2 = 200,
	POSX = 300, POSY = 250, WIDTH = 750, HEIGHT = 500,
	BTN_H_SIZE = 150, BTN_V_SIZE = 25, X_FIRSTBTN_POZ = 10, Y_FIRSTBTN_POZ = 10,
	V_SHIFT = 5, H_SHIFT = 10, STOP_SIZE = 200, EDIT_BOX_V_SIZE = 30, EDIT_BOX_H_SIZE = 250,
	EDIT_BOX_SINGLE_V_SIZE = 30, NAME_SIZE = 100, FEE_SIZE = 8
};

//void MoveExitWindow(const HWND& parentWindow, const HWND& replaceWindow);

enum CTRLSNMS { 
	BUTTON, EDIT, LISTBOX };

enum BTNS {
	COM_BTN_ADD, COM_BTN_TO_SINGLE, COM_BTN_TO_ALL,
	EDIT_BOX_NAME, EDIT_BOX_FEE, EDIT_BOX_LIMIT,
	LIST_BOX_FROM, LIST_BOX_TO,
	GROUPS_NAME
};

int FindCenterDesktopH(void);
int FindCenterDesktopV(void);

void AddInfo(HWND hWnd);
void Move(HWND hWnd);


//typedef std::pair<std::map<string, Employee*>::iterator, bool> ItBoolToMap;
//typedef map<string, Employee*> MapEmployee;
