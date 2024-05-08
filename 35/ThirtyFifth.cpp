#include <windows.h>

// Работа сделана на виртуалке с win 11

// Функция создания дочернего процесса для запуска блокнота и открытия файла
void onStart()
{

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    TCHAR cmd[] = TEXT("notepad C:\\process\\a.txt");

    CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}

void onStop()
{

    TerminateProcess(pi.hProcess, 0);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

// Функция запуска процесса с измененными параметрами окна
void onStartWithWindowParams()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Устанавливаем параметры окна
    si.dwX = 300;
    si.dwY = 200;
    si.dwXSize = 400;
    si.dwYSize = 400;
    si.dwFlags = STARTF_USESIZE | STARTF_USEPOSITION;

    TCHAR cmd[] = TEXT("notepad");

    CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, TEXT("C:\\process"), &si, &pi);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    onStart();
    onStop();
    onStartWithWindowParams();
    return 0;
}
