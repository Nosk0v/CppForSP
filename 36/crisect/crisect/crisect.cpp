// 2018 ReVoL Primer Template
// crisect.cpp
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "crisect.h"

#define MAXW 1
#define MAXT 2

HANDLE threads[MAXT];
int share = 0;
CRITICAL_SECTION cs;

DWORD WINAPI ThreadFunction(LPVOID id) {
    int threadNum = (int)id;
    for (int i = 0; i < MAXW; i++) {
        EnterCriticalSection(&cs);
        share++;
        std::cout << "Thread " << threadNum << " updated share to " << share << std::endl;
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main() {
    InitializeCriticalSection(&cs);

    for (int i = 0; i < MAXT; i++) {
        threads[i] = CreateThread(NULL, 0, ThreadFunction, (LPVOID)i, 0, NULL);
    }

    WaitForMultipleObjects(MAXT, threads, TRUE, INFINITE);

    for (int i = 0; i < MAXT; i++) {
        CloseHandle(threads[i]);
    }

    std::cout << "Final value of share: " << share << std::endl;

    DeleteCriticalSection(&cs);
    return 0;
}
