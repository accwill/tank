#pragma once
#include <vector>
#include "Brush.h"
#include "Tools.h"
#include "main.h"
#include "Tank.h"
#include "CBullet.h"

// 地图数据类型
typedef int(*MDType)[43];


extern SHORT g_nWidth;
extern SHORT g_nHeight;

class CBrush;
class CTank;
class CBullet;

class CMap {
public:
    enum class STATE { zero = 0, river, wall, brickwall, grassland, home };
    friend class Game;
private:
    using string = std::string;
    using strings = std::vector<string>;
	STATE m_state = STATE::wall;

	// 河流
	const char* m_szRiver = "〓";
	// 铁墙
	const char* m_szWall = "■";
	// 草地
	const char* m_szGrassLand = "※";
	// 砖墙
	const char* m_szBrickWall = "▓";
    // 家
    const char* m_szHome = "★";

    int m_nLevel = 0;                   //  关卡一共6关
    

	// 颜色信息
	const WORD m_dWallColor = 9;	    //7 = 白色		 铁墙■
	const WORD m_dBrickWallColor = 6;	//6 = 黄色		 砖墙▓
	const WORD m_dRiverColor = 9;	    //9= 蓝色		 河流〓
	const WORD m_dGrasslandColor = 2;	//2 = 绿色		 树林※ 子弹通过树林※	 
	const WORD m_dHomeColor  = 4;	    //4 = 红色		 基地★☢
	const WORD m_dFontColor = 9;

	// 边界
	const int m_nMaxWidth = g_nWidth - 34;
	const int m_nMaxHeight = g_nHeight;

    const int SIZEW = (g_nWidth - 34) / 2;  // 数组的宽度
    const int SIZEH = g_nHeight + 1;            // 数组的高度

    int m_arrData[61][43] = { 0 };

	// 地图要告诉笔刷要画什么，以及笔刷大小
	friend class CBrush;
    CBrush* m_pBrush;

    // 游戏菜单
    strings m_szMenus = {
        "保存并返回菜单"
    };

    enum OPERATION { // 枚举菜单
        ONEPLAY,     // 单人游戏
        TWOPLAY,     // 双人游戏
        BACK         // 返回
    };
    
    int m_nCurrentMenu = 0; // 当前选中的菜单
    int m_bIsBack = false;  // 是否返回

    void ChoiceMenu();
    void DrawData();
    void Reset();
public:
	CMap();
    // 显示地图
    void Show();

    // 显示地图
    void Show(bool bIsFromFile);

    // 编辑地图
    void Edit();

    // 打印左侧菜单
	void PrintMapMenu();

    // 打印键盘输入菜单
    void PrintKeyMenu();

    // 点击左侧菜单触发的事件
	void ClickMapMenu(int nX, int nY);

    // 使用鼠标画地图时触发此事件
	void DrawMapForMouse(int nX, int nY);

    // 键盘按下时触发
	void KeyEvent(WORD keyCode);

    // 保存画出来的地图
	void SaveMapEditPointer(int nX, int nY);

    // 设置关卡
    void SetLevel(int nLevel);

    // 获取当前关卡
    int GetLevel();

    // 保存地图到文件
    void ToFile();

    // 读取文件到地图
    void ReadFileToData();

    // 如果坐标是草地则打印草地，否则打印空白
    void PrintGlassForCoor(int nX, int nY, CTank* pTank);

    // 如果坐标是草地则打印草地，否则打印空白
    void PrintGlassForCoor(int nX, int nY, CBullet* pBullet);

    // 如果坐标是草地则打印坦克为绿色
    void PrintGlassForCoor(int nX, int nY, const char* ch, WORD wColor, CTank* pTank);

    // 如果坐标是草地则打印子弹为绿色
    void PrintGlassForCoor(int nX, int nY, const char* ch, WORD wColor, CBullet* pBullet);

    // 获取地图数据
    MDType GetData();

    // 用于触发鼠标和键盘的事件
	friend void InputEventForCMap(CMap& map);
};

