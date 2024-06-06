// 2019 ReVoL Primer Template
// ddeapp.cpp
// ОТИ НИЯУ МИФИ
// 1ПО-00Д
// Пономарев Владимир Вадимович
// Системное программирование
// SY-108. DDE
// 01.01.2000

#include "ddeapp.h"
#include "..\ccreate.h"

// клиент инициирует разговор
void InitiateConversation() {
    if (state == TALK) {
        return;
    }
    // Я - клиент
    SetName(DDEClient);
    // новое состояние
    SetState(INITIATE);
    // атом приложения
    dwSize = GetWindowText(hWndApp, bufa, MAX_TEXT);
    if (dwSize == 0) {
        atomApp = GlobalAddAtomA(NULL);
    } else {
        atomApp = GlobalAddAtomA(bufa);
    }
    // атом темы
    dwSize = GetWindowText(hWndTopic, bufb, MAX_TEXT);
    if (dwSize == 0) {
        atomTopic = GlobalAddAtomA(NULL);
    } else {
        atomTopic = GlobalAddAtomA(bufb);
    }
    // прошу начать переговоры
    // HWND_BROADCAST - послать всем окнам, hWnd1 - дескриптор моего окна
    // сервер запомнит мой hWnd1 и пришлет подтверждение
    SetLastError(0);
    lResult = SendMessage(HWND_BROADCAST, WM_DDE_INITIATE, (WPARAM)hWnd1, MAKELONG(atomApp, atomTopic));
    dwError = GetLastError();
    if (dwError) {
        //ShowError("InitiateConversation.SenMessage", dwError);
    }
}

// клиенту пришло подтверждение разговора
void OnAckInInitiate(WPARAM wParam, LPARAM lParam) {
    if (hWnd1 == (HWND)wParam) {
        return;
    }
    // получаем атомы
    atomA = (ATOM)LOWORD(lParam);
    atomB = (ATOM)HIWORD(lParam);
    // расшифровываем атомы
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    GlobalGetAtomName(atomB, bufb, MAX_TEXT);
    // формируем строку списка
    sprintf(bufc, "0x%p %s %s ", (int*)wParam, bufa, bufb);
    // добавляем в список
    SetLastError(0);
    lResult = SendMessage(hWndInAck, LB_SETCURSEL, SendMessage(hWndInAck, LB_ADDSTRING, 0, (LPARAM)bufc), 0);
    dwError = GetLastError();
    if (dwError) {
        //ShowError("OnAckInInitiate.SenMessage", dwError);
    }
}

