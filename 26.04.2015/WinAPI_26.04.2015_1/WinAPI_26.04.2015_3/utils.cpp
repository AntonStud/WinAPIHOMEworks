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

vector<HWND> wndws;

Game game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	HDC hdc;

	string result = "";

	static int flag = -1;

	string finalMessage;

	switch (message){

	case WM_CREATE:
		
		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[COMBOBOX], "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			LIST_X, LIST_Y * 2 + BTN_V_SIZE, BTN_H_SIZE, LIST_V_SIZE, hWnd, (HMENU)ID_COMBO_ARM, hinst, NULL));

		for (ui i = 0; i < game.GetPlayer().GetAmmo().size(); i++)
		{
			SendMessage(wndws[wndws.size() - 1], CB_ADDSTRING, NULL, (LPARAM)game.GetPlayer().GetAmmo()[i]->GetName().c_str());

		}// for (ui i = 0; i < arms.size(); i++)

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

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE | ES_READONLY | ES_CENTER,
			LIST_X*2 + BTN_H_SIZE, LIST_Y * 2 + BTN_V_SIZE , HEALTH_SIZE, BTN_V_SIZE, 
			hWnd, (HMENU)ID_EDIT_HEALTH_PLAYER, hinst, NULL));

		wndws.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE | ES_READONLY | ES_CENTER,
			LIST_X * 4 + LIST_H_SIZE + BTN_H_SIZE + HEALTH_SIZE, LIST_Y * 2 + BTN_V_SIZE, HEALTH_SIZE, BTN_V_SIZE,
			hWnd, (HMENU)ID_EDIT_HEALTH_COMPUTER, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "You",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS,
			LIST_X * 2 + BTN_H_SIZE, LIST_Y + BTN_V_SIZE, HEALTH_SIZE, BTN_V_SIZE,
			hWnd, (HMENU)ID_STATIC_YOU, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "PC",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS,
			LIST_X * 4 + LIST_H_SIZE + BTN_H_SIZE + HEALTH_SIZE, LIST_Y + BTN_V_SIZE, HEALTH_SIZE, BTN_V_SIZE,
			hWnd, (HMENU)ID_STATIC_PC, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "Ammo",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS ,
			LIST_X, LIST_Y + BTN_V_SIZE, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_ARM, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "Direction",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS,
			LIST_X, LIST_Y * 2 + BTN_V_SIZE * 2, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_DIRECT, hinst, NULL));

		wndws.push_back(CreateWindowEx(NULL, controlNames[STATIC], "Block",
			WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WORDELLIPSIS,
			LIST_X, LIST_Y * 3 + BTN_V_SIZE * 3, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)ID_STATIC_BLOCK, hinst, NULL));

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
					switch (game.GetTurn())
					{
					case FIRST_PLAYER:

						PlayerTurn(hWnd, wndws[BUTTONS_LIST_INFO], game);

						break;
					case COMPUTER:

						ComputerTurn(hWnd, wndws[BUTTONS_LIST_INFO], game);

						break;

					}// switch (Game.GetTurn())

					if (game.IsOver())
					{
						finalMessage = "You";

						finalMessage += game.GetTurn() == COMPUTER ? " win" : " loose";

						SendMessage(wndws[BUTTONS_LIST_INFO], LB_INSERTSTRING, 0, (LPARAM)finalMessage.c_str());

						SendMessage(wndws[BUTTONS_LIST_INFO], LB_INSERTSTRING, 0, (LPARAM)("The game is over"));

						EnableAll(wndws, FALSE);

					}// if (game.IsOver())
				
				break;

			}//switch (LOWORD(wParam)){

		case ID_BTN_START:

			if (HIWORD(wParam) == BN_CLICKED)
			{
				game.Init();

				SetWindowText(wndws[BUTTONS_EDIT_HEALTH_PLAYER], std::to_string(game.GetPlayer().GetHealth()).c_str());

				SetWindowText(wndws[BUTTONS_EDIT_HEALTH_COMPUTER], std::to_string(game.GetComputer().GetHealth()).c_str());

				EnableAll(wndws, TRUE);

				EnableWindow(wndws[BUTTONS_COMBO_BLOCK], FALSE);

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

}// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
int FindCenterDesktopV(void)
{
	// Получаем хэндл рабочего стола
	HWND hDesktop = GetDesktopWindow();

	// Переменная для хранения координат углов рабочего стола
	RECT rectDesktop;

	// Записываем углы рабочего стола в переменную
	GetWindowRect(hDesktop, &rectDesktop);

	return (rectDesktop.bottom - rectDesktop.top) / 2;
}// int FindCenterDesktopV(void)
//-----------------------------------------------------------------------------
void SendInfo(const HWND &listboxInfo, const string &result)
{

	SendMessage(listboxInfo, LB_ADDSTRING, NULL, (LPARAM)result.c_str());

}//void SendInfo(const HWND &listboxInfo)
//-----------------------------------------------------------------------------
int GetPlayerChoise(const HWND &combobox)
{
	int pos = ComboBox_GetCurSel(combobox);

	if (pos == CB_ERR)
		{
			throw "Choose option";
		}// if (pos == CB_ERR)

	return pos;

}// int GetPlayerShield(const HWND &combobox)
//-----------------------------------------------------------------------------
void EnableAll(vector<HWND> &wndws, const BOOL &enable)
{
	ui i;

	for (i = 0; i < wndws.size()-1; i++)
	{
		EnableWindow(wndws[i], enable);
	}//

	EnableWindow(wndws[i], !enable);

}// void EnableAll(vector<HWND> &wndws, const BOOL &enable)
//-----------------------------------------------------------------------------

