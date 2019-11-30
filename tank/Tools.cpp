#include "Tools.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

void SetPosition(unsigned short nX, unsigned short nY) {
	COORD cr = { static_cast<short>(nX * 2), static_cast<short>(nY) };
	SetConsoleCursorPosition(hStdOut, cr);
}

void SetColor(WORD dColor, bool isBack) {
	SetConsoleTextAttribute(hStdOut, dColor);
	if (isBack) {
		SetConsoleTextAttribute(hStdOut, dColor|
			BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	}

}

void ShowCursor() {
	CONSOLE_CURSOR_INFO cci = { 0 };
	cci.dwSize = 1;
	cci.bVisible = true;//�Ƿ���ʾ���
	SetConsoleCursorInfo(hStdOut, &cci);
}

void HideCursor() {
	CONSOLE_CURSOR_INFO cci = { 0 };
	cci.dwSize = 1;
	cci.bVisible = false;//�Ƿ���ʾ���
	SetConsoleCursorInfo(hStdOut, &cci);
}

void WriteChar(std::string& szStr, const unsigned short nX, const unsigned short nY, WORD dColor, bool isBack) {
	HideCursor();
	SetColor(dColor, isBack);
	SetPosition(nX, nY);
	printf("%s", szStr.data());
}

void WriteChar(const char* szStr, const unsigned short nX, const unsigned short nY, WORD dColor, bool isBack) {
	HideCursor();
	SetColor(dColor, isBack);
	SetPosition(nX, nY);
    printf("%s", szStr);
}

void WriteNum(const int nNum, const unsigned short nX, const unsigned short nY, WORD color) {
	HideCursor();
	SetColor(nNum);
	SetPosition(nX, nY);
	printf("%d", nNum);
}

void DisabledInputMethod() {
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}

void InputEventForCMap(CMap& map) { // Map����Ԫ����
	INPUT_RECORD eventMsg;
	DWORD Pointer;
	SetConsoleMode(hStdIn, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	while (true) {
		ReadConsoleInput(hStdIn, &eventMsg, 1, &Pointer); // Read input msg
		MOUSE_EVENT_RECORD mer = eventMsg.Event.MouseEvent;
		bool isMouseEvent = eventMsg.EventType == MOUSE_EVENT; // �Ƿ��������¼�
		bool isKeyEvent = eventMsg.EventType == KEY_EVENT; // �Ƿ��Ǽ��̵��¼�
		bool isClick = mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED; // �Ƿ񵥻���������
		bool isMove = mer.dwEventFlags == MOUSE_MOVED; // �Ƿ��ƶ������

		int nX = mer.dwMousePosition.X;
		int nY = mer.dwMousePosition.Y;
		if (isMouseEvent && isClick) { // �ж�����¼�
            if (nX > 1 && nX < map.m_nMaxWidth - 1 && nY >= 1 && nY < map.m_nMaxHeight) { // �ڱ߽��ڵ�����
                map.DrawMapForMouse(nX, nY);
            }
            if (isMove) {
				if (nX > 1 && nX < map.m_nMaxWidth - 1 && nY >= 1 && nY < map.m_nMaxHeight) { // �ڱ߽��ڵ�����
					map.DrawMapForMouse(nX, nY);
				}
			} 
            if (nX > map.m_nMaxWidth&& isClick) { // ������Ҳ�˵�
				map.ClickMapMenu(nX, nY);
			}
			

		} else if (isKeyEvent && eventMsg.Event.KeyEvent.bKeyDown) { // �Ƿ��Ǽ��̰���
            map.KeyEvent(eventMsg.Event.KeyEvent.wVirtualKeyCode);
		}
        
        if (map.m_bIsBack) {
            map.m_bIsBack = false;
            system("cls");
            system("color a");
            return;
        }
	}
}

void InputEvent() {
    INPUT_RECORD eventMsg;
    DWORD Pointer;
    SetConsoleMode(hStdIn, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    while (true) {
        ReadConsoleInput(hStdIn, &eventMsg, 1, &Pointer); // Read input msg
        bool isKeyEvent = eventMsg.EventType == KEY_EVENT;
        if (isKeyEvent && eventMsg.Event.KeyEvent.bKeyDown) { // �Ƿ��Ǽ��̰���
            //map.KeyEvent(eventMsg.Event.KeyEvent.wVirtualKeyCode);
        }
    }
}

void ReadFile(const char* fileName, int nEleSize, void* p) {
    FILE* pf = NULL;
    int nElementCount = 0;
    if (fopen_s(&pf, fileName, "rb") || pf == nullptr) {
        return;
    }

    fseek(pf, SEEK_SET, SEEK_END);

    long nCountSize = ftell(pf); // �ܴ�С

    nElementCount = nCountSize / nEleSize;

    rewind(pf);
    fread(p, nEleSize, nElementCount, pf);

    fclose(pf);

    return;
}

void ReadFile(const char* fileName, int nEleSize, GetSapcePointer gs, void** p, int& nSize) {
    FILE* pf = NULL;
    int nElementCount = 0;
    if (fopen_s(&pf, fileName, "rb") || pf == nullptr) {
        return;
    }

    fseek(pf, SEEK_SET, SEEK_END);

    long nCountSize = ftell(pf); // �ܴ�С

    nElementCount = nCountSize / nEleSize;
    rewind(pf);
    *p = gs(nElementCount); // ͨ������ָ�뿪�ٵĿռ�
    nSize = nElementCount;
    fread(*p, nEleSize, nElementCount, pf);

    fclose(pf);

    return;
}

void WriteFile(const char* fileName, int nEleSize, int nCount, const void* p) {
    FILE* pf = nullptr;
    if (fopen_s(&pf, fileName, "wb") || pf == NULL) {
        printf("�浵ʧ��");
        exit(EXIT_FAILURE);
    }
    fwrite(p, nEleSize, nCount, pf);
    fclose(pf);
    return;
}

void Sound(int nI) {
    switch (nI) {
        case 1:
            PlaySound(L"sound\\gameover.wav", NULL, SND_ASYNC | SND_NODEFAULT);
            break;
        case 3: // ����ǽ��
            PlaySound(L"sound\\wall.wav", NULL, SND_ASYNC | SND_NODEFAULT);
            break;
        case 4:
            PlaySound(L"sound\\Win.wav", NULL, SND_ASYNC | SND_NODEFAULT);
            break;
        case 5:
            PlaySound(L"sound\\bgm.wav", NULL, SND_ASYNC | SND_NODEFAULT);
            break;
        case 6:
            PlaySound(L"sound\\fire.wav", NULL, SND_ASYNC | SND_NODEFAULT);
            break;
    }
}
