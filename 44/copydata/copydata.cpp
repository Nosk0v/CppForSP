// 2019 ReVoL Primer Template
// copydata.cpp
// ОТИ НИЯУ МИФИ
// 1ПО-00Д
// Пономарев Владимир Вадимович
// Системное программирование
// SY-108. Data Copy
// 01.01.2000

#include "copydata.h"
#include "..\ccreate.h"

// посылает данные
void SendData() {
}

// получило данные
void GetData(PCOPYDATASTRUCT pcd) {
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmIdent = 0, wmEvent = 0;
    switch (message) {
    case WM_COMMAND:
        wmIdent = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmIdent) {
        case CMD_SEND:
            if (wmEvent == BN_CLICKED) {
                SendData();
            }
            break;
        case CMD_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_COPYDATA:
        GetData((PCOPYDATASTRUCT)(LPVOID)lParam);
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COPYDATA));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "COPYDATA";
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
    CCreateButton(hInstance, hWnd1, WL2, WT1, BTW, BTH, CMD_SEND, tahoma, "Send");
    CCreateButton(hInstance, hWnd1, WL2, WT3, BTW, BTH, CMD_EXIT, tahoma, "Close");
    SendMessage(hWndOut, EM_LIMITTEXT, MAX_TEXT, 0);
    SendMessage(hWndIn, EM_LIMITTEXT, MAX_TEXT, 0);
    // начальные значения буыеров вывода
    if (myname == 0) {
        SetWindowTextA(hWndOut, "0123456789");
    } else {
        SetWindowTextA(hWndOut, "ABCDEFGH");
    }
    return 1;
}

int InitInstance(HINSTANCE hInstance) {
    DWORD CX = (GetSystemMetrics(SM_CXFULLSCREEN) - MWW) / 2;
    DWORD CY = (GetSystemMetrics(SM_CYFULLSCREEN) - MWH) / 2;
    hWnd1 = CreateWindow("COPYDATA", "CopyData", 0x80c80000, CX, CY, MWW, MWH, 0, 0, hInstance, 0);
    if (!hWnd1) return 0;
    ShowWindow(hWnd1, SW_NORMAL);
    SetWindowText(hWnd1, name[myname]);
    return CreateControls(hInstance);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    hInst = hInstance;
    sprintf((char*)name[0], "First CopyData");
    sprintf((char*)name[1], "Second CopyData");
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
