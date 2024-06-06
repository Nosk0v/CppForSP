// 2019 ReVoL Primer Template
// copydata.h
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

// ��������� CopyData
COPYDATASTRUCT cd;
// �������
#define CDCMD 1

// ������������ ���������
struct copydata {
    char buffer[(MAX_TEXT) + 2];
} data;

// ������� ���������
void cleardata(copydata & d) {
    for (int i = 0; i <= (MAX_TEXT + 1); i++) d.buffer[i] = 0;
}

// �������
#define CMD_SEND 131
