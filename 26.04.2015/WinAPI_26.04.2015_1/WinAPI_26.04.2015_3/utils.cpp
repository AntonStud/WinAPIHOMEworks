#pragma once

#include "Utils.h"
#include "Game.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" },
	{ "COMBOBOX" },
	{ "STATIC" }

};

//HWND comboboxArms, comboboxDirection, buttonHit, listboxInfo;

vector<HWND> wndws;

Game game;

//vector<string> arms = {"Fist" , "Leg"};
//vector<string> direction = { "Head", "Body", "Legs" };
//vector<string> history;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	//RECT rect;
	HDC hdc;

	string result = "";

	static int flag = -1;

	int hit, shield, direct, health;

	switch (message){

	case WM_CREATE:

		
		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			LIST_X, LIST_Y * 2 + BTN_V_SIZE, BTN_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_ARM, hinst, NULL));

		for (ui i = 0; i < game.GetPlayer().GetAmmo().size(); i++)
		{
			SendMessage(wndws[wndws.size() - 1], CB_ADDSTRING, NULL, (LPARAM)game.GetPlayer().GetAmmo()[i]->GetName().c_str());

			//SetWindowText(hWnd, arms[i].c_str());
		}// for (ui i = 0; i < arms.size(); i++)

		//SendMessage(comboboxArms, CB_SELECTSTRING, -1, (LPARAM)arms[0].c_str());

		ComboBox_SetText(wndws[wndws.size() - 1], "Choose arm");

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_NOINTEGRALHEIGHT,
			LIST_X, LIST_Y*3 + BTN_V_SIZE * 2, BTN_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_DIRECT, hinst, NULL));

		for (ui i = 0; i < game.GetPlayer().GetBlocks().size(); i++)
		{
			
			SendMessage(wndws[wndws.size() - 1], CB_ADDSTRING, NULL, (LPARAM)game.GetPlayer().GetBlocks()[i]->GetName().c_str());

		}// for (ui i = 0; i < arms.size(); i++)

		ComboBox_SetText(wndws[wndws.size() - 1], "Choose direction");

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_NOINTEGRALHEIGHT,
			LIST_X, LIST_Y * 4 + BTN_V_SIZE * 3, BTN_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_BLOCK, hinst, NULL));

		for (ui i = 0; i < game.GetPlayer().GetBlocks().size(); i++)
		{

			SendMessage(wndws[wndws.size() - 1], CB_ADDSTRING, NULL, (LPARAM)game.GetPlayer().GetBlocks()[i]->GetName().c_str());

		}// for (ui i = 0; i < arms.size(); i++)

		ComboBox_SetText(wndws[wndws.size() - 1], "Choose block");

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "",
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			BTN_H_SIZE + LIST_X * 2 + 100, LIST_Y, LIST_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_LIST_BOX_INFO, hinst, NULL));

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "HIT",
			WS_CHILD | WS_VISIBLE,
			LIST_X, LIST_Y * 5 + BTN_V_SIZE * 4, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_BTN_HIT, hinst, NULL));


		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "Ammo",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS ,
			LIST_X, LIST_Y + BTN_V_SIZE, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_ARM, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "Direction",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS,
			LIST_X, LIST_Y * 2 + BTN_V_SIZE * 2, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_DIRECT, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "Block",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS,
			LIST_X, LIST_Y * 3 + BTN_V_SIZE * 3, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_BLOCK, hinst, NULL));

		//TODO Add two edit boxes for health;

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[BUTTON], "START",
			WS_CHILD | WS_VISIBLE,
			LIST_X, LIST_Y, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_BTN_START, hinst, NULL));

		EnableAll(wndws, FALSE);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){

		case ID_BTN_HIT:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (!game.IsOver())
				{
					switch (game.GetTurn())
					{
					case FIRST_PLAYER:

						game.SetEnd(game.GetComputer().GetHealth());

						game.ChangeTurn(COMPUTER);

						break;
					case COMPUTER:

						
						hit = game.GetComputer().ChooseArm();

						direct = game.GetComputer().ChooseDirect();
						
						try{
							shield = GetPlayerShield(wndws[3]);
						}
						catch (char* s)
						{
							
							MessageBox(hWnd, s, s, NULL);

							break;
						}

						health = game.GetPlayer().GetHealth() -
							game.GetComputer().CalculateDamage(hit, direct, shield);

						game.GetPlayer().SetHealth(health);

						//TODO Show hits, blocks, damage and set health
						
						game.SetEnd(game.GetPlayer().GetHealth());

						game.ChangeTurn(FIRST_PLAYER);

						break;

					
					}// switch (Game.GetTurn())

					/*try{

						result = GetInfo(comboboxArms, comboboxDirection);

					}
					catch (char* s){

						MessageBox(hWnd, s, s, NULL);

						break;
					}

					SendInfo(listboxInfo, result);*/
				}// if (!Game.IsOver())
				else
				{
				EnableAll(wndws,FALSE);
				}
				
				
				break;

			}//switch (LOWORD(wParam)){

		case ID_BTN_START:

			if (HIWORD(wParam) == BN_CLICKED)
			{
				EnableAll(wndws, TRUE);

			}// if (HIWORD(wParam) == BN_CLICKED)


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

int GetPlayerShield(const HWND &combobox)
{
	int pos = ComboBox_GetCurSel(combobox);

	if (pos == CB_ERR)
		{
			throw "Choose block";
		}// if (pos == CB_ERR)

	return pos;

}

string GetInfo(const HWND &comboboxArms, const HWND &comboboxDirection)
{
	
	string result = "Hit: ";

	//auto pos = ComboBox_GetCurSel(comboboxArms);

	//if (pos == CB_ERR)
	//{
	//	throw "Choose arm";
	//}// if (pos == CB_ERR)

	//result += arms[pos];

	//result += " in: ";

	//pos = ComboBox_GetCurSel(comboboxDirection);

	//if (pos == CB_ERR)
	//{
	//	throw "Choose level";
	//}// if (pos == CB_ERR)


	////result += direction[pos];

	return result;
}// string GetInfo(const HWND &comboboxArms, const HWND &comboboxDirection)

void EnableAll(vector<HWND> &wndws, const BOOL &enable)
{
	ui i;

	for (i = 0; i < wndws.size()-1; i++)
	{
		EnableWindow(wndws[i], enable);
	}//

	EnableWindow(wndws[i], !enable);
}