// принимает разговор
void AcceptConversation() {
    if (state == TALK) {
        ShowMessage("AcceptConversation: You are in a conversation.");
        return;
    }
    // выделенный элемент списка
    SelectedItem = SendMessage(hWndInAck, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // получим данные из списка
    GetListItemData(hWndInAck, SelectedItem);
    // приложение
    SetWindowText(hWndApp, bufa);
    // тема
    SetWindowText(hWndTopic, bufb);
    // состояние разговора
    SetState(TALK);
    // hWnd сервера
    SetHWnd2(hWndDummy);
    // удаляем из списка
    lResult = SendMessage(hWndInAck, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
    // выделяем последний элемент
    SendMessage(hWndInAck, LB_SELECTSTRING, SendMessage(hWndInAck, LB_GETCOUNT, 0, 0) - 1, 0);
}

// отклоняет разговор
void DeclineConversation() {
    if (state == TALK) {
        ShowMessage("You are in a conversation.");
        return;
    }
    // выделенный элемент списка
    SelectedItem = SendMessage(hWndInAck, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // получим данные из списка
    GetListItemData(hWndInAck, SelectedItem);
    // отклоняем разговор
    SetLastError(0);
    lResult = PostMessage(hWndDummy, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    dwError = GetLastError();
    if (dwError) {
        ShowError("DeclineConversation.PostMessage", dwError);
    }
    // удаляем из списка
    SendMessage(hWndInAck, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
    // выделяем последний элемент
    SendMessage(hWndInAck, LB_SELECTSTRING, SendMessage(hWndInAck, LB_GETCOUNT, 0, 0) - 1, 0);
}

// клиенту пришло подтверждение во время переговоров
void OnAckInConversation(WPARAM wParam, LPARAM lParam) {
    //ShowMessage("Incoming Ack");
    // распаковываем параметры
    UnpackDDElParam(WM_DDE_ACK, lParam, (PUINT)&ack, (PUINT)&atomA);
    // формируем сообщение
    sprintf(bufc, "Ack received:\r\nAck %d\r\nBusy: %d\r\nAppReturnCode: %d\r\nFrom: 0x%p", ack.fAck, ack.fBusy, ack.bAppReturnCode, (int*)wParam);
    // выводим
    SetWindowText(hWndAck, bufc);
}

// клиенту пришло какое-то подтверждение (или отрицание)
void OnAck(WPARAM wParam, LPARAM lParam) {
    if (state == TALK) {
        // другое подтверждение
        OnAckInConversation(wParam, lParam);
    } else {
        // подтверждение разговора
        OnAckInInitiate(wParam, lParam);
    }
}

// клиент посылает запрос данных
void SendRequest() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendRequest: You aren't in a conversation.");
        return;
    }
    // элемент данных
    GetWindowText(hWndItem, bufa, MAX_TEXT);
    // атом данных
    atomItem = GlobalAddAtom(bufa);
    // посылаем запрос, формат - текст
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_REQUEST, (WPARAM)hWnd1, PackDDElParam(WM_DDE_REQUEST, CF_TEXT, atomItem));
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendRequest.PostMessage", dwError);
    }
}

// клиент посылает запрос постоянной связи
void SendAdvise(int DeferUpd) {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendAdvise: You aren't in a conversation.");
        return;
    }
    // элемент данных
    GetWindowText(hWndItem, bufa, MAX_TEXT);
    // атом связи
    atomAdvise = GlobalAddAtom(bufa);
    SetLastError(0);
    // резервируем память для DDEADVISE
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, sizeof(DDEADVISE));
    if (!hGlobal) {
        ShowError("SendAdvise.GlobalAlloc", GetLastError());
        return;
    }
    SetLastError(0);
    // блокируем данные
    lpAdvise = (DDEADVISE FAR*)GlobalLock(hGlobal);
    if (!lpAdvise) {
        ShowError("SendAdvise.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // формат данных
    lpAdvise->cfFormat = CF_TEXT;
    // требуется подтверждение
    lpAdvise->fAckReq = 1;
    // 0 - горячая связь, иначе теплая
    lpAdvise->fDeferUpd = DeferUpd;
    // разблокируем данные
    GlobalUnlock(hGlobal);
    // формируем параметры
    SetLastError(0);
    lParam = PackDDElParam(WM_DDE_ADVISE, (UINT_PTR)hGlobal, atomAdvise);
    if (dwError) {
        ShowError("SendAdvise.PostMessage", dwError);
        // освобождаем данные
        GlobalFree(hGlobal);
    }
    // посылаем запрос
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_ADVISE, (WPARAM)hWnd1, lParam);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendAdvise.PostMessage", dwError);
        // освобождаем данные
        GlobalFree(hGlobal);
        // освобождаем lParam
        FreeDDElParam(WM_DDE_ADVISE, lParam);
    } else {
        // запрос постоянной связи отправлен
    }
}

// клиент посылает завершение постоянной связи
void SendUnadvise() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendUnadvise: You aren't in a conversation.");
        return;
    }
    // получим текст атома
    GlobalGetAtomName(atomAdvise, bufa, MAX_TEXT);
    // выводим текст в поле
    SetWindowText(hWndItem, bufa);
    // запрос завершения связи
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_UNADVISE, (WPARAM)hWnd1, atomAdvise);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendUnadvise.PostMessage", dwError);
    }
}

