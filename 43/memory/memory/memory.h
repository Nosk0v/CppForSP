// 2019 ReVoL Primer Template
// memory.h

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <psapi.h>
#include <tchar.h>

// ����� ������
int block = 0;
// ����� ������ �����
int count = 0;
// ������ ��������
DWORD page = 0;
// ����� ��� ���� � �����
TCHAR buf[MAX_PATH] = {};

// �������� ����� ��������
int any(DWORD value) { return 1; }

// ���������� �������� ������
void ShowProtect(FILE * stream, DWORD value) {
}

// ���������� ��������� ������
void ShowState(FILE * stream, DWORD value) {
    fprintf(stream, "Stat: ");
    if (value == 0) {
        fprintf(stream, "NONE");
    } else {
        //if (isa(value, MEM_FREE)) fprintf(stream, "FREE");
    }
    fprintf(stream, "\n");
}

// ���������� ��� ������
void ShowType(FILE * stream, DWORD value) {
}

// ���������� ������
DWORD ShowMem(FILE * stream, DWORD addr) {
    return 0;
}

// ��������
void mainf(void);

// �������� �������
int main(void) {
    __try {
        mainf();
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        unsigned int code = GetExceptionCode();
        if (code == EXCEPTION_ACCESS_VIOLATION) {
            printf("\nAccess violation.\n");
        } else if (code == EXCEPTION_STACK_OVERFLOW) {
            printf("\nStack overflow.\n");
        } else {
            printf("\nException raised.\n");
        }
    }
    return 0;
}
