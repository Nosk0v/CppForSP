// 2018 ReVoL Primer Template
// except.cpp
// Милюков Александр Васильевич
// SY-103.
// 01.01.2000

#include "except.h"
#include <windows.h>
#include <iostream>

#define EXCEPT_MALLOC 0xE0000001

void memory_alloc(size_t size);
void stackov(unsigned int &level);
void violation(unsigned int address);
void violationf(unsigned int address);
void integer_overflow(unsigned int number);
void float_error();
int filter(unsigned int code, PEXCEPTION_POINTERS ep);

int main() {
    unsigned int result = 1000000000;
    __try {
        memory_alloc(result);
        stackov(result);
        violation(result);
        violationf(result);
        integer_overflow(result);
        float_error();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        unsigned int code = GetExceptionCode();
        switch (code) {
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
                printf("Division by zero raised 0x%X in main\n", code);
                break;
            case EXCEPTION_INT_OVERFLOW:
                printf("Integer overflow raised 0x%X in main\n", code);
                break;
            case EXCEPTION_ACCESS_VIOLATION:
                printf("Access violation raised 0x%X in main\n", code);
                break;
            case EXCEPTION_STACK_OVERFLOW:
                printf("Stack overflow raised 0x%X in main\n", code);
                break;
            default:
                printf("Exception raised 0x%X in main\n", code);
        }
    }
    std::cout << "result = " << result << std::endl;
    return 0;
}

void memory_alloc(size_t size) {
    char* mem_alloc = nullptr;
    __try {
        mem_alloc = (char*)malloc(1 + size);
        if (mem_alloc) {
            printf("Memory allocated at %p\n", mem_alloc);
        } else {
            RaiseException(EXCEPT_MALLOC, 0, 0, 0);
        }
        size = 1000000000 / size;
    } __finally {
        printf("Memory alloc finally\n");
        if (mem_alloc) {
            free(mem_alloc);
            printf("Memory freed\n");
        }
    }
}

void stackov(unsigned int &level) {
    if (++level > 0) stackov(level);
}

void violation(unsigned int address) {
    ((char*)address)[0] = 0;
}

int filter(unsigned int code, PEXCEPTION_POINTERS ep) {
    if (code == EXCEPTION_ACCESS_VIOLATION) {
        int op = ep->ExceptionRecord->ExceptionInformation[0];
        int ad = ep->ExceptionRecord->ExceptionInformation[1];
        if (op == 0) {
            printf("Violation to read at 0x%p\n", (void*)ad);
        } else {
            printf("Violation to write at 0x%p\n", (void*)ad);
        }
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

void violationf(unsigned int address) {
    __try {
        violation(address);
    } __except (filter(GetExceptionCode(), GetExceptionInformation())) {
    }
}

void integer_overflow(unsigned int number) {
    unsigned int result = number;
    result += number;
    printf("Result = %u\n", result);
    __asm {
        into
    }
}

void float_error() {
    float x = 0.0f, y = FLT_MIN, z = FLT_MAX;
    x = z + z;
    unsigned int result = _clearfp();
    if (result & _EM_INEXACT) printf("Inexact\n");
    if (result & _EM_UNDERFLOW) printf("Underflow\n");
    if (result & _EM_OVERFLOW) printf("Overflow\n");
    if (result & _EM_ZERODIVIDE) printf("Divide by zero\n");
    if (result & _EM_DENORMAL) printf("Denormal\n");
    if (result & _EM_INVALID) printf("Invalid operation\n");
    printf("x = %g\n", x);
}