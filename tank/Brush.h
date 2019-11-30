#pragma once
#include "CMap.h"
#include <windows.h>


class CBrush {
	int m_nSize = 1;              // ���ʴ�С
	char* m_word = nullptr;       // ��ˢ
	WORD m_wColor = 0;            // ��ɫ
	const int m_nMAXSIZE = 3;     // �������
	const int m_nMINSIZE = 1;     // ������С
	int m_bBKG = 0;               // �Ƿ���Ҫ����ɫ
	void RealDraw1(int nX, int nY);
	void RealDraw2(int nX, int nY);
	
	// ��ˢҪ����Ҫ����������ڵ�ͼ��
	friend class CMap;
	CMap* m_cMap;
public:
    CBrush(CMap* pMap);
	// ���ӱ�ˢ��С
	void operator++(int);
	// ���ٱ�ˢ��С
	void operator--(int);
	void Draw(int nX, int nY);
};