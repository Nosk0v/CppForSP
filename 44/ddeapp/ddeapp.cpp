// 2019 ReVoL Primer Template
// ddeapp.cpp
// ��� ���� ����
// 1��-00�
// ��������� �������� ���������
// ��������� ����������������
// SY-108. DDE
// 01.01.2000

#include "ddeapp.h"
#include "..\ccreate.h"

// ������ ���������� ��������
void InitiateConversation() {
    if (state == TALK) {
        return;
    }
    // � - ������
    SetName(DDEClient);
    // ����� ���������
    SetState(INITIATE);
    // ���� ����������
    dwSize = GetWindowText(hWndApp, bufa, MAX_TEXT);
    if (dwSize == 0) {
        atomApp = GlobalAddAtomA(NULL);
    } else {
        atomApp = GlobalAddAtomA(bufa);
    }
    // ���� ����
    dwSize = GetWindowText(hWndTopic, bufb, MAX_TEXT);
    if (dwSize == 0) {
        atomTopic = GlobalAddAtomA(NULL);
    } else {
        atomTopic = GlobalAddAtomA(bufb);
    }
    // ����� ������ ����������
    // HWND_BROADCAST - ������� ���� �����, hWnd1 - ���������� ����� ����
    // ������ �������� ��� hWnd1 � ������� �������������
    SetLastError(0);
    lResult = SendMessage(HWND_BROADCAST, WM_DDE_INITIATE, (WPARAM)hWnd1, MAKELONG(atomApp, atomTopic));
    dwError = GetLastError();
    if (dwError) {
        //ShowError("InitiateConversation.SenMessage", dwError);
    }
}

// ������� ������ ������������� ���������
void OnAckInInitiate(WPARAM wParam, LPARAM lParam) {
    if (hWnd1 == (HWND)wParam) {
        return;
    }
    // �������� �����
    atomA = (ATOM)LOWORD(lParam);
    atomB = (ATOM)HIWORD(lParam);
    // �������������� �����
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    GlobalGetAtomName(atomB, bufb, MAX_TEXT);
    // ��������� ������ ������
    sprintf(bufc, "0x%p %s %s ", (int*)wParam, bufa, bufb);
    // ��������� � ������
    SetLastError(0);
    lResult = SendMessage(hWndInAck, LB_SETCURSEL, SendMessage(hWndInAck, LB_ADDSTRING, 0, (LPARAM)bufc), 0);
    dwError = GetLastError();
    if (dwError) {
        //ShowError("OnAckInInitiate.SenMessage", dwError);
    }
}

