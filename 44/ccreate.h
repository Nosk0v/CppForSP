// ReVoL 2018 Primer Template
// ccreate.h
// Общий файл!

// код последней ошибки
DWORD dwError = 0;
// размер данных
DWORD dwSize = 0;
// число записанных байт
DWORD dwWritten = 0;
// число прочитанных байт
DWORD dwRead = 0;
// число байт (прочитанных или записанных)
DWORD dwBytes = 0;
// результат операции
int result = 0;

// дескриптор приложения
HINSTANCE hInst;
// основные дескрипторы окон
HWND hWnd1 = 0, hWnd2 = 0;
// дескрипторы полей ввода/вывода
HWND hWndOut, hWndIn;
// шрифт приложения
HFONT tahoma;

// названия окон
char name[4][32] = { "", "", "", "" };
// номер моего окна (мое имя)
int myname = 0;
// устанавливает название окна (мое имя)
void SetName(int newname) {
    myname = newname;
    SetWindowText(hWnd1, name[myname]);
}

// буферы
char bufa[2 + MAX_TEXT] = "";
char bufb[2 + MAX_TEXT] = "";
char bufc[2 + MAX_TEXT] = "";

// очищает буфер
void clearbuf(LPSTR buffer) {
    for (int i = 0; i <= (MAX_TEXT + 1);i++) buffer[i] = 0;
}

// выводит информационное сообщение
void ShowMessage(LPCSTR message) {
    MessageBox(hWnd1, message, name[myname], MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
}

// выводит сообщение об ошибке по номеру winerror.h
// source выводится как заголовок окна сообщения
void ShowError(LPCSTR source, DWORD code) {
    HLOCAL hLocal = 0;
    BOOL fOk = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, code, 1049, (LPSTR)&hLocal, 0, 0);
    if (fOk) {
        MessageBox(0, (LPCSTR)hLocal, source, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        LocalFree(hLocal);
    } else {
        sprintf(bufc, "Error FormatMessage %d.", GetLastError());
        MessageBox(0, bufc, 0, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
    }
}

#define MWW 408 // ширина окна
#define MWH 338 // высота окна
#define LBW 100 // ширина надписи
#define LBH 17  // высота надписи
#define EDW 270 // ширина поля
#define EDH 80  // высота поля
#define BTW 80  // ширина кнопки
#define BTH 27  // высота кнопки
#define BIS (BTH + 3) // между кнопками
#define WL1 14  // слева для первой колонки
#define WL2 299 // слева для кнопки
#define WT1 26  // сверху первое поле
#define WT2 187 // сверху второе поле
#define WT3 (WT2 + EDH - BTH) // кнопка Close
#define LIS 18  // между надписью и полем
#define LT1 (WT1 - LIS) // первая надпись
#define LT2 (WT2 - LIS) // вторая надпись

// команда завершения
#define CMD_EXIT 199

// текст надписей
#define OUTLABEL "String to send:"
#define INPLABEL "Received string:"

// устанавливает шрифт в окне
void SetTheFont(HWND hWnd, HFONT font) {
    SendMessage(hWnd, WM_SETFONT, (WPARAM)font, 0);
}

// создает окно
HWND CCreateStatic1(HINSTANCE hinst, HWND P, int L, int T, int W, int H) {
    HWND hWnd = CreateWindow("STATIC", 0, 0x50800000, L, T, W, H, P, 0, hinst, 0);
    return hWnd;
}

// создает надпись
HWND CCreateLabel1(HINSTANCE hinst, HWND P, int L, int T, int W, int H, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("STATIC", text, 0x50000000, L, T, W, H, P, 0, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// создает однострочное поле ввода
HWND CCreateEditSL(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("EDIT", text, 0x50810000, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// создает однострочное поле ввода
HWND CCreateEditSS(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("EDIT", text, 0x50810800, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// создает многострочное поле ввода
HWND CCreateEditML(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("EDIT", text, 0x50810004, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// создает список
HWND CCreateListB1(HINSTANCE hInst, HWND P, int L, int T, int W, int H, HFONT font) {
    int style = WS_TABSTOP | WS_VISIBLE | WS_BORDER | WS_CHILD | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT;
    HWND hWnd = CreateWindow("LISTBOX", 0, style, L, T, W, H, P, (HMENU)0, hInst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// создает кнопку
HWND CCreateButton(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("BUTTON", text, 0x50014000, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// создает шрифт
HFONT CCreateFont(HWND hWnd, LPCSTR name, int size) {
    return CreateFont(-MulDiv(size, GetDeviceCaps(GetDC(hWnd), LOGPIXELSY),72), 0, 0, 0, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, 0, name);
}
