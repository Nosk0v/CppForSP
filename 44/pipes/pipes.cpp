// 2019 ReVoL Primer Template
// pipes.cpp
// ОТИ НИЯУ МИФИ
// 1ПО-00Д
// Пономарев Владимир Вадимович
// Системное программирование
// SY-108. pipes
// 01.01.2000

#include "pipes.h"
#include "..\ccreate.h"

// поток сервера, ожидающий подключения
DWORD WINAPI ServerThread(LPVOID lpVoid) {
    return 0;
}

// создает канал и запускает поток
void CreatePipe() {
}

// подключается к каналу, записывает и читает его
void WritePipe() {
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmIdent = 0, wmEvent = 0;
    switch (message) {
    case WM_COMMAND:
        wmIdent = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmIdent) {
        case CMD_EXIT:
            DestroyWindow(hWnd);
            break;
        case CMD_WAIT:
            if (wmEvent == BN_CLICKED) {
                CreatePipe();
            }
            break;
        case CMD_WRIT:
            if (wmEvent == BN_CLICKED) {
                WritePipe();
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM RegisterMyClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PIPES));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "PIPESAPP";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassEx(&wcex);
}

// создает элементы управления
int CreateControls(HINSTANCE hInstance) {
    int ccy = WT1 + BIS;
    tahoma = CCreateFont(hWnd1, "Tahoma", 9);
    hWndOut = CCreateLabel1(hInstance, hWnd1, WL1, LT1, LBW, LBH, tahoma, OUTLABEL);
    hWndOut = CCreateEditML(hInstance, hWnd1, WL1, WT1, EDW, EDH, 0, tahoma, "");
    hWndIn = CCreateLabel1(hInstance, hWnd1, WL1, LT2, LBW, LBH, tahoma, INPLABEL);
    hWndIn = CCreateEditML(hInstance, hWnd1, WL1, WT2, EDW, EDH, 0, tahoma, "");
    CCreateButton(hInstance, hWnd1, WL2, WT1, BTW, BTH, CMD_WAIT, tahoma, "Wait"); ccy = WT1 + BIS;
    CCreateButton(hInstance, hWnd1, WL2, ccy, BTW, BTH, CMD_WRIT, tahoma, "Write");
    CCreateButton(hInstance, hWnd1, WL2, WT3, BTW, BTH, CMD_EXIT, tahoma, "Close");
    SendMessage(hWndOut, EM_LIMITTEXT, MAX_TEXT, 0);
    SendMessage(hWndIn, EM_LIMITTEXT, MAX_TEXT, 0);
    return 1;
}

int InitInstance(HINSTANCE hInstance) {
    SetLastError(0);
    DWORD CX = (GetSystemMetrics(SM_CXFULLSCREEN) - MWW) / 2;
    DWORD CY = (GetSystemMetrics(SM_CYFULLSCREEN) - MWH) / 2;
    hWnd1 = CreateWindow("PIPESAPP", name[PipeUnknown], 0x80c80000, CX, CY, MWW, MWH, 0, 0, hInstance, 0);
    if (!hWnd1) return 0;
    ShowWindow(hWnd1, SW_NORMAL);
    SetWindowText(hWnd1, name[myname]);
    return CreateControls(hInstance);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    hInst = hInstance;
    sprintf((char*)name[PipeUnknown], "Unknown pipe");
    sprintf((char*)name[PipeClient], "Client pipe");
    sprintf((char*)name[PipeServer], "Server pipe");
    if (!RegisterMyClass(hInstance)) return 0;
    if (!InitInstance(hInstance)) return 0;
    SetFocus(hWndOut);
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_KEYDOWN && msg.wParam == 27) SendMessage(hWnd1, WM_DESTROY, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
