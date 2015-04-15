#pragma once

#include "Utils.h"

extern HINSTANCE hinst;

char *controlNames[] = {
	{ "BUTTON" },
	{ "EDIT" },
	{ "LISTBOX" }
};

HWND comBttnAdd, comBttnToSingle, comBttnToAll, editName, editFee, editLimit, listboxFrom, listboxTo,
	groupBttnName;


//MapEmployee in;
//MapEmployee out;

vector<Employee> in;
vector<Employee> out;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message){

	case WM_CREATE: 
		
		editName = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE , 10, 20, EDIT_BOX_H_SIZE, EDIT_BOX_V_SIZE, hWnd, (HMENU)EDIT_BOX_NAME, hinst, NULL);
		SendMessage(editName, EM_SETLIMITTEXT, NAME_SIZE, NULL);

		editFee = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE , 10, 50, EDIT_BOX_H_SIZE, EDIT_BOX_V_SIZE, hWnd, (HMENU)EDIT_BOX_FEE, hinst, NULL);
		SendMessage(editFee, EM_SETLIMITTEXT, FEE_SIZE, NULL);

		comBttnAdd = CreateWindowEx(NULL, controlNames[BUTTON], "��������",
			WS_CHILD | WS_VISIBLE, 10, 200, BTN_H_SIZE, BTN_V_SIZE, hWnd, (HMENU)COM_BTN_ADD, hinst, NULL);

		comBttnToSingle = CreateWindowEx(NULL, controlNames[BUTTON], "���������",
			WS_CHILD | WS_VISIBLE, EDIT_BOX_H_SIZE + 173, 150, BTN_H_SIZE - 35, BTN_V_SIZE, hWnd, (HMENU)COM_BTN_TO_SINGLE, hinst, NULL);

		comBttnToAll = CreateWindowEx(NULL, controlNames[BUTTON], "��������� ���",
			WS_CHILD | WS_VISIBLE, EDIT_BOX_H_SIZE + 173, 200, BTN_H_SIZE - 35, BTN_V_SIZE, hWnd, (HMENU)COM_BTN_TO_ALL, hinst, NULL);

		listboxFrom = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "", 
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT | LBS_NOTIFY,
			20 + EDIT_BOX_H_SIZE, 20, 150, 400, hWnd, (HMENU)LIST_BOX_FROM, hinst, NULL);

		listboxTo = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[LISTBOX], "", 
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT,
			(20 + EDIT_BOX_H_SIZE) * 2, 20, 150, 400, hWnd, (HMENU)LIST_BOX_TO, hinst, NULL);

		editLimit = CreateWindowEx(WS_EX_CLIENTEDGE, controlNames[EDIT], "",
			WS_CHILD | WS_VISIBLE, EDIT_BOX_H_SIZE + 185, 20, EDIT_BOX_V_SIZE * 3, EDIT_BOX_V_SIZE, hWnd, (HMENU)EDIT_BOX_LIMIT, hinst, NULL);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)){

		case LIST_BOX_FROM:

			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				Move(hWnd);

			}// if (HIWORD(wParam) == LBN_DBLCLK)

			break;
			
		case COM_BTN_ADD:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				AddInfo(hWnd);

			}// if (HIWORD(wParam) == BN_CLICKED)

			break;

		case COM_BTN_TO_SINGLE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				Move(hWnd);

			}// if (HIWORD(wParam) == BN_CLICKED)

			break; 
			/* */

		case COM_BTN_TO_ALL:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				SendMessage(listboxFrom, LB_SETSEL, TRUE, -1);

				Move(hWnd);

				SendMessage(listboxFrom, LB_SETSEL, FALSE, -1);

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

int FindCenterDesktopH(void)
{
	// �������� ����� �������� �����
	HWND hDesktop = GetDesktopWindow();

	// ���������� ��� �������� ��������� ����� �������� �����
	RECT rectDesktop;

	// ���������� ���� �������� ����� � ����������
	GetWindowRect(hDesktop, &rectDesktop);

	return (rectDesktop.right - rectDesktop.left) / 2;

}// int FindCenterDesktopH(void)

int FindCenterDesktopV(void)
{
	// �������� ����� �������� �����
	HWND hDesktop = GetDesktopWindow();

	// ���������� ��� �������� ��������� ����� �������� �����
	RECT rectDesktop;

	// ���������� ���� �������� ����� � ����������
	GetWindowRect(hDesktop, &rectDesktop);

	return (rectDesktop.bottom - rectDesktop.top) / 2;
}// int FindCenterDesktopV(void