// ��������� ��������
void AcceptConversation() {
    if (state == TALK) {
        ShowMessage("AcceptConversation: You are in a conversation.");
        return;
    }
    // ���������� ������� ������
    SelectedItem = SendMessage(hWndInAck, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // ������� ������ �� ������
    GetListItemData(hWndInAck, SelectedItem);
    // ����������
    SetWindowText(hWndApp, bufa);
    // ����
    SetWindowText(hWndTopic, bufb);
    // ��������� ���������
    SetState(TALK);
    // hWnd �������
    SetHWnd2(hWndDummy);
    // ������� �� ������
    lResult = SendMessage(hWndInAck, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
    // �������� ��������� �������
    SendMessage(hWndInAck, LB_SELECTSTRING, SendMessage(hWndInAck, LB_GETCOUNT, 0, 0) - 1, 0);
}

// ��������� ��������
void DeclineConversation() {
    if (state == TALK) {
        ShowMessage("You are in a conversation.");
        return;
    }
    // ���������� ������� ������
    SelectedItem = SendMessage(hWndInAck, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // ������� ������ �� ������
    GetListItemData(hWndInAck, SelectedItem);
    // ��������� ��������
    SetLastError(0);
    lResult = PostMessage(hWndDummy, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    dwError = GetLastError();
    if (dwError) {
        ShowError("DeclineConversation.PostMessage", dwError);
    }
    // ������� �� ������
    SendMessage(hWndInAck, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
    // �������� ��������� �������
    SendMessage(hWndInAck, LB_SELECTSTRING, SendMessage(hWndInAck, LB_GETCOUNT, 0, 0) - 1, 0);
}

// ������� ������ ������������� �� ����� �����������
void OnAckInConversation(WPARAM wParam, LPARAM lParam) {
    //ShowMessage("Incoming Ack");
    // ������������� ���������
    UnpackDDElParam(WM_DDE_ACK, lParam, (PUINT)&ack, (PUINT)&atomA);
    // ��������� ���������
    sprintf(bufc, "Ack received:\r\nAck %d\r\nBusy: %d\r\nAppReturnCode: %d\r\nFrom: 0x%p", ack.fAck, ack.fBusy, ack.bAppReturnCode, (int*)wParam);
    // �������
    SetWindowText(hWndAck, bufc);
}

// ������� ������ �����-�� ������������� (��� ���������)
void OnAck(WPARAM wParam, LPARAM lParam) {
    if (state == TALK) {
        // ������ �������������
        OnAckInConversation(wParam, lParam);
    } else {
        // ������������� ���������
        OnAckInInitiate(wParam, lParam);
    }
}

// ������ �������� ������ ������
void SendRequest() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendRequest: You aren't in a conversation.");
        return;
    }
    // ������� ������
    GetWindowText(hWndItem, bufa, MAX_TEXT);
    // ���� ������
    atomItem = GlobalAddAtom(bufa);
    // �������� ������, ������ - �����
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_REQUEST, (WPARAM)hWnd1, PackDDElParam(WM_DDE_REQUEST, CF_TEXT, atomItem));
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendRequest.PostMessage", dwError);
    }
}

// ������ �������� ������ ���������� �����
void SendAdvise(int DeferUpd) {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendAdvise: You aren't in a conversation.");
        return;
    }
    // ������� ������
    GetWindowText(hWndItem, bufa, MAX_TEXT);
    // ���� �����
    atomAdvise = GlobalAddAtom(bufa);
    SetLastError(0);
    // ����������� ������ ��� DDEADVISE
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, sizeof(DDEADVISE));
    if (!hGlobal) {
        ShowError("SendAdvise.GlobalAlloc", GetLastError());
        return;
    }
    SetLastError(0);
    // ��������� ������
    lpAdvise = (DDEADVISE FAR*)GlobalLock(hGlobal);
    if (!lpAdvise) {
        ShowError("SendAdvise.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // ������ ������
    lpAdvise->cfFormat = CF_TEXT;
    // ��������� �������������
    lpAdvise->fAckReq = 1;
    // 0 - ������� �����, ����� ������
    lpAdvise->fDeferUpd = DeferUpd;
    // ������������ ������
    GlobalUnlock(hGlobal);
    // ��������� ���������
    SetLastError(0);
    lParam = PackDDElParam(WM_DDE_ADVISE, (UINT_PTR)hGlobal, atomAdvise);
    if (dwError) {
        ShowError("SendAdvise.PostMessage", dwError);
        // ����������� ������
        GlobalFree(hGlobal);
    }
    // �������� ������
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_ADVISE, (WPARAM)hWnd1, lParam);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendAdvise.PostMessage", dwError);
        // ����������� ������
        GlobalFree(hGlobal);
        // ����������� lParam
        FreeDDElParam(WM_DDE_ADVISE, lParam);
    } else {
        // ������ ���������� ����� ���������
    }
}

// ������ �������� ���������� ���������� �����
void SendUnadvise() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendUnadvise: You aren't in a conversation.");
        return;
    }
    // ������� ����� �����
    GlobalGetAtomName(atomAdvise, bufa, MAX_TEXT);
    // ������� ����� � ����
    SetWindowText(hWndItem, bufa);
    // ������ ���������� �����
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_UNADVISE, (WPARAM)hWnd1, atomAdvise);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendUnadvise.PostMessage", dwError);
    }
}

