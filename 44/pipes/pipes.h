// 2019 ReVoL Primer Template
// pipes.h
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

// ����� (���) ������
LPCSTR TestPipe = TEXT("\\\\.\\pipe\\testpipe");
// ���������� �������
HANDLE hPipe = 0;
// ���������� �������
HANDLE hFile = 0;

// �����
#define PipeUnknown 0
#define PipeClient 1
#define PipeServer 2

// �������
#define CMD_WAIT 131
#define CMD_WRIT 132
