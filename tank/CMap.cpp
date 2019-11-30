#include "CMap.h"

CMap::CMap() {
    m_pBrush = new CBrush(this);
    m_pBrush->m_bBKG = false;
    m_pBrush->m_word = const_cast<char*>(m_szBrickWall);
    m_pBrush->m_wColor = m_dBrickWallColor;
    m_state = STATE::brickwall;
}

void CMap::ChoiceMenu() {
    ToFile();
    m_bIsBack = true; // 返回上层, 在Tools中InputEvent， 第92行实现退出
}

void CMap::DrawData() {
    for (int i = 0; i < SIZEH; i++) {
        for (int j = 0; j < SIZEW; j++) {
            switch (m_arrData[i][j]) {
                case static_cast<int>(CMap::STATE::zero) :
                    WriteChar("  ", j, i, 0);
                    break;
                case static_cast<int>(CMap::STATE::river):
                    WriteChar(m_szRiver, j, i, m_dRiverColor);
                    break;
                case static_cast<int>(CMap::STATE::wall):
                    WriteChar(m_szWall, j, i, m_dWallColor, true);
                    break;
                case static_cast<int>(CMap::STATE::brickwall):
                    WriteChar(m_szBrickWall, j, i, m_dBrickWallColor);
                    break;
                case static_cast<int>(CMap::STATE::grassland):
                    WriteChar(m_szGrassLand, j, i, m_dGrasslandColor);
                    break;
                case static_cast<int>(CMap::STATE::home) :
                    WriteChar(m_szHome, j, i, m_dHomeColor);
                    break;
                default:
                    break;
            }
        }
    }
}

void CMap::Reset() {
    ReadFileToData();
    DrawData();
}

void CMap::Show() {
    ReadFileToData();        // 从文件读取地图到m_arrData
    DrawData();              // 画地图
}

void CMap::Show(bool bIsFromFile) {
    DrawData();              // 画地图
}

void CMap::Edit() {
    PrintMapMenu();          // 显示与鼠标交互的右侧菜单
    PrintKeyMenu();          // 显示与键盘交互的右侧菜单
    ReadFileToData();        // 从文件读取地图到m_arrData
    DrawData();              // 画地图
    InputEventForCMap(*this);       // 添加鼠标键盘的事件监听
}

void CMap::PrintMapMenu() {
	int nLeft = (m_nMaxWidth + 11) / 2;
	int nRight = (m_nMaxWidth + 23) / 2;
	WriteChar("点击选择功能", (m_nMaxWidth + 13) / 2, 4, m_dFontColor);
	WriteChar("铁墙", nLeft, 6, m_dFontColor);
	WriteChar("■■", nLeft, 7, m_dWallColor);
	WriteChar("■■", nLeft, 8, m_dWallColor);

	WriteChar("砖墙", nRight, 6, m_dFontColor);
	WriteChar("▓▓", nRight, 7, m_dBrickWallColor);
	WriteChar("▓▓", nRight, 8, m_dBrickWallColor);

	WriteChar("草地", nLeft, 11, m_dFontColor);
	WriteChar("※※", nLeft, 12, m_dGrasslandColor);
	WriteChar("※※", nLeft, 13, m_dGrasslandColor);

	WriteChar("河流", nRight, 11, m_dFontColor);
	WriteChar("〓〓", nRight, 12, m_dRiverColor);
	WriteChar("〓〓", nRight, 13, m_dRiverColor);

	WriteChar("关卡+", nLeft, 16, m_dFontColor);
	WriteChar("关卡-", nRight, 16, m_dFontColor);

	WriteChar("笔刷+", nLeft, 20, m_dFontColor);
	WriteChar("笔刷-", nRight, 20, m_dFontColor);

	WriteChar("删除", nLeft, 24, m_dFontColor);
	WriteChar("□□", nLeft, 25, m_dRiverColor);
	WriteChar("□□", nLeft, 26, m_dRiverColor);

	//WriteChar("重置", nRight, 24, m_dFontColor);
	//WriteChar("◇◇", nRight, 25, m_dRiverColor);
	//WriteChar("◇◇", nRight, 26, m_dRiverColor);
}