// ������� ������ ������
void OnData(WPARAM wParam, LPARAM lParam) {
    // ������������� ���������
    UnpackDDElParam(WM_DDE_DATA, lParam, (PUINT)&hGlobal, (PUINT)&atomA);
    // �������� ��� �������� ������
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    if (!hGlobal) {
        //ShowMessage("Incoming Notification");
        // ������ ����������� ���������� �����
        sprintf(bufc, "Data link notification received:\r\nAtom: %s\r\nFrom: 0x%p", bufa, (int*)wParam);
        // �������
        SetWindowText(hWndAck, bufc);
        return;
    }
    // ��������� ������
    SetLastError(0);
    lpData = (DDEDATA FAR*)GlobalLock(hGlobal);
    if (!lpData) {
        ShowError("OnData.GlobalLock", GetLastError());
        // ������������� �������������
        PostMessage((HWND)wParam, WM_DDE_ACK, (WPARAM)hWnd1, PackDDElParam(WM_DDE_ACK, 0, atomA));
        return;
    }
    // ������ ������
    format = lpData->cfFormat;
    if (format != CF_TEXT) {
    }
    // ����� �� ������������ ������
    fRelease = lpData->fRelease;
    // �������� �� ������� �� ������
    fResponse = lpData->fResponse;
    // ��������� �� �������������
    fAckReq = lpData->fAckReq;
    // �������� ������ � �����
    lstrcpy(bufb, (LPCSTR)lpData->Value);
    // ������ ������
    dwSize = strlen(bufb);
    // ������������ ������
    GlobalUnlock(hGlobal);
    // ������� ������ � ���� hWndIn
    SetWindowText(hWndIn, bufb);
    // ��������� ���������
    sprintf(bufc, "Data received (bytes: %d):\r\nFormat: %d\r\nRelease: %d\r\nResponse: %d\r\nAckReq: %d\r\nFrom: 0x%p\r\nAtom: %s", dwSize, format, fRelease, fResponse, fAckReq, (int*)wParam, bufa);
    // �������
    SetWindowText(hWndAck, bufc);
    //ShowMessage("Incoming data");
    if (fRelease) {
        // ����������� ������
        GlobalFree(hGlobal);
    }
    if (fAckReq) {
        // ������������� �������������
        PostMessage((HWND)wParam, WM_DDE_ACK, (WPARAM)hWnd1, PackDDElParam(WM_DDE_ACK, 0x8000, atomA));
    }
}

// ������ �������� ������ �������
void SendPoke() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendPoke: You aren't in a conversation.");
        return;
    }
    // ������� ����� ���� ������ � �����
    GetWindowTextA(hWndOut, bufa, MAX_TEXT);
    // ������ ������
    dwSize = strlen(bufa);
    if (dwSize == 0) {
        ShowMessage("SendPoke: nothing to send.");
        return;
    }
    // ����������� ������ ��� DDEPOKE, 2 ������� ��� CR � LF, ����������� ���� ��������� DDEPOKE
    SetLastError(0);
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, 2 + dwSize + sizeof(DDEPOKE));
    if (!hGlobal) {
        ShowError("SendPoke.GlobalAlloc", GetLastError());
        return;
    }
    // ��������� ������
    SetLastError(0);
    lpPoke = (DDEPOKE FAR*)GlobalLock(hGlobal);
    if (!lpPoke) {
        ShowError("SendPoke.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // ������ ������
    lpPoke->cfFormat = CF_TEXT;
    // ��������� ������������
    lpPoke->fRelease = 1;
    // �������� ������ � DDEPOKE
    lstrcpy((LPSTR)lpPoke->Value, bufa);
    // � ������� CF_TEXT ������ ������ ����������� CR � LF
    lstrcat((LPSTR)lpPoke->Value, (LPSTR)"\r\n");
    // ������������ ������
    GlobalUnlock(hGlobal);
    // ������� ������
    GetWindowText(hWndItem, bufa, MAX_TEXT);
    // ���� ������
    atomPoke = GlobalAddAtom(bufa);
    // ��������� ���������
    lParam = PackDDElParam(WM_DDE_POKE, (UINT)hGlobal, atomPoke);
    // ������ POKE
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_POKE, (WPARAM)hWnd1, lParam);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendPoke.PostMessage", dwError);
        // ����������� ������
        GlobalFree(hGlobal);
        // ����������� lParam
        FreeDDElParam(WM_DDE_POKE, lParam);
    }
}

