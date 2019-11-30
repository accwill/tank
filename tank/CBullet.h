#pragma once
#include <Windows.h>
#include "CMap.h"
#include "Tank.h"
#include "main.h"
#include <map>

class CMap;
class CTank;

class CBullet {
public:
    //using DIR = CTank::DIR;
    enum class DIR { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
    static int arrBulletsCoor[61][43];
    static std::map<std::string, CBullet*> oMapBullt;
    static int nSpeed;
    static DWORD dwIncID;
    static CBullet* OpenUpSpaceForCount(int nCount);
private:
    int m_nX;
    int m_nY;
    bool m_bIsDie = false;       // �Ƿ�������
    DIR m_eDir = DIR::UP;        // �ӵ�����
    CMap* m_pMap;                // ��ͼ��
    CTank* m_pTank;              // ̹����
    int m_nType;                 // �ӵ�������
    DWORD m_dwID = ++dwIncID;    // Ψһֵ
    DWORD m_dwPrevID = 0;       // Ψһֵ
    DWORD m_dwTankID;             // ��ʾ�����ĸ�̹�����ɵ����ɵ�ID
    static const char* szWord;   // Ҫ��ӡ���ַ�
    static WORD wColor;
    friend class Game;
public:
    CBullet() {};
    CBullet(int nX, int nY, DIR eDir, CMap* pMap, CTank* pTank, DWORD nTankID, int nType = NPCTYPE) :
        m_nX(nX), m_nY(nY), m_pMap(pMap), m_pTank(pTank), m_eDir(eDir), m_nType(nType), m_dwTankID(nTankID){};
    void Move();
    void Hide();
    void Hide(int nX, int nY);
    void Show();
    int GetType();
    DWORD GetID() { return m_dwID; }
    DWORD GetTankID() { return m_dwTankID; }
    bool GetDie();
    bool DecideIsDie(int nX, int nY);       // �ж��Ƿ�����
    CTank* GetTank() { return m_pTank; };
};