void CMap::PrintKeyMenu() {
    size_t nLength = m_szMenus.size();
    int i = 0;
    WriteChar("选择菜单", (m_nMaxWidth + 16) / 2 - 1, 40, FOREGROUND_RED);

    for (auto szMenu : m_szMenus) {
        SHORT nX = g_nWidth - static_cast<SHORT>(szMenu.length()) * 2 - 4;
        SHORT nY = g_nHeight / 2 + 13 + i;
        WriteChar(szMenu, nX / 2 + 4, nY, FOREGROUND_BLUE, true);
      
    }
}

void CMap::ClickMapMenu(int nX, int nY) {
	if ((nX >= m_nMaxWidth + 11) && (nX <= m_nMaxWidth + 14)) {
		if (nY == 7 || nY == 8 || nY == 6) {
			// 铁砖
			m_pBrush->m_bBKG = true;
			m_pBrush->m_word = const_cast<char*>(m_szWall);
			m_pBrush->m_wColor = m_dWallColor;
			m_state = STATE::wall;


            //WriteChar("铁砖", 0, 3, m_dFontColor);
            // 画家的时候用的
            //pBrush->m_bBKG = false;
            //pBrush->m_word = const_cast<char*>(m_cHome);
            //pBrush->m_wColor = m_dHomeColor;
            //m_state = STATE::home;
		}

		if (nY == 12 || nY == 13 || nY == 11) {
			m_pBrush->m_bBKG = false;
			m_pBrush->m_word = const_cast<char*>(m_szGrassLand);
			m_pBrush->m_wColor = m_dGrasslandColor;
			m_state = STATE::grassland;
			//WriteChar("草地", 0, 3, m_dFontColor);
		}

		if (nY == 16) {
			m_pBrush->m_bBKG = false;
            if (++m_nLevel > 5) {
                m_nLevel = 5;
            }
            ReadFileToData();
            DrawData();
			//WriteChar("关卡+", 0, 3, m_dFontColor);
		}

		if (nY == 20) {
			m_pBrush->m_bBKG = false;
			(*m_pBrush)++;
			//WriteChar("笔刷+", 0, 3, m_dFontColor);
		}

		if (nY == 25 || nY == 26 || nY == 24) {
			m_pBrush->m_bBKG = false;
			m_pBrush->m_word = (char*)"  ";
			m_state = STATE::zero;
			//WriteChar("删除", 0, 3, m_dFontColor);
		}
		return;
	}
	// 右侧菜单
	if ((nX >= m_nMaxWidth + 23) && (nX <= m_nMaxWidth + 26)) {
		if (nY == 7 || nY == 8 || nY == 6) {
			// 砖墙
			m_pBrush->m_bBKG = false;
			m_pBrush->m_word = const_cast<char*>(m_szBrickWall);
			m_pBrush->m_wColor = m_dBrickWallColor;
			m_state = STATE::brickwall;
			//WriteChar("砖墙", 0, 3, m_dFontColor);
		}

		if (nY == 12 || nY == 13 || nY == 11) {
			m_pBrush->m_bBKG = false;
			m_pBrush->m_word = const_cast<char*>(m_szRiver);
			m_pBrush->m_wColor = m_dRiverColor;
			m_state = STATE::river;
			//WriteChar("河流", 0, 3, m_dFontColor);
		}

		if (nY == 16) {
			m_pBrush->m_bBKG = false;
            if (--m_nLevel < 0) {
                m_nLevel = 0;
            }
            ReadFileToData();
            DrawData();
			//WriteChar("关卡-", 0, 3, m_dFontColor);
		}

		if (nY == 20) {
			m_pBrush->m_bBKG = false;
			(*m_pBrush)--;
			//WriteChar("笔刷-", 0, 3, m_dFontColor);
		}

		if (nY == 25 || nY == 26 || nY == 24) {
			m_pBrush->m_bBKG = false;
            Reset();
			//WriteChar("重置", 0, 3, m_dFontColor);
		}
		return;
	}

}

void CMap::DrawMapForMouse(int nX, int nY) {
	m_pBrush->Draw(nX / 2, nY);
}

void CMap::KeyEvent(WORD keyCode) {
    switch (keyCode) {
        case VK_UP:
        case 0x57:
            if (--m_nCurrentMenu < ONEPLAY) {
                m_nCurrentMenu = BACK;
            }
            PrintKeyMenu();
            break;
        case VK_DOWN:
        case 0x53:
            if (++m_nCurrentMenu > BACK) {
                m_nCurrentMenu = ONEPLAY;
            }
            PrintKeyMenu();
            break;
        case VK_RETURN:
            ChoiceMenu();
            break;

    }
}

