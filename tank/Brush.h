#pragma once
#include "CMap.h"
#include <windows.h>


class CBrush {
	int m_nSize = 1;              // 画笔大小
	char* m_word = nullptr;       // 笔刷
	WORD m_wColor = 0;            // 颜色
	const int m_nMAXSIZE = 3;     // 画笔最大
	const int m_nMINSIZE = 1;     // 画笔最小
	int m_bBKG = 0;               // 是否需要背景色
	void RealDraw1(int nX, int nY);
	void RealDraw2(int nX, int nY);
	
	// 笔刷要把需要画的坐标放在地图中
	friend class CMap;
	CMap* m_cMap;
public:
    CBrush(CMap* pMap);
	// 增加笔刷大小
	void operator++(int);
	// 减少笔刷大小
	void operator--(int);
	void Draw(int nX, int nY);
};