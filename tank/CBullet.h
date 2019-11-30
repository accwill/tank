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
    bool m_bIsDie = false;       // 是否死掉了
    DIR m_eDir = DIR::UP;        // 子弹方向
    CMap* m_pMap;                // 地图类
    CTank* m_pTank;              // 坦克类
    int m_nType;                 // 子弹的类型
    DWORD m_dwID = ++dwIncID;    // 唯一值
    DWORD m_dwPrevID = 0;       // 唯一值
    DWORD m_dwTankID;             // 表示是由哪个坦克生成的生成的ID
    static const char* szWord;   // 要打印的字符
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
    bool DecideIsDie(int nX, int nY);       // 判断是否死亡
    CTank* GetTank() { return m_pTank; };
};
