// 2018 ReVoL Primer Template
// reader.cpp
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

#define INFINITE 0xFFFFFFFF  // Максимальное время ожидания

// Функция чтения из файла и вывода на экран
void read_and_print(FILE *file) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fflush(stdout);
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

    FILE *quefile = fopen("que.txt", "r");
    FILE *bakfile = fopen("bak.txt", "r");

    if (quefile == NULL || bakfile == NULL) {
        printf("Error opening files.");
        return 1;
    }

    const int attempts = 10; // Число попыток чтения
    const int delay = 1000; // Задержка между чтениями в миллисекундах

    for (int i = 0; i < attempts; i++) {
        // Захватываем мьютекс que
        WaitForSingleObject(quemutex, INFINITE);
        printf("Contents of que.txt:\n");
        read_and_print(quefile);
        ReleaseMutex(quemutex);

        // Захватываем мьютекс bak
        WaitForSingleObject(bakmutex, INFINITE);
        printf("Contents of bak.txt:\n");
        read_and_print(bakfile);
        ReleaseMutex(bakmutex);

        Sleep(delay);
    }

    fclose(quefile);
    fclose(bakfile);

    CloseHandle(quemutex);
    CloseHandle(bakmutex);

    return 0;
}
