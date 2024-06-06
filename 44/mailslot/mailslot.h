// 2019 ReVoL Primer Template
// mailslot.h
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include "targetver.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ������������ ������ ���������
#define MAX_TEXT 62

// ����� (���) ��������� �����
LPCSTR TestSlot = TEXT("\\\\.\\mailslot\\testslot");
// ���������� ��������� ����� �������
HANDLE hServer = 0;
// ���������� ��������� ����� �������
HANDLE hClient = 0;
// ��������� ��������� �����
DWORD dwNextSize = 0, dwCount = 0;

// �����
#define MSUnknown 0
#define MSServer 1
#define MSClient 2

// �������
#define CMD_OPN 131
#define CMD_CHK 132
#define CMD_PUT 133
#define CMD_GET 134
