// 2019 ReVoL Primer Template
// ddeapp.h
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include "targetver.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dde.h>

// ������������ ������ ���������
#define MAX_TEXT 62

// ���������� �� ���������
//#define DEFAPP ""
#define DEFAPP "Excel"
//#define DEFAPP "Self"

// ���� �� ���������
//#define DEFTOPIC ""
//#define DEFTOPIC "System"
#define DEFTOPIC "[dde.xls]dde"
//#define DEFTOPIC "Self"

// ������� ������ �� ���������
//#define DEFITEM ""
//#define DEFITEM "r1c1:r1c2"
#define DEFITEM "r2c1:r2c3"
//#define DEFITEM "Topics"

// ���������� ������ �� ���������
//#define DEFSEND ""
#define DEFSEND "2\t3\t=A2*B2"

// �����
ATOM atomApp, atomTopic, atomItem, atomAdvise, atomPoke, atomA, atomB;

// ��������� ������ DDE
DDEDATA ddedata;
DDEACK ack;
DDEADVISE advise;
DDEPOKE poke;
// ��������� �� ��������� ������ DDE
DDEDATA FAR* lpData;
DDEACK FAR* lpAck;
DDEADVISE FAR* lpAdvise;
DDEPOKE FAR* lpPoke;
char far* lpCommand;
// �����
int fRelease = 0;
int fResponse = 0;
int fAckReq = 0;
// ����������� ������
HGLOBAL hGlobal;
// ��� ����������
UINT format;
// ���� ����������
LPARAM lParam;
// ������������ ��������
LRESULT lResult = 0;
// ��������� � ������
int SelectedItem = -1;

// ��������� ����������
enum ddestates { IDLE, INITIATE, TALK };
ddestates state = IDLE;
// �������� ���������
LPCSTR statenames[] = { "Idle", "Initiate", "Conversation" };

// ����� ����������
void onStartApp() {
}

// ���� ����������
void onCloseApp() {
    GlobalDeleteAtom(atomA);
    GlobalDeleteAtom(atomB);
    GlobalDeleteAtom(atomApp);
    GlobalDeleteAtom(atomTopic);
    GlobalDeleteAtom(atomItem);
    GlobalDeleteAtom(atomAdvise);
    GlobalDeleteAtom(atomPoke);
}

// �����
#define DDEUnknown 0
#define DDEClient 1
#define DDEServer 2
#define DDEBoth 3

// �����������
HWND hWndDummy = 0;
HWND hWndApp = 0;
HWND hWndTopic = 0;
HWND hWndItem = 0;
HWND hWndInAck = 0;
HWND hWndInitiate = 0;
HWND hWndMine = 0;
HWND hWndPartner = 0;
HWND hWndState = 0;
HWND hWndAck = 0;
HWND hWndTerm = 0;

// ���������
void SetState(ddestates newstate);
void ShowHWnd1();
void SetHWnd2(HWND hWnd);
void ClearDataAndAck();
void GetListItemData(HWND hWnd, int index);

// �������
#define INITIAT 224
#define DECLINE 225
#define ACCEPTC 226
#define REQUEST 227
#define ADVISEW 228
#define ADVISEH 229
#define UNADVIS 230
#define POKESVR 231
#define EXECUTE 232
#define TERMINA 233
#define DECLINI 234
#define ACCEPTI 235
#define DELETEA 236
#define DELETET 237

// �������������� �������
#define W0W 800 // ������ ����
#define W0H 468 // ������ ����
#define BWW 100 // ������ ������
#define DW1 100
#define DW2 242
#define BSP (DW2 - BWW - BWW)
#define DT1 6
#define DL1 14
#define DL2 (DL1 + BWW + BSP)
#define DL3 (DL1 + DW2 + 16)
#define DL4 (DL3 + BWW + BSP)
#define DL5 (DL3 + DW2 + 16)
#define DL6 (DL5 + BWW + BSP)
#define DH1 17
#define DH2 19
#define DH3 138
#define DH4 52
#define DH5 68
#define DH6 100
#define DH7 92
