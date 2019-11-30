#pragma once
#include <vector>
#include <time.h>
#include <conio.h>
#include "Tools.h"
#include "CMap.h"
#include "Tank.h"
#include "CBullet.h"
#include "data.h"


class Game {
	using string = std::string;
	using strings = std::vector<string>;
    using Bullets = std::vector<CBullet*>;
    using Tanks = std::vector<CTank*>;
    using Map = std::map<int, int>;
	enum DIR { // 选择
		UP = 'w', 
		DOWN = 's',
		OK = '\r'
	};

    enum OPERATION { // 操作
        ONEPLAY,     // 单人游戏
        TWOPLAY,     // 双人游戏
        READFILE,    // 读取游戏
        MAPEDIT,     // 地图编辑
        EXIT         // 退出游戏
    };
    int m_nCurrentMenu = 0; // 用键盘选中的菜单
    int m_nPlayerCount = 1;
    bool m_bNextLevel = false;
    int m_nLevel = 0;       // 关卡
    const int m_nMAXLEVEL = 5;
    Map m_mapTankCount;     // 对应关卡，坦克的数量
    Map m_mapTankDieCount;  // 对应关卡，已经死去的数量
    CMap* m_pMap;
    CTank* m_pTank;
    CTank* m_pTank2;

    strings m_szMenus = { // 菜单
		" 单人游戏 ",
		" 双人游戏 ",
		" 读取游戏 ",
		" 地图编辑 ",
		" 结束游戏 "
	};
    Bullets m_arrBullets;
    Tanks m_arrTanks;                       // 每一关对应的坦克数量
    Map m_mapAlReadyGeneratorTankCount;     // 对应关卡，已经生成的坦克数量统计
    int m_mapEverGeneratorTankCout = 6;     // 每次生成多少个坦克
    bool m_bIsReadFromFile = false;         // 是否存读档进入
    // 选择菜单
    void ChoiceMenu();
    // 生成NPC
    void GeneratorNPC();

    // 进入下一关
    void NextLevel();

    // 展示右侧的菜单
    void ShowMenu();

    // 判断是否游戏结束了
    void DecideIsGameOver();

    // 存档
    void WriteFile();

    // 读档
    void ReadFile();

    // 关联坦克和子弹，以及坦克和地图，子弹和地图
    void RelatedBulletAndTankAndMap();

    // 画菜单
    void WriteMenu();

    // 打印标题
    void WriteTitle();

    // 选择菜单
    void SelectMenu();
public:
    Game();

    // 开始游戏
    void StartGame();

    // 玩游戏
    void PlayGame(int n);

	// 设置窗口的大小
	void SetWindowSize(); 
	
	// 设置window的标题
	void SetWindowTitle(); 

    // 键盘事件
    void KeyEvent();


};