// 2019 ReVoL Primer Template
// clipboard.cpp
// ��� ���� ����
// 1��-00�
// ��������� �������� ���������
// ��������� ����������������
// SY-108. Clipboard
// 01.01.2000

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <string.h>
#include <windows.h>

// ����������� ������
HGLOBAL hGlobal = 0;
// ��������� �� ����������� ������ ��������� ����
char FAR* lpData = 0;
// ������������� ������� ������ ����� ����������
UINT myformat = 0;
// ������������ ��������� ������ ����� ����������
struct mydata {
    int x;
} data;

// ���������� ����� � ����� ������
int SetText() {
    int result = 0;
closec:
    return result;
}

// ��������� ����� �� ������ ������
int GetText() {
    int result = 0;
closec:
    return result;
}

// ���������� ��������� ������ � ����� ������
int SetStruct() {
    int result = 0;
closec:
    return result;
}

// ��������� ��������� ������ �� ����� ������
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
