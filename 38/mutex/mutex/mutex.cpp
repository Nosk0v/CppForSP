// 2018 ReVoL Primer Template
// mutex.cpp
// Милюков Александр Васильевич 363
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include <stdio.h>

#define MAXW 3 // число итераций

// путь к разделяемому файлу
char path[32] = "C:\\mutex\\Debug\\share.txt";
char buff[32] = "";

// функция для открытия файла для добавления
HANDLE openFile(const char* filePath) {
    HANDLE file = CreateFile(filePath, FILE_APPEND_DATA, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) return file;
    return CreateFile(filePath, FILE_APPEND_DATA, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
}

// основная функция
void mainf(int n) {
    int i = 0;
    HANDLE file = 0, mutex = 0;
    DWORD written = 0, err = 0;

    // создаем мьютекс
    mutex = CreateMutex(NULL, FALSE, "sharefile");
    if (mutex == NULL) {
        err = GetLastError();
        sprintf(buff, "Mutex error in process #%d due to %d", n, err);
        MessageBoxA(NULL, buff, "Mutex creation", MB_OK);
        return;
    } else {
        err = GetLastError();
        if (err == ERROR_ALREADY_EXISTS) {
            sprintf(buff, "Mutex exists in process #%d", n);
        } else {
            sprintf(buff, "Mutex created in process #%d", n);
        }
        MessageBoxA(NULL, buff, "Mutex creation", MB_OK);
    }

    // захватываем мьютекс
    WaitForSingleObject(mutex, INFINITE);

    // цикл записи строк
    for (i = 1; i <= MAXW; i++) {
        file = openFile(path);
        if (file == INVALID_HANDLE_VALUE) {
            err = GetLastError();
            sprintf(buff, "Process #%d failed due to %d\n", n, err);
            MessageBoxA(NULL, buff, "Error open file", MB_OK);
            return;
        }

        if (i == MAXW) {
            sprintf(buff, "%d\r\n", n);
            WriteFile(file, buff, 3, &written, NULL);
        } else {
            sprintf(buff, "%d", n);
            WriteFile(file, buff, 1, &written, NULL);
        }

        Sleep(1);
        FlushFileBuffers(file);
        CloseHandle(file);

        sprintf(buff, "Iteration %d in process #%d", i, n);
        MessageBoxA(NULL, buff, "Iteration", MB_OK);
    }

    // освобождаем мьютекс
    ReleaseMutex(mutex);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        MessageBoxA(NULL, "Usage: mutex.exe <process_number>", "Error", MB_OK);
        return 1;
    }

    int processNumber = atoi(argv[1]);
    mainf(processNumber);
    return 0;
}

