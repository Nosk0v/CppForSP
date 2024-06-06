#include <iostream>
#include <windows.h>
#include <strsafe.h>

void ShowError(LPCSTR functionName, DWORD errorCode) {
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPSTR)lpMsgBuf) + lstrlen(functionName) + 40) * sizeof(CHAR)); 
    StringCchPrintf((LPSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(CHAR),
        TEXT("%s failed with error %d: %s"), 
        functionName, errorCode, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

void TestFunction() {
    // Пример вызова функции, которая может вызвать ошибку
    if (!DeleteFile("nonexistentfile.txt")) {
        ShowError("DeleteFile", GetLastError());
    }
}

int main() {
    TestFunction();
    return 0;
}