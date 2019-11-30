// tank.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <time.h>
#include "Game.h"
#include "CMap.h"


WORD CBullet::wColor = FOREGROUND_RED;               // 子弹的颜色
const char* CBullet::szWord = "●";                   // 子弹的图标
int CTank::arrTanksCoor[][43] = { 0 };               // 坦克静态表初始化
int CTank::nSpeed = 200;                             // NPC移动速度
int CTank::nGeneratorBulletTime = 300;               // NPC生成子弹的间隔
int CBullet::arrBulletsCoor[][43] = { 0 };           // 子弹静态表初始化
int CBullet::nSpeed = 40;                            // 子弹的移动速度
std::map<std::string, CTank*> CTank::oMapTank;       // 坦克坐标链接坦克的MAP
std::map<std::string, CBullet*> CBullet::oMapBullt;  // 子弹坐标链接子弹的MAP
DWORD CBullet::dwIncID = 0;                          // 子弹的自增ID
DWORD CTank::dwIncID = 0;                            // 坦克的自增ID


int main()
{
	DisabledInputMethod();
	Game game;

    game.StartGame();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
