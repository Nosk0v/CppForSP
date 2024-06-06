// 2019 ReVoL Primer Template
// clipboard.cpp
// ОТИ НИЯУ МИФИ
// 1ПО-00Д
// Пономарев Владимир Вадимович
// Системное программирование
// SY-108. Clipboard
// 01.01.2000

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <string.h>
#include <windows.h>

// разделяемая память
HGLOBAL hGlobal = 0;
// указатель на разделяемую память заданного типа
char FAR* lpData = 0;
// идентификатор формата данных этого приложения
UINT myformat = 0;
// передаваемая структура данных этого приложения
struct mydata {
    int x;
} data;

// записывает текст в буфер обмена
int SetText() {
    int result = 0;
closec:
    return result;
}

// извлекает текст из буфера обмена
int GetText() {
    int result = 0;
closec:
    return result;
}

// записывает структуру данных в буфер обмена
int SetStruct() {
    int result = 0;
closec:
    return result;
}

// извлекает структуру данных из буфер обмена
int GetStruct() {
    int result = 0;
closec:
    return result;
}

int main(void) {
//    SetText();
//    GetText();
//    SetStruct();
//    GetStruct();
}
