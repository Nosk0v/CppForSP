// 2019 ReVoL Primer Template
// clipwapp.h
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include "targetver.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "resource.h"

#define MAX_TEXT 62

HWND hWndBMP = 0;
HWND hWndErr = 0;
HBITMAP hBitmap = 0;
HDC hDC = 0;
HDC CDC = 0;

// команды
#define SHOWB1 131
#define SHOWB2 132
#define COPYTO 133
#define PASTEF 134
// размер окна картинки
#define IMAGES 249

// прототип
void DisplayBitmap(HBITMAP bitmap);
