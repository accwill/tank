#pragma once
#include <windows.h>
#include <string>
#include "CMap.h"
#pragma comment(lib, "winmm")

typedef void* (*GetSapcePointer)(int);

class CMap;
// 设置光标位置
void SetPosition(unsigned short nX, unsigned short nY);

// 设置字体颜色
void SetColor(WORD dColor, bool isBack = false);

// 显示光标
void ShowCursor();

// 隐藏光标
void HideCursor();

// 打印字符串
void WriteChar(std::string& szStr, const unsigned short nX, const unsigned short nY, WORD dColor, bool isBack = false);
void WriteChar(const char* szStr, const unsigned short nX, const unsigned short nY, WORD dColor, bool isBack = false);

// 打印数字
void WriteNum(const int szStr, const unsigned short nX, const unsigned short nY, WORD color);

// 禁止输入法
void DisabledInputMethod();

// 接收鼠标和键盘事件
void InputEventForCMap(CMap& map);

void InputEvent();


// 读取文件，已知大小
void ReadFile(const char* fileName, int nEleSize, void* p);

// 读取文件，未知大小
void ReadFile(const char* fileName, int nEleSize, GetSapcePointer gs, void** p, int& nSize);

// 写入文件
void WriteFile(const char* fileName, int nEleSize, int nCount, const void* p);

void Sound(int nI);