// клиенту пришли данные
void OnData(WPARAM wParam, LPARAM lParam) {
    // распаковываем параметры
    UnpackDDElParam(WM_DDE_DATA, lParam, (PUINT)&hGlobal, (PUINT)&atomA);
    // получаем имя элемента данных
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    if (!hGlobal) {
        //ShowMessage("Incoming Notification");
        // пришло уведомление постоянной связи
        sprintf(bufc, "Data link notification received:\r\nAtom: %s\r\nFrom: 0x%p", bufa, (int*)wParam);
        // выводим
        SetWindowText(hWndAck, bufc);
        return;
    }
    // блокируем данные
    SetLastError(0);
    lpData = (DDEDATA FAR*)GlobalLock(hGlobal);
    if (!lpData) {
        ShowError("OnData.GlobalLock", GetLastError());
        // отрицательное подтверждение
        PostMessage((HWND)wParam, WM_DDE_ACK, (WPARAM)hWnd1, PackDDElParam(WM_DDE_ACK, 0, atomA));
        return;
    }
    // формат данных
    format = lpData->cfFormat;
    if (format != CF_TEXT) {
    }
    // нужно ли освобождение данных
    fRelease = lpData->fRelease;
    // является ли ответом на запрос
    fResponse = lpData->fResponse;
    // требуется ли подтверждение
    fAckReq = lpData->fAckReq;
    // копируем данные в буфер
    lstrcpy(bufb, (LPCSTR)lpData->Value);
    // размер данных
    dwSize = strlen(bufb);
    // разблокируем данные
    GlobalUnlock(hGlobal);
    // выводим данные в окно hWndIn
    SetWindowText(hWndIn, bufb);
    // формируем сообщение
    sprintf(bufc, "Data received (bytes: %d):\r\nFormat: %d\r\nRelease: %d\r\nResponse: %d\r\nAckReq: %d\r\nFrom: 0x%p\r\nAtom: %s", dwSize, format, fRelease, fResponse, fAckReq, (int*)wParam, bufa);
    // выводим
    SetWindowText(hWndAck, bufc);
    //ShowMessage("Incoming data");
    if (fRelease) {
        // освобождаем данные
        GlobalFree(hGlobal);
    }
    if (fAckReq) {
        // положительное подтверждение
        PostMessage((HWND)wParam, WM_DDE_ACK, (WPARAM)hWnd1, PackDDElParam(WM_DDE_ACK, 0x8000, atomA));
    }
}

// клиент посылает данные серверу
void SendPoke() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendPoke: You aren't in a conversation.");
        return;
    }
    // получим текст окна вывода в буфер
    GetWindowTextA(hWndOut, bufa, MAX_TEXT);
    // размер текста
    dwSize = strlen(bufa);
    if (dwSize == 0) {
        ShowMessage("SendPoke: nothing to send.");
        return;
    }
    // резервируем память для DDEPOKE, 2 символа для CR и LF, завершающий ноль учитывает DDEPOKE
    SetLastError(0);
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, 2 + dwSize + sizeof(DDEPOKE));
    if (!hGlobal) {
        ShowError("SendPoke.GlobalAlloc", GetLastError());
        return;
    }
    // блокируем данные
    SetLastError(0);
    lpPoke = (DDEPOKE FAR*)GlobalLock(hGlobal);
    if (!lpPoke) {
        ShowError("SendPoke.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // формат данных
    lpPoke->cfFormat = CF_TEXT;
    // требуется освобождение
    lpPoke->fRelease = 1;
    // копируем данные в DDEPOKE
    lstrcpy((LPSTR)lpPoke->Value, bufa);
    // в формате CF_TEXT каждая строка завершается CR и LF
    lstrcat((LPSTR)lpPoke->Value, (LPSTR)"\r\n");
    // разблокируем данные
    GlobalUnlock(hGlobal);
    // элемент данных
    GetWindowText(hWndItem, bufa, MAX_TEXT);
    // атом записи
    atomPoke = GlobalAddAtom(bufa);
    // формируем параметры
    lParam = PackDDElParam(WM_DDE_POKE, (UINT)hGlobal, atomPoke);
    // запрос POKE
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_POKE, (WPARAM)hWnd1, lParam);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendPoke.PostMessage", dwError);
        // освобождаем данные
        GlobalFree(hGlobal);
        // освобождаем lParam
        FreeDDElParam(WM_DDE_POKE, lParam);
    }
}