void CMap::SaveMapEditPointer(int nX, int nY) {
    // TODO： 判断其他数组中是否有已经包含数据，如果已经包含则删除。
    m_arrData[nY][nX] = (int)m_state;
}

void CMap::SetLevel(int nLevel) {
    m_nLevel = nLevel;
    ReadFileToData();
}

int CMap::GetLevel() {
    return m_nLevel;
}

void CMap::ToFile() {
    string szLevel = std::to_string(m_nLevel);
    string szBaseMapFilName = MAPFILENAME;
    szBaseMapFilName += szLevel;
    WriteFile(szBaseMapFilName.data(), sizeof(int), SIZEW * SIZEH, m_arrData);
}

void CMap::ReadFileToData() {
   string szLevel = std::to_string(m_nLevel);
   string szBaseMapFilName = MAPFILENAME;
   szBaseMapFilName += szLevel;
   ReadFile(szBaseMapFilName.data(), sizeof(int), m_arrData);
}

void CMap::PrintGlassForCoor(int nX, int nY, CTank* pTank) {
    STATE state = static_cast<STATE>(m_arrData[nY][nX]);
    CTank::arrTanksCoor[nY][nX] = 0;                                      // 从坦克表删除坐标
    CTank::oMapTank.erase(std::to_string(nX) + "," + std::to_string(nY)); // 删除map表子帧
    switch (state) {
        case CMap::STATE::river:
            WriteChar(m_szRiver, nX, nY, m_dRiverColor);
            return;
        case CMap::STATE::grassland:
            WriteChar(m_szGrassLand, nX, nY, m_dGrasslandColor);
            return;
    }
    WriteChar("  ", nX, nY, 0xa);
}

void CMap::PrintGlassForCoor(int nX, int nY, CBullet* pBullet) {
    STATE state = static_cast<STATE>(m_arrData[nY][nX]);
    int nType = CTank::arrTanksCoor[nY][nX];
    CBullet::arrBulletsCoor[nY][nX] = 0;                                         // 从子弹表删除坐标
    CBullet::oMapBullt.erase(std::to_string(nX) + "," + std::to_string(nY));
    switch (state) { // 子弹打到地图
        case CMap::STATE::river:
            WriteChar(m_szRiver, nX, nY, m_dRiverColor);
            return;
        case CMap::STATE::wall:
            return;
        case CMap::STATE::brickwall:
            WriteChar("  ", nX, nY, 0xa);
            return;
        case CMap::STATE::grassland:
            WriteChar(m_szGrassLand, nX, nY, m_dGrasslandColor);
            return;
    }
    if (nType != 0) return; // 如果打到坦克就什么都不打印
    WriteChar("  ", nX, nY, 0xa);
}

void CMap::PrintGlassForCoor(int nX, int nY, const char* szWord, WORD wColor, CTank* pTank) {
    STATE state = static_cast<STATE>(m_arrData[nY][nX]);
    CTank::arrTanksCoor[nY][nX] = pTank->GetType();                         // 设置坦克坐标
    CTank::oMapTank[std::to_string(nX) + "," + std::to_string(nY)] = pTank; // 保存坦克指针

    switch (state) {
        case CMap::STATE::river:
            WriteChar(szWord, nX, nY, m_dRiverColor);
            return;
        case CMap::STATE::grassland:
            WriteChar(szWord, nX, nY, m_dGrasslandColor);
            return;
    }
    WriteChar(szWord, nX, nY, wColor);
}

void CMap::PrintGlassForCoor(int nX, int nY, const char* szWord, WORD wColor, CBullet* pBullet) {
    STATE state = static_cast<STATE>(m_arrData[nY][nX]);                            // 读取坐标状态：wall/brickwall/river/Grassland
    CBullet::arrBulletsCoor[nY][nX] = pBullet->GetType();                           // 设置子弹表：
    CBullet::oMapBullt[std::to_string(nX) + "," + std::to_string(nY)] = pBullet;    // 保存子弹指针
    int nType = CTank::arrTanksCoor[nY][nX];
    if (nType != 0) return; // 如果打到坦克就什么都不打印
    switch (state) {
        case CMap::STATE::river:
            WriteChar(szWord, nX, nY, m_dRiverColor);
            return;
        case CMap::STATE::grassland:
            WriteChar(szWord, nX, nY, m_dGrasslandColor);
            return;
    }
    WriteChar(szWord, nX, nY, wColor);
}

MDType CMap::GetData() {
    return m_arrData;
}

