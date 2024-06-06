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

// максимальный размер сообщения
#define MAX_TEXT 62

// адрес (имя) канала
LPCSTR TestPipe = TEXT("\\\\.\\pipe\\testpipe");
// дескриптор сервера
HANDLE hPipe = 0;
// дескриптор клиента
HANDLE hFile = 0;

// имена
#define PipeUnknown 0
#define PipeClient 1
#define PipeServer 2

// команды
#define CMD_WAIT 131
#define CMD_WRIT 132
