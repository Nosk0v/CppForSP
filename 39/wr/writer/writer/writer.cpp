// 2018 ReVoL Primer Template
// writer.cpp
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writer.h"

#define INFINITE 0xFFFFFFFF  // Максимальное время ожидания

// Функция записи в файл
void writen(FILE *file, const char *message) {
    fprintf(file, "%s", message);
    fflush(file);
}

int main() {
    HANDLE bakmutex = CreateMutex(NULL, FALSE, "bakfile");
    if (bakmutex == NULL) {
        printf("bakmutex error due to %d", GetLastError());
        return 1;
    }

    HANDLE quemutex = CreateMutex(NULL, FALSE, "quefile");
    if (quemutex == NULL) {
        printf("quemutex error due to %d", GetLastError());
        return 1;
    }

    FILE *quefile = fopen("que.txt", "a+");
    FILE *bakfile = fopen("bak.txt", "a+");

    if (quefile == NULL || bakfile == NULL) {
        printf("Error opening files.");
        return 1;
    }

    const int attempts = 10; // Число попыток записи
    const int delay = 1000; // Задержка между записями в миллисекундах
    char quebuff[20];
    int n = 1;

    for (int i = 0; i < attempts; i++) {
        sprintf(quebuff, "%02d-%03d\r\n", n, (i + 1));

        // Захватываем мьютекс que
        WaitForSingleObject(quemutex, INFINITE);
        writen(quefile, quebuff);
        ReleaseMutex(quemutex);

        // Захватываем мьютекс bak
        WaitForSingleObject(bakmutex, INFINITE);
        writen(bakfile, quebuff);
        ReleaseMutex(bakmutex);

        printf("%s", quebuff);

        Sleep(delay);
    }

    fclose(quefile);
    fclose(bakfile);

    CloseHandle(quemutex);
    CloseHandle(bakmutex);

    return 0;
}
