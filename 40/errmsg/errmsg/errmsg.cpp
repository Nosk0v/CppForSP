// 2018 ReVoL Primer Template
// errmsg.cpp
// Милюков Александр Васильевич
// 363 КТК
// SY-102. 
// 30.05.2024

char file_to_delete[] = "c:\\windows\\system";
#include "errmsg.h"
#include <windows.h>
#include <cstdio>
#include <string>

void icons() {
    int icons[] = { MB_ICONINFORMATION, MB_ICONWARNING, MB_ICONERROR, MB_ICONQUESTION };
    const char* iconNames[] = { "MB_ICONINFORMATION", "MB_ICONWARNING", "MB_ICONERROR", "MB_ICONQUESTION" };

    for (int i = 0; i < 4; ++i) {
        char msg[50];
        sprintf(msg, "Сообщение номер %d - %s", i + 1, iconNames[i]);
        MessageBoxA(NULL, msg, "Test", MB_OK | icons[i]);
    }
}

void frombuf() {
    char bufa[] = "Сообщение из буфера ANSI";
    wchar_t bufw[] = L"Сообщение из буфера Unicode";

    MessageBoxA(NULL, bufa, "ANSI", MB_OK | MB_ICONEXCLAMATION);
    MessageBoxW(NULL, bufw, L"Unicode", MB_OK | MB_ICONEXCLAMATION);
}

void yesno() {
    char bufa[64];
    char file_to_delete[] = "example.txt";
    sprintf(bufa, "Удалить файл %s?", file_to_delete);

    int response = MessageBoxA(NULL, bufa, "Подтвердите", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

    if (response == IDYES) {
        MessageBoxA(NULL, "Файл удален", "Результат", MB_OK | MB_ICONINFORMATION);
    } else {
        MessageBoxA(NULL, "Отменено пользователем", "Результат", MB_OK | MB_ICONINFORMATION);
    }
}

void yesnocancel() {
    char bufa[64];
    char file_to_delete[] = "example.txt";
    sprintf(bufa, "Удалить файл %s?", file_to_delete);

    int response;
    do {
        response = MessageBoxA(NULL, bufa, "Подтвердите", MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON3);
        if (response == IDYES) {
            MessageBoxA(NULL, "Файл удален", "Результат", MB_OK | MB_ICONINFORMATION);
        } else if (response == IDNO) {
            MessageBoxA(NULL, "Отменено пользователем", "Результат", MB_OK | MB_ICONINFORMATION);
        }
    } while (response != IDCANCEL);
}

void format_from_system(DWORD errorCode, DWORD locale) {
    HLOCAL hLocal = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&hLocal,
        0,
        NULL
    );

    if (hLocal != NULL) {
        MessageBoxA(NULL, (LPSTR)hLocal, "System Error", MB_OK | MB_ICONERROR);
        LocalFree(hLocal);
    } else {
        DWORD err = GetLastError();
        char errorMsg[100];
        sprintf(errorMsg, "Error FormatMessage. Code: %lu", err);
        MessageBoxA(NULL, errorMsg, "Error", MB_OK | MB_ICONERROR);
    }
}

void format_sys_msg() {
    SetLastError(ERROR_FILE_NOT_FOUND);
    DWORD dwError = GetLastError();
    format_from_system(dwError, 1049);
    format_from_system(dwError, 1033);
    format_from_system(0, 1049);
}

void format_with_param() {
    DWORD_PTR params[] = {
        (DWORD_PTR)"A",
        (DWORD_PTR)"diskette",
        (DWORD_PTR)"0000-1111",
    };

    HLOCAL hLocal = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
        NULL,
        ERROR_WRONG_DISK,
        1049,
        (LPSTR)&hLocal,
        0,
        (va_list*)params
    );

    if (hLocal != NULL) {
        MessageBoxA(NULL, (LPSTR)hLocal, "Formatted Message", MB_OK | MB_ICONERROR);
        LocalFree(hLocal);
    } else {
        DWORD err = GetLastError();
        char errorMsg[100];
        sprintf(errorMsg, "Error FormatMessage. Code: %lu", err);
        MessageBoxA(NULL, errorMsg, "Error", MB_OK | MB_ICONERROR);
    }
}

void format_dll_msg(DWORD msgID) {
    HMODULE hModule = LoadLibraryA("kernel32.dll");
    if (hModule == NULL) {
        DWORD err = GetLastError();
        char errorMsg[100];
        sprintf(errorMsg, "Error LoadLibrary. Code: %lu", err);
        MessageBoxA(NULL, errorMsg, "Error", MB_OK | MB_ICONERROR);
        return;
    }

    HLOCAL hLocal = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
        hModule,
        msgID,
        1049,
        (LPSTR)&hLocal,
        0,
        NULL
    );

    if (hLocal != NULL) {
        MessageBoxA(NULL, (LPSTR)hLocal, "Formatted Message from DLL", MB_OK | MB_ICONERROR);
        LocalFree(hLocal);
    } else {
        DWORD err = GetLastError();
        char errorMsg[100];
        sprintf(errorMsg, "Error FormatMessage. Code: %lu", err);
        MessageBoxA(NULL, errorMsg, "Error", MB_OK | MB_ICONERROR);
    }

    FreeLibrary(hModule);
}

void format_from_string() {
    char buf[] = "Error %1 occurred";
    DWORD_PTR params[] = {
        (DWORD_PTR)"diskette",
    };

    HLOCAL hLocal = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
        buf,
        0,
        0,
        (LPSTR)&hLocal,
        0,
        (va_list*)params
    );

    if (hLocal != NULL) {
        MessageBoxA(NULL, (LPSTR)hLocal, "Formatted Message from String", MB_OK | MB_ICONERROR);
        LocalFree(hLocal);
    } else {
        DWORD err = GetLastError();
        char errorMsg[100];
        sprintf(errorMsg, "Error FormatMessage. Code: %lu", err);
        MessageBoxA(NULL, errorMsg, "Error", MB_OK | MB_ICONERROR);
    }
}

int main() {
    icons();
    frombuf();
    yesno();
    yesnocancel();
    format_sys_msg();
    format_with_param();
    format_dll_msg(5);
    format_from_string();

    return 0;
}
