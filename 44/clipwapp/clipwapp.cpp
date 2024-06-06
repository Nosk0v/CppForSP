// 2019 ReVoL Primer Template
// clipwapp.cpp
// ОТИ НИЯУ МИФИ
// 1ПО-00Д
// Пономарев Владимир Вадимович
// Системное программирование
// SY-108. clipboard
// 01.01.2000

#include "clipwapp.h"
#include "..\ccreate.h"

// копирует в буфер обмена
void CopyToClipboard() {
}

// извлекает из буфера обмена
void PasteFromClipboard() {
}

// выводит картинку
void DisplayBitmap(HBITMAP bitmap) {
    // контекст окна картинки
    hDC = GetDC(hWndBMP);
    // совместимый контекст для картинки
    CDC = CreateCompatibleDC(hDC);
    // выбираем картинку в контекст
    SelectObject(CDC, bitmap);
    // копируем из совместимого контекста в окно картинки
    BitBlt(hDC, 0, 0, IMAGES, IMAGES, CDC, 0, 0, SRCCOPY);
    // освобождаем совместимый контекст
    DeleteObject(CDC);
    UpdateWindow(hWndBMP);
}

// показывает картинку приложения
void ShowBMP1() {
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BMP1));
    DisplayBitmap(hBitmap);
}

// показывает картинку приложения
void ShowBMP2() {
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BMP2));
    DisplayBitmap(hBitmap);
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
        case SHOWB1:
            if (wmEvent == BN_CLICKED) {
                SetWindowText(hWndErr, "BMP1");
                ShowBMP1();
            }
            break;
        case SHOWB2:
            if (wmEvent == BN_CLICKED) {
                SetWindowText(hWndErr, "BMP2");
                ShowBMP2();
            }
            break;
        case COPYTO:
            if (wmEvent == BN_CLICKED) {
                SetWindowText(hWndErr, "Copy");
                CopyToClipboard();
            }
            break;
        case PASTEF:
            if (wmEvent == BN_CLICKED) {
                SetWindowText(hWndErr, "Paste");
                PasteFromClipboard();
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        if (hBitmap) {
            DisplayBitmap(hBitmap);
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
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
    wcex.hInstance = hInst;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIPWAPP));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "CLIPWAPP";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassEx(&wcex);
}

// создает элементы управления
int CreateControls(HINSTANCE hInstance) {
    tahoma = CCreateFont(hWnd1, "Tahoma", 9);
    hWndBMP = CCreateStatic1(hInstance, hWnd1, 16, 16, 2 + IMAGES, 2 + IMAGES);
    hWndErr = CCreateLabel1(hInstance, hWnd1, 16, IMAGES + 16 + 8, IMAGES, 17, tahoma, "");
    hWndOut = CCreateButton(hInstance, hWnd1, WL2, 16, BTW, BTH, SHOWB1, tahoma, "BMP 1");
    CCreateButton(hInstance, hWnd1, WL2, 46, BTW, BTH, SHOWB2, tahoma, "BMP 2");
    CCreateButton(hInstance, hWnd1, WL2, 76, BTW, BTH, COPYTO, tahoma, "Copy to");
    CCreateButton(hInstance, hWnd1, WL2, 106, BTW, BTH, PASTEF, tahoma, "Paste from");
    CCreateButton(hInstance, hWnd1, WL2, WT3, BTW, BTH, CMD_EXIT, tahoma, "Close");
    return 1;
}

int InitInstance(HINSTANCE hInstance) {
    DWORD CX = (GetSystemMetrics(SM_CXFULLSCREEN) - MWW) / 2;
    DWORD CY = (GetSystemMetrics(SM_CYFULLSCREEN) - MWH) / 2;
    hWnd1 = CreateWindow("CLIPWAPP", "Clipboard App", 0x80c80000, CX, CY, MWW, MWH, 0, 0, hInstance, 0);
    if (!hWnd1) return 0;
    // выбираем картинку из ресурсов этого приложения
    if (FindWindow("CLIPWAPP", name[0])) {
        myname = 1;
    } else {
        myname = 0;
    }
    ShowWindow(hWnd1, SW_NORMAL);
    SetWindowText(hWnd1, name[myname]);
    return CreateControls(hInstance);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    hInst = hInstance;
    sprintf((char*)name[0], "First App");
    sprintf((char*)name[1], "Second App");
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