void PlayerTurn(const HWND &hWnd, const HWND &listboxInfo, Game &game)
{
	int hit, shield, direct, health, damage;
	string result, dam;

	try{

		hit = GetPlayerChoise(wndws[BUTTONS_COMBO_ARM]);

	}
	catch (char* s)
	{

		MessageBox(hWnd, s, s, NULL);

		return;
	}// try catch

	try{

		direct = GetPlayerChoise(wndws[BUTTONS_COMBO_DIRECT]);

	}
	catch (char* s)
	{

		MessageBox(hWnd, s, s, NULL);

		return;
	}// try catch

	shield = game.GetComputer().ChooseBlock();

	damage = game.GetPlayer().CalculateDamage(hit, direct, shield);

	health = game.GetComputer().GetHealth() - damage;

	game.GetComputer().SetHealth(health);

	SetWindowText(wndws[BUTTONS_EDIT_HEALTH_COMPUTER], std::to_string(game.GetComputer().GetHealth()).c_str());

	result = "You hit by " + game.GetPlayer().GetAmmo()[hit]->GetName() +
		" in " + game.GetPlayer().GetBlocks()[direct]->GetName() + ". PC blocked "
		+ game.GetComputer().GetBlocks()[shield]->GetName();
	
	dam = "The damage is " + std::to_string(damage);

	SendMessage(listboxInfo, LB_INSERTSTRING, 0, (LPARAM)dam.c_str());

	SendMessage(listboxInfo, LB_INSERTSTRING, 0, (LPARAM)result.c_str());

	game.SetEnd(game.GetComputer().GetHealth());

	game.ChangeTurn(COMPUTER);

	EnableWindow(wndws[BUTTONS_COMBO_BLOCK], TRUE);

	EnableWindow(wndws[BUTTONS_COMBO_ARM], FALSE);

	EnableWindow(wndws[BUTTONS_COMBO_DIRECT], FALSE);

}// void PlayerTurn()
//-----------------------------------------------------------------------------
void ComputerTurn(const HWND &hWnd, const HWND &listboxInfo, Game &game)
{
	int hit, shield, direct, health, damage;

	string result, dam;

	hit = game.GetComputer().ChooseArm();

	direct = game.GetComputer().ChooseDirect();

	try{

		shield = GetPlayerChoise(wndws[BUTTONS_COMBO_BLOCK]);

	}
	catch (char* s)
	{

		MessageBox(hWnd, s, s, NULL);

		return;
	}

	damage = game.GetComputer().CalculateDamage(hit, direct, shield);

	health = game.GetPlayer().GetHealth() - damage;

	game.GetPlayer().SetHealth(health);

	SetWindowText(wndws[BUTTONS_EDIT_HEALTH_PLAYER], std::to_string(game.GetPlayer().GetHealth()).c_str());

	result = "PC hit by " + game.GetComputer().GetAmmo()[hit]->GetName() +
		" in " + game.GetComputer().GetBlocks()[direct]->GetName() + ". You blocked "
		+ game.GetPlayer().GetBlocks()[shield]->GetName();

	dam = "The damage is " + std::to_string(damage);

	SendMessage(listboxInfo, LB_INSERTSTRING, 0, (LPARAM)dam.c_str());

	SendMessage(listboxInfo, LB_INSERTSTRING, 0, (LPARAM)result.c_str());

	game.SetEnd(game.GetPlayer().GetHealth());

	game.ChangeTurn(FIRST_PLAYER);

	EnableWindow(wndws[BUTTONS_COMBO_BLOCK], FALSE);

	EnableWindow(wndws[BUTTONS_COMBO_ARM], TRUE);

	EnableWindow(wndws[BUTTONS_COMBO_DIRECT], TRUE);

}// void ComputerTurn()
//-----------------------------------------------------------------------------