void Move(HWND hWnd)
{
	int lengthName;
	double feeDbl;
	char *fee;
	string nameToBox;

	int countOfSelElems;
	int *indexesOfElems;

	lengthName = GetWindowTextLength(editLimit);

	if (lengthName){

		fee = new char[lengthName + 2];

		GetWindowText(editLimit, fee, lengthName + 1);

		strcat(fee, ".");

		try{
			feeDbl = stod(fee);
		}
		catch (...)
		{
			MessageBox(hWnd, "����������� �����", "������� �� �����", 0);

			SetWindowText(editLimit, "");

			delete fee;

			return;

		}// try catch

	}else{

		feeDbl = 0.;

	}// if else

	// ������ ���������� ��������� ��������� �� ������ ��������� � �������
	countOfSelElems = SendMessage(listboxFrom, LB_GETSELCOUNT, NULL, NULL);

	// �������� ������ ��� ������, ��� ����� ��������� �������
	indexesOfElems = new int[countOfSelElems];

	// �������� � ������������ ������ ������ ��������� ���������
	SendMessage(listboxFrom, LB_GETSELITEMS, countOfSelElems, (LPARAM)indexesOfElems);
	
	// ��������� ������ (����� � ������ ���������� �������� ������ (<))
	// ��������� ����������� ������ �� ������������
	sort(in.begin(), in.end());

	// �������� �� ������� �������� ���������
	for (int i = countOfSelElems-1; i >=0 ; i--)
	{
		// ���� �������� ���� �������� ������ �������� ������������
		if (in[indexesOfElems[i]].GetFee() <= feeDbl){

			// ������� � ����������� ������ �������������� ��������
			// (������� �������)
			out.push_back(*(in.begin() + indexesOfElems[i]));

			// � �������� ������� ������� ��������� �������
			in.erase(in.begin() + indexesOfElems[i]);

			// ������� �� ��������� ��������� ��������������� ������
			SendMessage(listboxFrom, LB_DELETESTRING, indexesOfElems[i], NULL);

			// ������ � ����������� �������� ��������������� ������
			SendMessage(listboxTo, LB_ADDSTRING, NULL,
				(LPARAM)out.back().GetInfoInStr().c_str());

		}// if (in[indexesOfElems[i]].GetFee() <= feeDbl)
	
	}// for (int i = 0; i < countOfSelElems; i++)

	// ����������� ������ ��-��� ������������� ������� ��������
	delete [] indexesOfElems;

}// void Move(HWND hWnd)

void AddInfo(HWND hWnd)
{
	int lengthName;
	double feeDbl;
	string name;
	string fee;
	string nameToBox;
	
	lengthName = GetWindowTextLength(editName);

	if (lengthName){

		//name = new char[lengthName + 1];

		GetWindowText(editName, const_cast<LPSTR>(name.c_str())/* name*/, lengthName + 1);

	}
	else{
		
		//delete name;
		
		MessageBox(hWnd, "������� ������� ����������", "�� ������� �������", 0);

		return;
	}// if else

	lengthName = GetWindowTextLength(editFee);

	if (lengthName){

		//fee = new char[lengthName + 2];

		GetWindowText(editFee, const_cast<LPSTR>(fee.c_str()), lengthName + 1);

		//strcat(fee, ".");

		//fee += ".";

		try{
			feeDbl = stod(fee);
		}
		catch (std::invalid_argument& ia)
		{
			std::cerr << "Invalid argument: " << ia.what() << '\n';

			MessageBox(hWnd, "����������� �����", "������� �� �����", 0);

			SetWindowText(editFee, "");

			//delete name;

			//delete fee;

			return;

		}// try catch

	}else{

		MessageBox(hWnd, "������� ��������", "�� ������� ��������", 0);

		//delete name;

		return;

	}// if else
	
	// ���� � ������� ��� ���� �������(�������� �� ������������)
	if (in.size()){

		//���� � ������� ���������� �� �����
		vector<Employee>::iterator it = std::find(in.begin(), in.end(), Employee(name.c_str(), false));

		if (it != in.end()){
			// ��� ���������� �������� �������
			MessageBox(hWnd, "����� �������� ��� ���� � ������", "������", 0);

			return;
		}// if (it != in.end())

	}// if (in.size())
		
	//������ ������� � ����� ������
	in.push_back(Employee(name.c_str(), feeDbl));

	// �������� ������ �� ������ ���������� ��������
	nameToBox = in.back().GetInfoInStr();

	// ������ ������ � ��������
	SendMessage(listboxFrom, LB_ADDSTRING, NULL, (LPARAM)nameToBox.c_str());

	SetWindowText(editName, "");
	SetWindowText(editFee, "");

}// void AddInfo(HWND hWnd)