#pragma once
#include <windows.h>
#include <string>
#include "CMap.h"
#pragma comment(lib, "winmm")

typedef void* (*GetSapcePointer)(int);

class CMap;
// ���ù��λ��
void SetPosition(unsigned short nX, unsigned short nY);

// ����������ɫ
void SetColor(WORD dColor, bool isBack = false);

// ��ʾ���
void ShowCursor();

// ���ع��
void HideCursor();

// ��ӡ�ַ���
void WriteChar(std::string& szStr, const unsigned short nX, const unsigned short nY, WORD dColor, bool isBack = false);
void WriteChar(const char* szStr, const unsigned short nX, const unsigned short nY, WORD dColor, bool isBack = false);

// ��ӡ����
void WriteNum(const int szStr, const unsigned short nX, const unsigned short nY, WORD color);

// ��ֹ���뷨
void DisabledInputMethod();

// �������ͼ����¼�
void InputEventForCMap(CMap& map);

void InputEvent();


// ��ȡ�ļ�����֪��С
void ReadFile(const char* fileName, int nEleSize, void* p);

// ��ȡ�ļ���δ֪��С
void ReadFile(const char* fileName, int nEleSize, GetSapcePointer gs, void** p, int& nSize);

// д���ļ�
void WriteFile(const char* fileName, int nEleSize, int nCount, const void* p);

void Sound(int nI);