// ������ �������� ������� �������
void SendExecute() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendExecute: You aren't in a conversation.");
        return;
    }
    // ������� ����� ���� ������ � �����
    GetWindowTextA(hWndOut, bufa, MAX_TEXT);
    // ������ ������
    dwSize = strlen(bufa);
    if (dwSize == 0) {
        ShowMessage("SendExecute: nothing to send.");
        return;
    }
    // ����������� ������ ��� ������ ������
    SetLastError(0);
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, 1 + dwSize);
    if (!hGlobal) {
        ShowError("SendExecute.GlobalAlloc", GetLastError());
        return;
    }
    // ��������� ������
    SetLastError(0);
    lpCommand = (char FAR*)GlobalLock(hGlobal);
    if (!lpCommand) {
        ShowError("SendExecute.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // �������� ������
    lstrcpy((LPSTR)lpCommand, bufa);
    // ������������ ������
    GlobalUnlock(hGlobal);
    // ��������� ���������
    lParam = PackDDElParam(WM_DDE_EXECUTE, 0, (UINT)hGlobal);
    // �������� ������
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_EXECUTE, (WPARAM)hWnd1, lParam);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendExecute.PostMessage", dwError);
        // ����������� ������
        GlobalFree(hGlobal);
        // ����������� lParam
        FreeDDElParam(WM_DDE_ADVISE, lParam);
    }
}