// клиент посылает команды серверу
void SendExecute() {
    ClearDataAndAck();
    if (state != TALK) {
        ShowMessage("SendExecute: You aren't in a conversation.");
        return;
    }
    // получим текст окна вывода в буфер
    GetWindowTextA(hWndOut, bufa, MAX_TEXT);
    // размер текста
    dwSize = strlen(bufa);
    if (dwSize == 0) {
        ShowMessage("SendExecute: nothing to send.");
        return;
    }
    // резервируем память для текста команд
    SetLastError(0);
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, 1 + dwSize);
    if (!hGlobal) {
        ShowError("SendExecute.GlobalAlloc", GetLastError());
        return;
    }
    // блокируем данные
    SetLastError(0);
    lpCommand = (char FAR*)GlobalLock(hGlobal);
    if (!lpCommand) {
        ShowError("SendExecute.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // копируем данные
    lstrcpy((LPSTR)lpCommand, bufa);
    // разблокируем данные
    GlobalUnlock(hGlobal);
    // формируем параметры
    lParam = PackDDElParam(WM_DDE_EXECUTE, 0, (UINT)hGlobal);
    // посылаем запрос
    SetLastError(0);
    lResult = PostMessage(hWnd2, WM_DDE_EXECUTE, (WPARAM)hWnd1, lParam);
    dwError = GetLastError();
    if (dwError) {
        ShowError("SendExecute.PostMessage", dwError);
        // освобождаем данные
        GlobalFree(hGlobal);
        // освобождаем lParam
        FreeDDElParam(WM_DDE_ADVISE, lParam);
    }
}

// посылает уведомление об окончании разговора
void SendTerminate() {
    ClearDataAndAck();
    if (state == IDLE) {
        ShowMessage("SendTerminate: Nothing to terminate.");
        return;
    }
    if (hWnd2) {
        // посылаем сообщение TERMINATE
        PostMessage(hWnd2, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    }
    //// имя нулевое
    //SetName(DDEUnknown);
    //// состояние начальное
    //SetState(IDLE);
    //// сервера больше нет
    //SetHWnd2(0);
}

// пришел запрос разговора
void OnInitiate(WPARAM wParam, LPARAM lParam) {
    ATOM atomA = (ATOM)LOWORD(lParam);
    ATOM atomB = (ATOM)HIWORD(lParam);
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    GlobalGetAtomName(atomB, bufb, MAX_TEXT);
    // формируем сообщение
    sprintf(bufc, "0x%p %s %s ", (int*)wParam, bufa, bufb);
    // добавляем в список
    SendMessage(hWndInitiate, LB_SETCURSEL, SendMessage(hWndInitiate, LB_ADDSTRING, 0, (LPARAM)bufc), 0);
}

// отклоняет входящее INITIATE
void DeclineIncoming() {
    // выделенный элемент списка
    SelectedItem = SendMessage(hWndInitiate, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // получим данные из списка
    GetListItemData(hWndInitiate, SelectedItem);
    // отклоняем входящий разговор
    SetLastError(0);
    lResult = PostMessage(hWndDummy, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    dwError = GetLastError();
    if (dwError) {
        //ShowError("DeclineIncoming.PostMessage", dwError);
    }
    // удаляем из списка
    SendMessage(hWndInitiate, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
}

// принимает входящее INITIATE
void AcceptIncoming() {
    if (state == TALK) {
        ShowMessage("AcceptIncoming: You are in a conversation.");
        return;
    }
    // выделенный элемент списка
    SelectedItem = SendMessage(hWndInitiate, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // получим данные из списка
    GetListItemData(hWndInitiate, SelectedItem);
    // приложение
    SetWindowText(hWndApp, bufa);
    // атом приложения
    dwSize = GetWindowText(hWndApp, bufa, MAX_TEXT);
    if (dwSize == 0) {
        atomApp = GlobalAddAtomA(NULL);
    } else {
        atomApp = GlobalAddAtomA(bufa);
    }
    // тема
    SetWindowText(hWndTopic, bufb);
    // атом темы
    dwSize = GetWindowText(hWndTopic, bufb, MAX_TEXT);
    if (dwSize == 0) {
        atomTopic = GlobalAddAtomA(NULL);
    } else {
        atomTopic = GlobalAddAtomA(bufb);
    }
    // посылаем accept
    SetLastError(0);
    lResult = SendMessage(hWndDummy, WM_DDE_ACK, (WPARAM)hWnd1, MAKELONG(atomApp, atomTopic));
    dwError = GetLastError();
    if (dwError) {
        ShowError("AcceptIncoming.SendMessage", dwError);
    } else {
        // Я либо сервер, либо клиент и сервер
        if (hWnd1 == hWndDummy) {
            SetName(DDEBoth);
        } else {
            SetName(DDEServer);
        }
        // hWnd сервера
        SetHWnd2(hWndDummy);
        // состояние разговора
        SetState(TALK);
    }
    // удаляем из списка
    SendMessage(hWndInitiate, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
}

// сервер получил запрос данных
void OnRequest(WPARAM wParam, LPARAM lParam) {
    // распаковываем параметры
    UnpackDDElParam(WM_DDE_REQUEST, lParam, (PUINT)&format, (PUINT)&atomA);
    // название элемента данных
    GlobalGetAtomName(atomA, bufa, MAX_TEXT);
    // формируем сообщение
    sprintf(bufc, "Request received:\r\nAtom: %s\r\nFrom: 0x%p", bufa, (int*)wParam);
    // выводим
    SetWindowText(hWndAck, bufc);
    ShowMessage("Incoming request");
    // получаем текст поля вывода
    GetWindowText(hWndOut, bufa, MAX_TEXT);
    // размер текста
    dwSize = strlen(bufa);
    // проверяем, есть что отсылать
    if (dwSize == 0) {
        ShowMessage("OnRequest: nothing to send.");
        return;
    }
    // резервируем разделяемую память
    hGlobal = GlobalAlloc(GMEM_MOVEABLE, 2 + dwSize + sizeof(DDEDATA));
    // проверяем результат
    SetLastError(0);
    if (!hGlobal) {
        ShowError("OnRequest.GlobalAlloc", GetLastError());
        return;
    }
    // блокируем память
    lpData = (DDEDATA FAR*)GlobalLock(hGlobal);
    // проверяем результат
    SetLastError(0);
    if (!lpData) {
        ShowError("OnRequest.GlobalLock", GetLastError());
        GlobalFree(hGlobal);
        return;
    }
    // копируем данные
    lstrcpy((LPSTR)lpData->Value, bufa);
    // приписываем CR LF
    lstrcat((LPSTR)lpData->Value, (LPSTR)"\r\n");
    // формат данных
    lpData->cfFormat = CF_TEXT;
    // требуется ли подтверждение
    lpData->fAckReq = 1;
    // является ответом
    lpData->fResponse = 1;
    // разблокируем память
    GlobalUnlock(hGlobal);
    // посылаем сообщение WM_DDE_DATA
    SetLastError(0);
    lResult = PostMessage((HWND)wParam, WM_DDE_DATA, (WPARAM)hWnd1, PackDDElParam(WM_DDE_DATA, (UINT)hGlobal, atomA));
    dwError = GetLastError();
    if (dwError) {
        ShowError("OnRequest.PostMessage", dwError);
        // освобождаем разделяемую память
        GlobalFree(hGlobal);
    }
}

// сервер получил запрос постоянной связи
void OnAdvise(WPARAM wParam, LPARAM lParam) {
}

// сервер получил запрос завершения постоянной связи
void OnUnadvise(WPARAM wParam, LPARAM lParam) {
}

// сервер получил запрос на получение данных
void OnPoke(WPARAM wParam, LPARAM lParam) {
}

// сервер получил запрос на выполнение команды
void OnExecute(WPARAM wParam, LPARAM lParam) {
}

// получено уведомление о завершении разговора
void OnTerminate(WPARAM wParam, LPARAM lParam) {
    // формирую сообщение
    sprintf(bufc, "0x%p", (int*)wParam);
    // добавляем в список
    SendMessage(hWndTerm, LB_SETCURSEL, SendMessage(hWndTerm, LB_ADDSTRING, 0, (LPARAM)bufc), 0);
    // завершаю, если предназначено мне
    if (state == TALK && (HWND)wParam == hWnd2) {
        // я обязан отвечать TERMINATE
        PostMessage(hWnd2, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
        // имя нулевое
        SetName(DDEUnknown);
        // состояние начальное
        SetState(IDLE);
        // сервера больше нет
        SetHWnd2(0);
    }
}

// перед уничтожением окна
void OnDestroyWindow() {
    // завершаем разговор
    if (hWnd2 && state == TALK && hWnd1 != hWnd2) {
        PostMessage(hWnd2, WM_DDE_TERMINATE, (WPARAM)hWnd1, 0);
    }
}

// удаляет строку списка входящих TERMINATE
void DeleteTerminate() {
    // выделенный элемент списка
    SelectedItem = SendMessage(hWndTerm, LB_GETCURSEL, 0, 0);
    if (SelectedItem < 0) {
        ShowMessage("Select item in a listbox first.");
        return;
    }
    // удаляем из списка
    SendMessage(hWndTerm, LB_DELETESTRING, (WPARAM)SelectedItem, 0);
}

// удаляет все строки списка входящих TERMINATE
void ClearTerminate() {
    // очищаем список
    dwSize = SendMessage(hWndTerm, LB_GETCOUNT, 0, 0);
    for (int i = 0; i < (int)dwSize; i++) {
        // удаляем из списка
        SendMessage(hWndTerm, LB_DELETESTRING, (WPARAM)0, 0);
    }
}

// устанавливает состояние
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

// очищает поля
void ClearDataAndAck() {
    SetWindowText(hWndIn, "");
    SetWindowText(hWndAck, "");
}

// получает данные элемента списка
void GetListItemData(HWND hWnd, int index) {
    char c = 0, *p = 0;
    int i = 0, j = 0;
    if (index < 0) return;
    // запомним индекс списка
    SelectedItem = index;
    // запросим текст списка
    dwSize = SendMessage(hWnd, LB_GETTEXT, (WPARAM)index, (LPARAM)bufc);
    // разберем текст
    clearbuf(bufa);
    for (; i < (int)dwSize; i++) {
        c = bufc[i];
        if (c == 32) {
            bufa[j] = 0;
            break;
        }
        bufa[j++] = bufc[i];
    }
    // преобразуем в hWnd2
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
        // от сервера
        OnAck(wParam, lParam);
        if (state == TALK) {
            FreeDDElParam(WM_DDE_ACK, lParam);
        }
        break;
    case WM_DDE_DATA:
        // от сервера
        OnData(wParam, lParam);
        FreeDDElParam(WM_DDE_DATA, lParam);
        break;
    case WM_DDE_INITIATE:
        // от клиента
        OnInitiate(wParam, lParam);
        break;
    case WM_DDE_REQUEST:
        // от клиента
        OnRequest(wParam, lParam);
        FreeDDElParam(WM_DDE_REQUEST, lParam);
        break;
    case WM_DDE_ADVISE:
        // от клиента
        OnAdvise(wParam, lParam);
        FreeDDElParam(WM_DDE_ADVISE, lParam);
        break;
    case WM_DDE_UNADVISE:
        // от клиента
        OnUnadvise(wParam, lParam);
        FreeDDElParam(WM_DDE_UNADVISE, lParam);
        break;
    case WM_DDE_POKE:
        // от клиента
        OnPoke(wParam, lParam);
        FreeDDElParam(WM_DDE_POKE, lParam);
        break;
    case WM_DDE_EXECUTE:
        // от клиента
        OnExecute(wParam, lParam);
        FreeDDElParam(WM_DDE_POKE, lParam);
        break;
    case WM_DDE_TERMINATE:
        // от клиента или от сервера
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

// создает элементы управления
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
