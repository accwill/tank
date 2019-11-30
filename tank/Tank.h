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
    char m_cWord[3] = "■";   // 要打印的字符
    WORD m_wColor = 1;           // 字符的颜色
    bool m_bIsDie = false;       // 是否已经死亡
    int m_nBlood;                // 血量HP
    int m_nPosX;                 // 横坐标
    int m_nPosY;                 // 纵坐标
    int m_nAlreadyKill = 0;      // 杀敌数量
    int m_nScores = 0;           // 分数
    int m_nType;                 // 类型，用来标识NPC/玩家
    DWORD m_dwID = dwIncID++;    // 唯一值
    DWORD m_dwPrevID = 0;    // 唯一值
    CMap* m_pMap;                // 地图
    DIR m_eDir;                  // 方向
    
    friend class Game;
public:
    CTank() {};
    CTank(CMap* pMap);
    CTank(CMap* oMap, int nX, int nY, DIR eDir, int nType = 1, int nBlood = 5) :
        m_pMap(oMap), m_nPosX(nX), m_nPosY(nY),  m_nType(nType), m_eDir(eDir), m_nBlood(nBlood){};

    // 显示自己
    void Show(DIR eDir);

    // 隐藏自己
    void Hide();

    // 移动
    void Move(DIR eDir);

    // 判断是否是有效的移动
    bool isValidMove(DIR eDir, int nX, int nY);

    // 获取坦克类型
    int GetType();

    // 赐予死刑
    void SetDie();

    // 加分
    void Incoming() { m_nScores++; }

    // 记录功绩（杀敌数量）
    void IncomKill() { m_nAlreadyKill++; }

    // 获取评分
    int GetScores() { return m_nScores * 10; }

    // 获得功绩（已斩杀敌人数量）
    int GetAldreaKill() { return m_nAlreadyKill; }

    // 获得HP
    int GetHP() { return m_nBlood; }

    // 被命中
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