// �������� ����������� �� ��������� ���������
void SendTerminate() {
    ClearDataAndAck();
    if (state == IDLE) {
        ShowMessage("SendTerminate: Nothing to terminate.");
        return;
    }
    if (hWnd2) {
        // �������� ��������� TERMINATE
        PostMessage(hWnd2, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    }
    //// ��� �������
    //SetName(DDEUnknown);
    //// ��������� ���������
    //SetState(IDLE);
    //// ������� ������ ���
    //SetHWnd2(0);
}

// ������ ������ ���������
void OnInitiate(WPARAM wParam, LPARAM lParam) {
    ATOM atomA = (ATOM)LOWORD(lParam);
    ATOM atomB = (ATOM)HIWORD(lParam);
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    GlobalGetAtomName(atomB, bufb, MAX_TEXT);
    // ��������� ���������
    sprintf(bufc, "0x%p %s %s ", (int*)wParam, bufa, bufb);
    // ��������� � ������
    SendMessage(hWndInitiate, LB_SETCURSEL, SendMessage(hWndInitiate, LB_ADDSTRING, 0, (LPARAM)bufc), 0);
}

// ��������� �������� INITIATE
void DeclineIncoming() {
    // ���������� ������� ������
    SelectedItem = SendMessage(hWndInitiate, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // ������� ������ �� ������
    GetListItemData(hWndInitiate, SelectedItem);
    // ��������� �������� ��������
    SetLastError(0);
    lResult = PostMessage(hWndDummy, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    dwError = GetLastError();
    if (dwError) {
        //ShowError("DeclineIncoming.PostMessage", dwError);
    }
    // ������� �� ������
    SendMessage(hWndInitiate, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
}

// ��������� �������� INITIATE
void AcceptIncoming() {
    if (state == TALK) {
        ShowMessage("AcceptIncoming: You are in a conversation.");
        return;
    }
    // ���������� ������� ������
    SelectedItem = SendMessage(hWndInitiate, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // ������� ������ �� ������
    GetListItemData(hWndInitiate, SelectedItem);
    // ����������
    SetWindowText(hWndApp, bufa);
    // ���� ����������
    dwSize = GetWindowText(hWndApp, bufa, MAX_TEXT);
    if (dwSize == 0) {
        atomApp = GlobalAddAtomA(NULL);
    } else {
        atomApp = GlobalAddAtomA(bufa);
    }
    // ����
    SetWindowText(hWndTopic, bufb);
    // ���� ����
    dwSize = GetWindowText(hWndTopic, bufb, MAX_TEXT);
    if (dwSize == 0) {
        atomTopic = GlobalAddAtomA(NULL);
    } else {
        atomTopic = GlobalAddAtomA(bufb);
    }
    // �������� accept
    SetLastError(0);
    lResult = SendMessage(hWndDummy, WM_DDE_ACK, (WPARAM)hWnd1, MAKELONG(atomApp, atomTopic));
    dwError = GetLastError();
    if (dwError) {
        ShowError("AcceptIncoming.SendMessage", dwError);
    } else {
        // � ���� ������, ���� ������ � ������
        if (hWnd1 == hWndDummy) {
            SetName(DDEBoth);
        } else {
            SetName(DDEServer);
        }
        // hWnd �������
        SetHWnd2(hWndDummy);
        // ��������� ���������
        SetState(TALK);
    }
    // ������� �� ������
    SendMessage(hWndInitiate, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
}

// ������ ������� ������ ������
void OnRequest(WPARAM wParam, LPARAM lParam) {
    // ������������� ���������
    UnpackDDElParam(WM_DDE_REQUEST, lParam, (PUINT)&format, (PUINT)&atomA);
    // �������� �������� ������
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    // ��������� ���������
    sprintf(bufc, "Request received:\r\nAtom: %s\r\nFrom: 0x%p", bufa, (int*)wParam);
    // �������
    SetWindowText(hWndAck, bufc);
    ShowMessage("Incoming request");
    // �������� ����� ���� ������
    GetWindowText(hWndOut, bufa, MAX_TEXT);
    // ������ ������
    dwSize = strlen(bufa);
    // ���������, ���� ��� ��������
    if (dwSize == 0) {
        ShowMessage("OnRequest: nothing to send.");
        return;
    }
    // ����������� ����������� ������
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, 2 + dwSize + sizeof(DDEDATA));
    // ��������� ���������
    SetLastError(0);
    if (!hGlobal) {
        ShowError("OnRequest.GlobalAlloc", GetLastError());
        return;
    }
    // ��������� ������
    lpData = (DDEDATA FAR*)GlobalLock(hGlobal);
    // ��������� ���������
    SetLastError(0);
    if (!lpData) {
        ShowError("OnRequest.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // �������� ������
    lstrcpy((LPSTR)lpData->Value, bufa);
    // ����������� CR LF
    lstrcat((LPSTR)lpData->Value, (LPSTR)"\r\n");
    // ������ ������
    lpData->cfFormat = CF_TEXT;
    // ��������� �� �������������
    lpData->fAckReq = 1;
    // �������� �������
    lpData->fResponse = 1;
    // ������������ ������
    GlobalUnlock(hGlobal);
    // �������� ��������� WM_DDE_DATA
    SetLastError(0);
    lResult = PostMessage((HWND)wParam, WM_DDE_DATA, (WPARAM)hWnd1, PackDDElParam(WM_DDE_DATA, (UINT)hGlobal, atomA));
    dwError = GetLastError();
    if (dwError) {
        ShowError("OnRequest.PostMessage", dwError);
        // ����������� ����������� ������
        GlobalFree(hGlobal);
    }
}

// ������ ������� ������ ���������� �����
void OnAdvise(WPARAM wParam, LPARAM lParam) {
}

// ������ ������� ������ ���������� ���������� �����
void OnUnadvise(WPARAM wParam, LPARAM lParam) {
}

// ������ ������� ������ �� ��������� ������
void OnPoke(WPARAM wParam, LPARAM lParam) {
}

// ������ ������� ������ �� ���������� �������
void OnExecute(WPARAM wParam, LPARAM lParam) {
}

// �������� ����������� � ���������� ���������
void OnTerminate(WPARAM wParam, LPARAM lParam) {
    // �������� ���������
    sprintf(bufc, "0x%p", (int*)wParam);
    // ��������� � ������
    SendMessage(hWndTerm, LB_SETCURSEL, SendMessage(hWndTerm, LB_ADDSTRING, 0, (LPARAM)bufc), 0);
    // ��������, ���� ������������� ���
    if (state == TALK && (HWND)wParam == hWnd2) {
        // � ������ �������� TERMINATE
        PostMessage(hWnd2, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
        // ��� �������
        SetName(DDEUnknown);
        // ��������� ���������
        SetState(IDLE);
        // ������� ������ ���
        SetHWnd2(0);
    }
}

// ����� ������������ ����
void OnDestroyWindow() {
    // ��������� ��������
    if (hWnd2 && state == TALK && hWnd1 != hWnd2) {
        PostMessage(hWnd2, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    }
}

// ������� ������ ������ �������� TERMINATE
void DeleteTerminate() {
    // ���������� ������� ������
    SelectedItem = SendMessage(hWndTerm, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // ������� �� ������
    SendMessage(hWndTerm, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
}

// ������� ��� ������ ������ �������� TERMINATE
void ClearTerminate() {
    // ������� ������
    dwSize = SendMessage(hWndTerm, LB_GETCOUNT, 0, 0);
    for (int i = 0; i < (int)dwSize; i++) {
        // ������� �� ������
        SendMessage(hWndTerm, LB_DELETESTRING, (WPARAM)0, 0);
    }
}

// ������������� ���������
void SetState(ddestates newstate) {
    state = newstate;
    sprintf(bufc, "%s", statenames[state]);
    SetWindowText(hWndState, bufc);
}

void ShowHWnd1() {
    sprintf(bufc, "0x%p", (int*)hWnd1);
    SetWindowText(hWndMine, bufc);
}

void SetHWnd2(HWND hWnd) {
    hWnd2 = hWnd;
    sprintf(bufc, "0x%p", (int*)hWnd);
    SetWindowText(hWndPartner, bufc);
}

// ������� ����
void ClearDataAndAck() {
    SetWindowText(hWndIn, "");
    SetWindowText(hWndAck, "");
}

// �������� ������ �������� ������
void GetListItemData(HWND hWnd, int index) {
    char c = 0, *p = 0;
    int i = 0, j = 0;
    if (index < 0) return;
    // �������� ������ ������
    SelectedItem = index;
    // �������� ����� ������
    dwSize = SendMessage(hWnd, LB_GETTEXT, (WPARAM)index, (LPARAM)bufc);
    // �������� �����
    clearbuf(bufa);
    for (; i < (int)dwSize; i++) {
        c = bufc[i];
        if (c == 32) {
            bufa[j] = 0;
            break;
        }
        bufa[j++] = bufc[i];
    }
    // ����������� � hWnd2
    hWndDummy = (HWND)strtoul(bufa, &p, 16);
    clearbuf(bufa);
    for (i = i + 1, j = 0; i < (int)dwSize; i++) {
        c = bufc[i];
        if (c == 32) {
            bufa[j] = 0;
            break;
        }
        bufa[j++] = bufc[i];
    }
    clearbuf(bufb);
    for (i = i + 1, j = 0; i < (int)dwSize; i++) {
        c = bufc[i];
        if (c == 32) {
            bufb[j] = 0;
            break;
        }
        bufb[j++] = bufc[i];
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmIdent = 0, wmEvent = 0;
    switch (message) {
    case WM_DDE_ACK:
        // �� �������
        OnAck(wParam, lParam);
        if (state == TALK) {
            FreeDDElParam(WM_DDE_ACK, lParam);
        }
        break;
    case WM_DDE_DATA:
        // �� �������
        OnData(wParam, lParam);
        FreeDDElParam(WM_DDE_DATA, lParam);
        break;
    case WM_DDE_INITIATE:
        // �� �������
        OnInitiate(wParam, lParam);
        break;
    case WM_DDE_REQUEST:
        // �� �������
        OnRequest(wParam, lParam);
        FreeDDElParam(WM_DDE_REQUEST, lParam);
        break;
    case WM_DDE_ADVISE:
        // �� �������
        OnAdvise(wParam, lParam);
        FreeDDElParam(WM_DDE_ADVISE, lParam);
        break;
    case WM_DDE_UNADVISE:
        // �� �������
        OnUnadvise(wParam, lParam);
        FreeDDElParam(WM_DDE_UNADVISE, lParam);
        break;
    case WM_DDE_POKE:
        // �� �������
        OnPoke(wParam, lParam);
        FreeDDElParam(WM_DDE_POKE, lParam);
        break;
    case WM_DDE_EXECUTE:
        // �� �������
        OnExecute(wParam, lParam);
        FreeDDElParam(WM_DDE_POKE, lParam);
        break;
    case WM_DDE_TERMINATE:
        // �� ������� ��� �� �������
        OnTerminate(wParam, lParam);
        break;
    case WM_COMMAND:
        wmIdent = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmIdent) {
        case CMD_EXIT:
            DestroyWindow(hWnd);
            break;
        }
        switch (wmEvent) {
        case BN_CLICKED:
            switch (wmIdent) {
            case INITIAT:
                InitiateConversation();
                break;
            case ACCEPTC:
                AcceptConversation();
                break;
            case DECLINE:
                DeclineConversation();
                break;
            case REQUEST:
                SendRequest();
                break;
            case ADVISEW:
                SendAdvise(1);
                break;
            case ADVISEH:
                SendAdvise(0);
                break;
            case UNADVIS:
                SendUnadvise();
                break;
            case POKESVR:
                SendPoke();
                break;
            case EXECUTE:
                SendExecute();
                break;
            case TERMINA:
                SendTerminate();
                break;
            case DECLINI:
                DeclineIncoming();
                break;
            case ACCEPTI:
                AcceptIncoming();
                break;
            case DELETEA:
                ClearTerminate();
                break;
            case DELETET:
                DeleteTerminate();
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        OnDestroyWindow();
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DDEAPP));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "DDEAPP";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassEx(&wcex);
}

// ������� �������� ����������
int CreateControls(HINSTANCE hInstance) {
    int ccy = DT1 + 114 + BIS;
    tahoma = CCreateFont(hWnd1, "Tahoma", 8);
    hWndApp = CCreateLabel1(hInstance, hWnd1, DL1, DT1, DW1, DH1, tahoma, "Application:");
    hWndApp = CCreateEditSL(hInstance, hWnd1, DL1, DT1 + 16, DW2, DH2, 0, tahoma, DEFAPP);
    hWndTopic = CCreateLabel1(hInstance, hWnd1, DL1, DT1 + 40, DW1, DH1, tahoma, "Topic:");
    hWndTopic = CCreateEditSL(hInstance, hWnd1, DL1, DT1 + 56, DW2, DH2, 0, tahoma, DEFTOPIC);
    CCreateButton(hInstance, hWnd1, DL2, DT1 + 81, BWW, BTH, INITIAT, tahoma, "Initiate");
    hWndInAck = CCreateLabel1(hInstance, hWnd1, DL1, DT1 + 96, DW1, DH1, tahoma, "Received Aks's:");
    hWndInAck = CCreateListB1(hInstance, hWnd1, DL1, DT1 + 114, DW2, DH3, tahoma);
    CCreateButton(hInstance, hWnd1, DL1, DT1 + 257, BWW, BTH, DECLINE, tahoma, "Decline");
    CCreateButton(hInstance, hWnd1, DL2, DT1 + 257, BWW, BTH, ACCEPTC, tahoma, "Accept");
    hWndMine = CCreateLabel1(hInstance, hWnd1, DL1, DT1 + 291, DW1, DH1, tahoma, "hWnd1:");
    hWndMine = CCreateEditSS(hInstance, hWnd1, DL2, DT1 + 289, BWW, DH2, 0, tahoma, "hWnd1");
    hWndPartner = CCreateLabel1(hInstance, hWnd1, DL1, DT1 + 312, DW1, DH1, tahoma, "hWnd2:");
    hWndPartner = CCreateEditSS(hInstance, hWnd1, DL2, DT1 + 310, BWW, DH2, 0, tahoma, "hWnd2");
    hWndState = CCreateLabel1(hInstance, hWnd1, DL1, DT1 + 333, DW1, DH1, tahoma, "State:");
    hWndState = CCreateEditSS(hInstance, hWnd1, DL2, DT1 + 331, BWW, DH2, 0, tahoma, "Idle");
    CCreateButton(hInstance, hWnd1, DL2, DT1 + 355, BWW, BTH, TERMINA, tahoma, "Terminate");
    CCreateButton(hInstance, hWnd1, DL2, DT1 + 386, BWW, BTH, CMD_EXIT, tahoma, "Close");
    //
    hWndItem = CCreateLabel1(hInstance, hWnd1, DL3, DT1, DW1, DH1, tahoma, "Item:");
    hWndItem = CCreateEditSL(hInstance, hWnd1, DL3, DT1 + 16, DW2, DH2, 0, tahoma, DEFITEM);
    hWndOut = CCreateLabel1(hInstance, hWnd1, DL3, DT1 + 40, DW1, DH1, tahoma, "To send:");
    hWndOut = CCreateEditML(hInstance, hWnd1, DL3, DT1 + 56, DW2, DH4, 0, tahoma, DEFSEND);
    CCreateButton(hInstance, hWnd1, DL3, DT1 + 114, BWW, BTH, REQUEST, tahoma, "Request");
    CCreateButton(hInstance, hWnd1, DL4, DT1 + 114, BWW, BTH, POKESVR, tahoma, "Poke");
    CCreateButton(hInstance, hWnd1, DL3, ccy, BWW, BTH, ADVISEW, tahoma, "Advise warm");
    CCreateButton(hInstance, hWnd1, DL4, ccy, BWW, BTH, ADVISEH, tahoma, "Advise hot"); ccy += BIS;
    CCreateButton(hInstance, hWnd1, DL3, ccy, BWW, BTH, UNADVIS, tahoma, "Unadvise");
    CCreateButton(hInstance, hWnd1, DL4, ccy, BWW, BTH, EXECUTE, tahoma, "Execute");
    hWndIn = CCreateLabel1(hInstance, hWnd1, DL3, DT1 + 207, DW1, DH1, tahoma, "Received data:");
    hWndIn = CCreateEditML(hInstance, hWnd1, DL3, DT1 + 223, DW2, DH5, 0, tahoma, "");
    hWndAck = CCreateLabel1(hInstance, hWnd1, DL3, DT1 + 298, 190, DH1, tahoma, "Received Ack, Request or data fields:");
    hWndAck = CCreateEditML(hInstance, hWnd1, DL3, DT1 + 313, DW2, DH6, 0, tahoma, "");
    //
    hWndInitiate = CCreateLabel1(hInstance, hWnd1, DL5, DT1, DW1, DH1, tahoma, "Incoming Initiates:");
    hWndInitiate = CCreateListB1(hInstance, hWnd1, DL5, DT1 + 16, DW2, DH7, tahoma);
    CCreateButton(hInstance, hWnd1, DL5, DT1 + 114, BWW, BTH, DECLINI, tahoma, "Decline");
    CCreateButton(hInstance, hWnd1, DL6, DT1 + 114, BWW, BTH, ACCEPTI, tahoma, "Accept");
    hWndTerm = CCreateLabel1(hInstance, hWnd1, DL5, DT1 + 148, 110, DH1, tahoma, "Incoming Terminates:");
    hWndTerm = CCreateListB1(hInstance, hWnd1, DL5, DT1 + 164, DW2, 219, tahoma);
    CCreateButton(hInstance, hWnd1, DL5, DT1 + 386, BWW, BTH, DELETEA, tahoma, "Clear");
    CCreateButton(hInstance, hWnd1, DL6, DT1 + 386, BWW, BTH, DELETET, tahoma, "Delete");
    //
    SendMessage(hWndIn, EM_LIMITTEXT, MAX_TEXT, 0);
    SendMessage(hWndIn, EM_LIMITTEXT, MAX_TEXT, 0);
    //
    ShowHWnd1();
    SetHWnd2(0);
    SetState(IDLE);
    return 1;
}

int InitInstance(HINSTANCE hInstance) {
    SetLastError(0);
    DWORD CCY = (GetSystemMetrics(SM_CYFULLSCREEN) - W0H) / 2;
    DWORD CCX = (GetSystemMetrics(SM_CXFULLSCREEN) - W0W) / 2;
    DWORD CHX = 20 + (W0W / 2);
    hWnd1 = CreateWindow("DDEAPP", name[DDEUnknown], 0x80c80000, CCX, CCY, W0W, W0H, 0, 0, hInstance, 0);
    if (!hWnd1) return 0;
    if (!CreateControls(hInstance)) return 0;
    ShowWindow(hWnd1, SW_NORMAL);
    UpdateWindow(hWnd1);
    SetLastError(0);
    onStartApp();
    return 1;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    hInst = hInstance;
    sprintf((char*)name[DDEUnknown], "DDE Unknown");
    sprintf((char*)name[DDEClient], "DDE Client");
    sprintf((char*)name[DDEServer], "DDE Server");
    sprintf((char*)name[DDEBoth], "DDE Both");
    if (!RegisterMyClass(hInstance)) return 0;
    if (!InitInstance(hInstance)) return 0;
    SetFocus(hWndApp);
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_KEYDOWN && msg.wParam == 27) SendMessage(hWnd1, WM_DESTROY, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    SetLastError(0);
    onCloseApp();
    return (int)msg.wParam;
}
