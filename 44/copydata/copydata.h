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

// максимальный размер сообщения
#define MAX_TEXT 62

// структура CopyData
COPYDATASTRUCT cd;
// команда
#define CDCMD 1

// пересылаемая структура
struct copydata {
    char buffer[(MAX_TEXT) + 2];
} data;

// очищает структуру
void cleardata(copydata & d) {
    for (int i = 0; i <= (MAX_TEXT + 1); i++) d.buffer[i] = 0;
}

// команды
#define CMD_SEND 131
