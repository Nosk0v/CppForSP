// 2019 ReVoL Primer Template
// memory.cpp
// Системное программирование
// SY-106. Управление памятью
// Милюков Александр Васильевич
// 30.05.2024

#include "memory.h"
#include <windows.h>
#include <stdio.h>

extern DWORD page;
extern int block;

int any(DWORD value) { return 1; }
int isa(DWORD value, DWORD mask) { return (value & mask) == mask; }

void ShowProtect(FILE* stream, DWORD value) {
    fprintf(stream, "Prot: ");
    if (value == 0) {
        fprintf(stream, "NONE");
    } else {
        if (isa(value, PAGE_NOACCESS)) fprintf(stream, "NOACCESS ");
        if (isa(value, PAGE_READONLY)) fprintf(stream, "READONLY ");
        if (isa(value, PAGE_READWRITE)) fprintf(stream, "READWRITE ");
        if (isa(value, PAGE_WRITECOPY)) fprintf(stream, "WRITECOPY ");
        if (isa(value, PAGE_EXECUTE)) fprintf(stream, "EXECUTE ");
        if (isa(value, PAGE_EXECUTE_READ)) fprintf(stream, "EXECUTE_READ ");
        if (isa(value, PAGE_EXECUTE_READWRITE)) fprintf(stream, "EXECUTE_READWRITE ");
        if (isa(value, PAGE_EXECUTE_WRITECOPY)) fprintf(stream, "EXECUTE_WRITECOPY ");
        if (isa(value, PAGE_WRITECOMBINE)) fprintf(stream, "WRITECOMBINE ");
        if (isa(value, PAGE_NOCACHE)) fprintf(stream, "NOCACHE ");
        if (isa(value, PAGE_GUARD)) fprintf(stream, "GUARD ");
    }
    fprintf(stream, "\n");
}

void ShowState(FILE* stream, DWORD value) {
    fprintf(stream, "Stat: ");
    if (value == 0) {
        fprintf(stream, "NONE");
    } else {
        if (isa(value, MEM_FREE)) fprintf(stream, "FREE ");
        if (isa(value, MEM_RESERVE)) fprintf(stream, "RESERVE ");
        if (isa(value, MEM_COMMIT)) fprintf(stream, "COMMIT ");
    }
    fprintf(stream, "\n");
}

void ShowType(FILE* stream, DWORD value) {
    fprintf(stream, "Type: ");
    if (value == 0) {
        fprintf(stream, "NONE");
    } else {
        if (isa(value, MEM_IMAGE)) fprintf(stream, "IMAGE ");
        if (isa(value, MEM_MAPPED)) fprintf(stream, "MAPPED ");
        if (isa(value, MEM_PRIVATE)) fprintf(stream, "PRIVATE ");
    }
    fprintf(stream, "\n");
}

DWORD ShowMem(FILE* stream, HANDLE process, DWORD addr) {
    MEMORY_BASIC_INFORMATION mbi;
    DWORD result = VirtualQueryEx(process, (LPCVOID)addr, &mbi, page / 8);
    if (result == 0) return 0x80000000;

    DWORD size = mbi.RegionSize;
    fprintf(stream, "%d\n", ++block);
    fprintf(stream, "Addr: 0x%p\n", (void*)addr);
    fprintf(stream, "Base: 0x%p\n", mbi.AllocationBase);
    fprintf(stream, "Size: 0x%x\n", size);
    
    ShowProtect(stream, mbi.AllocationProtect);
    ShowState(stream, mbi.State);
    ShowType(stream, mbi.Type);
    
    fprintf(stream, "\n");
    return size;
}

void ExploreProcessMemory(DWORD processId) {
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (process == NULL) {
        printf("Could not open process: %d\n", processId);
        return;
    }

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    page = si.dwPageSize;

    DWORD addr = 0;
    DWORD count = 0;
    while (addr < 0x80000000 && count < 1000) {
        DWORD size = ShowMem(stdout, process, addr);
        addr += size;
        count++;
    }

    printf("Total blocks: %d\n", block);
    printf("Total iterations: %d\n", count);

    CloseHandle(process);
}

int main() {
    // Создаем процесс блокнота
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    if (!CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Could not create process.\n");
        return 1;
    }

    // Исследуем память процесса блокнота
    ExploreProcessMemory(pi.dwProcessId);

    // Ждем завершения процесса блокнота
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Закрываем дескрипторы процесса и потока
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}