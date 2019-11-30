#pragma once
#include "CMap.h"
#include "Tank.h"
#include <conio.h>
#include <map>

class CTank {
public:
    enum class DIR { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
    static int arrTanksCoor[61][43];
    static int nSpeed;
    static int nGeneratorBulletTime;
    static DWORD dwIncID;
    static std::map<std::string, CTank*> oMapTank;
private:
    char m_cWord[3] = "��";   // Ҫ��ӡ���ַ�
    WORD m_wColor = 1;           // �ַ�����ɫ
    bool m_bIsDie = false;       // �Ƿ��Ѿ�����
    int m_nBlood;                // Ѫ��HP
    int m_nPosX;                 // ������
    int m_nPosY;                 // ������
    int m_nAlreadyKill = 0;      // ɱ������
    int m_nScores = 0;           // ����
    int m_nType;                 // ���ͣ�������ʶNPC/���
    DWORD m_dwID = dwIncID++;    // Ψһֵ
    DWORD m_dwPrevID = 0;    // Ψһֵ
    CMap* m_pMap;                // ��ͼ
    DIR m_eDir;                  // ����
    
    friend class Game;
public:
    CTank() {};
    CTank(CMap* pMap);
    CTank(CMap* oMap, int nX, int nY, DIR eDir, int nType = 1, int nBlood = 5) :
        m_pMap(oMap), m_nPosX(nX), m_nPosY(nY),  m_nType(nType), m_eDir(eDir), m_nBlood(nBlood){};

    // ��ʾ�Լ�
    void Show(DIR eDir);

    // �����Լ�
    void Hide();

    // �ƶ�
    void Move(DIR eDir);

    // �ж��Ƿ�����Ч���ƶ�
    bool isValidMove(DIR eDir, int nX, int nY);

    // ��ȡ̹������
    int GetType();

    // ��������
    void SetDie();

    // �ӷ�
    void Incoming() { m_nScores++; }

    // ��¼������ɱ��������
    void IncomKill() { m_nAlreadyKill++; }

    // ��ȡ����
    int GetScores() { return m_nScores * 10; }

    // ��ù�������նɱ����������
    int GetAldreaKill() { return m_nAlreadyKill; }

    // ���HP
    int GetHP() { return m_nBlood; }

    // ������
    void Hited() { --m_nBlood; }

    int GetX() { return m_nPosX; };
    void SetX(int nX) { m_nPosX = nX; };
    int GetX(bool isBullet);
    int GetY() { return m_nPosY; };
    DWORD GetID() { return m_dwID; };
    void SetY(int nY) { m_nPosY = nY; };
    int GetY(bool isBullet);
    bool GetDie() { return m_bIsDie; };
    DIR GetDir() { return m_eDir; };
};
