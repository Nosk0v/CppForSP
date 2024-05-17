#include <windows.h>
#include <iostream>

#define MAXW 1
#define MAXT 2

HANDLE threads[MAXT];
int share = 0;
volatile LONG lock = 0;

DWORD WINAPI ThreadFunction(LPVOID id) {
    int threadNum = (int)id;
    for (int i = 0; i < MAXW; i++) {
        while (InterlockedCompareExchange(&lock, 1, 0) != 0) {
            // Spin until the lock is acquired
        }
        share++;
        std::cout << "Thread " << threadNum << " updated share to " << share << std::endl;
        InterlockedExchange(&lock, 0);
    }
    return 0;
}

int main() {
    for (int i = 0; i < MAXT; i++) {
        threads[i] = CreateThread(NULL, 0, ThreadFunction, (LPVOID)i, 0, NULL);
    }

    WaitForMultipleObjects(MAXT, threads, TRUE, INFINITE);

    for (int i = 0; i < MAXT; i++) {
        CloseHandle(threads[i]);
    }

    std::cout << "Final value of share: " << share << std::endl;
    return 0;
}
