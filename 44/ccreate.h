// ReVoL 2018 Primer Template
// ccreate.h
// ����� ����!

// ��� ��������� ������
DWORD dwError = 0;
// ������ ������
DWORD dwSize = 0;
// ����� ���������� ����
DWORD dwWritten = 0;
// ����� ����������� ����
DWORD dwRead = 0;
// ����� ���� (����������� ��� ����������)
DWORD dwBytes = 0;
// ��������� ��������
int result = 0;

// ���������� ����������
HINSTANCE hInst;
// �������� ����������� ����
HWND hWnd1 = 0, hWnd2 = 0;
// ����������� ����� �����/������
HWND hWndOut, hWndIn;
// ����� ����������
HFONT tahoma;

// �������� ����
char name[4][32] = { "", "", "", "" };
// ����� ����� ���� (��� ���)
int myname = 0;
// ������������� �������� ���� (��� ���)
void SetName(int newname) {
    myname = newname;
    SetWindowText(hWnd1, name[myname]);
}

// ������
char bufa[2 + MAX_TEXT] = "";
char bufb[2 + MAX_TEXT] = "";
char bufc[2 + MAX_TEXT] = "";

// ������� �����
void clearbuf(LPSTR buffer) {
    for (int i = 0; i <= (MAX_TEXT + 1);i++) buffer[i] = 0;
}

// ������� �������������� ���������
void ShowMessage(LPCSTR message) {
    MessageBox(hWnd1, message, name[myname], MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
}

// ������� ��������� �� ������ �� ������ winerror.h
// source ��������� ��� ��������� ���� ���������
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

#define MWW 408 // ������ ����
#define MWH 338 // ������ ����
#define LBW 100 // ������ �������
#define LBH 17  // ������ �������
#define EDW 270 // ������ ����
#define EDH 80  // ������ ����
#define BTW 80  // ������ ������
#define BTH 27  // ������ ������
#define BIS (BTH + 3) // ����� ��������
#define WL1 14  // ����� ��� ������ �������
#define WL2 299 // ����� ��� ������
#define WT1 26  // ������ ������ ����
#define WT2 187 // ������ ������ ����
#define WT3 (WT2 + EDH - BTH) // ������ Close
#define LIS 18  // ����� �������� � �����
#define LT1 (WT1 - LIS) // ������ �������
#define LT2 (WT2 - LIS) // ������ �������

// ������� ����������
#define CMD_EXIT 199

// ����� ��������
#define OUTLABEL "String to send:"
#define INPLABEL "Received string:"

// ������������� ����� � ����
void SetTheFont(HWND hWnd, HFONT font) {
    SendMessage(hWnd, WM_SETFONT, (WPARAM)font, 0);
}

// ������� ����
HWND CCreateStatic1(HINSTANCE hinst, HWND P, int L, int T, int W, int H) {
    HWND hWnd = CreateWindow("STATIC", 0, 0x50800000, L, T, W, H, P, 0, hinst, 0);
    return hWnd;
}

// ������� �������
HWND CCreateLabel1(HINSTANCE hinst, HWND P, int L, int T, int W, int H, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("STATIC", text, 0x50000000, L, T, W, H, P, 0, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// ������� ������������ ���� �����
HWND CCreateEditSL(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("EDIT", text, 0x50810000, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// ������� ������������ ���� �����
HWND CCreateEditSS(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("EDIT", text, 0x50810800, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// ������� ������������� ���� �����
HWND CCreateEditML(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("EDIT", text, 0x50810004, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// ������� ������
HWND CCreateListB1(HINSTANCE hInst, HWND P, int L, int T, int W, int H, HFONT font) {
    int style = WS_TABSTOP | WS_VISIBLE | WS_BORDER | WS_CHILD | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT;
    HWND hWnd = CreateWindow("LISTBOX", 0, style, L, T, W, H, P, (HMENU)0, hInst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// ������� ������
HWND CCreateButton(HINSTANCE hinst, HWND P, int L, int T, int W, int H, int id, HFONT font, LPCSTR text) {
    HWND hWnd = CreateWindow("BUTTON", text, 0x50014000, L, T, W, H, P, (HMENU)id, hinst, 0);
    if (hWnd) SetTheFont(hWnd, font);
    return hWnd;
}

// ������� �����
HFONT CCreateFont(HWND hWnd, LPCSTR name, int size) {
    return CreateFont(-MulDiv(size, GetDeviceCaps(GetDC(hWnd), LOGPIXELSY),72), 0, 0, 0, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, 0, name);
}
