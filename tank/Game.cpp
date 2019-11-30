#pragma once

#include "Game.h"
#include "main.h"
#include <iostream>

SHORT g_nWidth = 120;
SHORT g_nHeight = 60;

clock_t startPlayer1Bullet = clock();
clock_t startPlayer2Bullet = clock();
clock_t startPause = clock();
clock_t startSave = clock();
clock_t startOneMove = clock();
clock_t startTwoMove = clock();

Game::Game() {
    SetWindowTitle();
    SetWindowSize();
    m_pMap = new CMap;
    m_pTank = new CTank(m_pMap, 14, 58, CTank::DIR::UP, PLAYTYPE);
    m_pTank2 = new CTank(m_pMap, 28, 58, CTank::DIR::UP, PLAYTYPE);

    // 初始化每一关的NPC数量
    m_mapTankCount[0] = 6;
    m_mapTankCount[1] = 20;
    m_mapTankCount[2] = 25;
    m_mapTankCount[3] = 30;
    m_mapTankCount[4] = 35;
    m_mapTankCount[5] = 50;
    // 初始化每一关已经存在坦克的数量
    m_mapAlReadyGeneratorTankCount[0] = 6;
    m_mapAlReadyGeneratorTankCount[1] = 6;
    m_mapAlReadyGeneratorTankCount[2] = 6;
    m_mapAlReadyGeneratorTankCount[3] = 6;
    m_mapAlReadyGeneratorTankCount[4] = 6;
    m_mapAlReadyGeneratorTankCount[5] = 6;
    // 初始化已经死掉的坦克的数量
    m_mapTankDieCount[0] = 0;
    m_mapTankDieCount[1] = 0;
    m_mapTankDieCount[2] = 0;
    m_mapTankDieCount[3] = 0;
    m_mapTankDieCount[4] = 0;
    m_mapTankDieCount[5] = 0;
}

void Game::StartGame() {
    WriteTitle();
    WriteMenu();
    SelectMenu();
}

void Game::PlayGame(int nPlayerCount) {
    Sound(5);
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    
    if (!m_bIsReadFromFile) {
        m_pMap->Show();
        GeneratorNPC();
    } else {
        m_pMap->Show(true);
    }

    CTank::DIR eDir = CTank::DIR::UP;
    if (nPlayerCount == 1) {
        if (m_bIsReadFromFile) eDir = m_pTank->GetDir();
        m_pTank->Show(eDir);
        delete m_pTank2;
        m_pTank2 = nullptr;
    }
    if (nPlayerCount == 2) {
        if (m_bIsReadFromFile) eDir = m_pTank2->GetDir();
        m_pTank->Show(eDir);
        m_pTank2->Show(eDir);

    }
    std::map<int, CTank::DIR> mDirMap;              // 用于存储方向
    mDirMap[0] = CTank::DIR::UP;
    mDirMap[1] = CTank::DIR::DOWN;
    mDirMap[2] = CTank::DIR::LEFT;
    mDirMap[3] = CTank::DIR::RIGHT;
    clock_t startBullet = clock();                  // 用于子弹移动计时
    clock_t startKeyBoard = clock();                // 用于键盘按下连续计时
    clock_t startGeneratorBulletForNPC = clock();   // 用于生成NPC子弹计时
    clock_t startTankMoveForNPC = clock();          // 用于移动NPC计时
    clock_t clockDir = clock();
    srand(static_cast<unsigned int>(time((0))));
    int nTempDieCount = 0;
    while (true) {
        DecideIsGameOver();
        if (m_arrBullets.size() == 0 && m_arrTanks.size() == 0 && m_bNextLevel) {
            NextLevel();
        }
        clock_t endClock = clock();
        if (endClock - startBullet > CBullet::nSpeed) { // 移动子弹
            for (auto itr = m_arrBullets.begin(); itr != m_arrBullets.end();) {
                if ((*itr)->GetDie()) { // 判断是否死亡
                    (*itr)->Hide();
                    delete (*itr); // 释放内存
                    itr = m_arrBullets.erase(itr);
                    continue;
                }
                (*itr)->Move(); // 移动子弹
                (*itr)->GetTank()->Show((*itr)->GetTank()->GetDir()); // 显示被遮盖的坦克头
                ++itr;
            }
            startBullet = endClock;
        }
        endClock = clock();
        if (endClock - startTankMoveForNPC > CTank::nSpeed) {
            for (auto itr = m_arrTanks.begin(); itr != m_arrTanks.end();) {
                if ((*itr)->GetDie()) {
                    (*itr)->Hide();
                    Sound(3);
                    m_mapTankDieCount[m_nLevel]++;
                    nTempDieCount++;
                    delete (*itr); // 释放内存
                    itr = m_arrTanks.erase(itr);
                    continue;
                }
                CTank::DIR eDir = (*itr)->GetDir();
                (*itr)->Move(eDir);
                itr++;
            }
            if (nTempDieCount >= 1) {
                GeneratorNPC();
                nTempDieCount = 0;
            }
            startTankMoveForNPC = endClock;
        }

        if (clock() - clockDir > 300) {
            for (auto itr = m_arrTanks.begin(); itr != m_arrTanks.end();) {
                (*itr)->Move(mDirMap[rand() % 4]);
                itr++;
            }
            clockDir = clock();
        }

        endClock = clock();
        if (endClock - startGeneratorBulletForNPC > CTank::nGeneratorBulletTime) {
            ShowMenu();
            if (m_arrTanks.size() != 0) {
                CTank* pTank = m_arrTanks[rand() % m_arrTanks.size()]; // 不一定是6
                m_arrBullets.push_back(new CBullet(pTank->GetX(true), pTank->GetY(true),
                    static_cast<CBullet::DIR>(pTank->GetDir()), m_pMap, pTank, pTank->GetID(), pTank->GetType()));
                startGeneratorBulletForNPC = endClock;
            }
        }


        endClock = clock();
        if (endClock - startKeyBoard > 60) {
            KeyEvent();
            startKeyBoard = endClock;
        }
    }
}

void Game::WriteMenu() {
	size_t nLength = m_szMenus.size();
	int i = 0;
	WriteChar("ws选择菜单", (g_nWidth / 2 - 10) / 2, g_nHeight / 2 + 2,FOREGROUND_BLUE);
	for (auto szMenu : m_szMenus) {
		SHORT nX = g_nWidth / 2 - static_cast<SHORT>(szMenu.length());
		SHORT nY = g_nHeight / 2 + 5 + i;
		if ((m_nCurrentMenu) * 2 == i) {
			WriteChar(szMenu, nX / 2, nY, FOREGROUND_BLUE, true);
		} else {
			WriteChar(szMenu, nX / 2, nY, FOREGROUND_BLUE);
		}
		i += 2;
	}
}

void Game::WriteTitle() {
	string szTitle = "Play TANK";
	WriteChar(szTitle, (g_nWidth / 2 - static_cast<SHORT>(szTitle.length())) / 2, 5, FOREGROUND_BLUE);
}

void Game::SelectMenu() {
	char cCh = 0;
	while (1) {
		if (!_kbhit()) {
			continue;
		}
		cCh = _getch();
		switch (cCh) {
			case Game::UP:
				if (--m_nCurrentMenu < 0) {
					m_nCurrentMenu = m_szMenus.size() - 1;
				}
				break;
			case Game::DOWN:
                if (++m_nCurrentMenu >= static_cast<int>(m_szMenus.size())) {
					m_nCurrentMenu = 0;
				}
				break;
			case OK:
                ChoiceMenu();
		}
		WriteMenu();
	}
}

void Game::KeyEvent() {
    if (KEYDOWN(VK_ESCAPE) && clock() - startSave > 200) {
        WriteChar("是否存储游戏？Y/n", 50, 58, 1);
        startSave = clock();
        INPUT_RECORD eventMsg;
        DWORD Pointer;
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
        while (true) {
            if (clock() - startSave <= 1000) { _getch(); continue; }
            ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &eventMsg, 1, &Pointer); // Read input msg
            bool isKeyEvent = eventMsg.EventType == KEY_EVENT;
            if (isKeyEvent && eventMsg.Event.KeyEvent.bKeyDown) { // 是否是键盘按键
                if (eventMsg.Event.KeyEvent.wVirtualKeyCode == 0x59) {
                    WriteFile();
                    WriteChar("游戏存储成功", 19, 31, 1, true);
                } else {
                    WriteChar("取消存储成功", 19, 31, 1, true);
                }
                WriteChar("程序3秒后退出！！", 18, 32, 1, true);
                Sleep(3000);
                exit(EXIT_SUCCESS);
            }
        }

    }
    if (KEYDOWN(VK_SPACE) && (clock() - startPause > 200)) {
        clock_t startTemp = clock();
        while (true) {
            if (_kbhit()) {
                if (KEYDOWN(VK_SPACE) && (clock() - startTemp > 200)) {
                    startPause = clock();
                    break;
                }
            }
        }
    }
    if (m_pTank != nullptr && m_pTank->GetHP() > 0 && clock() - startOneMove > 0) {
        startOneMove = clock();
        if (KEYDOWN(0x57)) {
            m_pTank->Move(CTank::DIR::UP);
            return;
        }
        if (KEYDOWN(0x53)) {
            m_pTank->Move(CTank::DIR::DOWN);
            return;
        }
        if (KEYDOWN(0x41)) {
            m_pTank->Move(CTank::DIR::LEFT);
            return;
        }
        if (KEYDOWN(0x44)) {
            m_pTank->Move(CTank::DIR::RIGHT);
            return;
        }
        if (KEYDOWN(0x4A)) { // j 发射子弹
            if (clock() - startPlayer1Bullet > 300) {
                Sound(6);
                m_arrBullets.push_back(new CBullet(m_pTank->GetX(true), m_pTank->GetY(true),
                    static_cast<CBullet::DIR>(m_pTank->GetDir()), m_pMap, m_pTank, m_pTank->GetID(), m_pTank->GetType()));
                startPlayer1Bullet = clock();
            }
            return;
        }
    }

    if (m_pTank2 == nullptr || m_pTank2->GetHP() <= 0 || clock() - startTwoMove < 100) return; // 如果不存在玩家2 直接return
    startTwoMove = clock();

    if (KEYDOWN(VK_UP)) {
        m_pTank2->Move(CTank::DIR::UP);
        return;
    }
    if (KEYDOWN(VK_DOWN)) {
        m_pTank2->Move(CTank::DIR::DOWN);
        return;
    }
    if (KEYDOWN(VK_LEFT)) {
        m_pTank2->Move(CTank::DIR::LEFT);
        return;
    }
    if (KEYDOWN(VK_RIGHT)) {
        m_pTank2->Move(CTank::DIR::RIGHT);
        return;
    }
    if (KEYDOWN(0x61)) { // 1 发射子弹
        if (clock() - startPlayer2Bullet > 300) {
            Sound(6);
            m_arrBullets.push_back(new CBullet(m_pTank2->GetX(true), m_pTank2->GetY(true),
                static_cast<CBullet::DIR>(m_pTank2->GetDir()), m_pMap, m_pTank2, m_pTank2->GetID(), m_pTank2->GetType()));
            startPlayer2Bullet = clock();
        }
        return;
    }
}

void Game::GeneratorNPC() {
    if ((m_mapAlReadyGeneratorTankCount[m_nLevel] >= m_mapTankCount[m_nLevel]) && m_mapTankDieCount[m_nLevel] != 0) {
        // TODO: 进入下一关
        if (m_mapTankCount[m_nLevel] == m_mapTankDieCount[m_nLevel]) {
            m_bNextLevel = true;
        }
        return;
    }
    int nCount = m_mapTankDieCount[m_nLevel];
    if (nCount == 0) {
        nCount = m_mapEverGeneratorTankCout;
        for (int i = 0; i < nCount; i++) { // 生成6个NPC坦克
            m_arrTanks.push_back(new CTank(m_pMap, (i + 1) * 6, 2, CTank::DIR::DOWN, NPCTYPE, 1));
            m_arrTanks[m_arrTanks.size() - 1]->Show(CTank::DIR::DOWN);
        }
        return;
    }

    m_mapAlReadyGeneratorTankCount[m_nLevel]++;    // 增加已经生成坦克的数量
    for (int i = 0; i < 1; i++) { // 生成随机坐标的NPC坦克，写成循环方便扩展
        m_arrTanks.push_back(new CTank(m_pMap, (rand() % 6 + 1) * 6, 2, CTank::DIR::DOWN, NPCTYPE, 1));
        m_arrTanks[m_arrTanks.size() - 1]->Show(CTank::DIR::DOWN);
    }

}

void Game::NextLevel() {
    ++m_nLevel;
    if (m_nLevel > m_nMAXLEVEL) {
        WriteChar("恭喜你通关了！！", 15, 31, 1, true);
        WriteChar("程序3秒后退出！！", 18, 32, 1, true);
        Sleep(3000);
        exit(EXIT_SUCCESS);
        // TODO: 通关了。
    }
    m_pTank->Hide();
    m_pTank->SetX(14);
    m_pTank->SetY(58);
    m_pMap->SetLevel(m_nLevel);
    m_pMap->Show();
    m_pTank->Show(CTank::DIR::UP);
    if (m_pTank2 != nullptr) {
        m_pTank2->Hide();
        m_pTank2->SetX(28);
        m_pTank2->SetY(58);
        m_pTank2->Show(CTank::DIR::UP);
    }
    GeneratorNPC();
    m_bNextLevel = false;
}

void Game::ShowMenu() {
    int nLeft = 43;
    int nRight = 59;
    int nX = (nRight - nLeft) / 2 + 43;
    int nTop = 16;
    string szTemp = std::to_string(m_pTank->GetScores()) + " ";

    WriteChar("玩家一", nX, 10, 11);
    WriteChar("分数：", nX - 2, 12, 11);
    szTemp = std::to_string(m_pTank->GetScores()) + " ";
    WriteChar(szTemp, nX + 2, 12, 4);
    WriteChar("HP：", nX - 2, 14, 11);
    szTemp = std::to_string(m_pTank->GetHP()) + " ";
    WriteChar(szTemp, nX + 2, 14, 4);
    WriteChar("已击杀：", nX - 2, 16, 11);
    szTemp = std::to_string(m_pTank->GetAldreaKill()) + " ";
    WriteChar(szTemp, nX + 2, 16, 4);
    if (m_pTank2 != nullptr) {
        WriteChar("玩家二", nX, 19, 10);
        WriteChar("分数：", nX - 2, 21, 10);
        szTemp = std::to_string(m_pTank2->GetScores());
        WriteChar(szTemp, nX + 2, 21, 4);
        WriteChar("HP：", nX - 2, 23, 11);
        szTemp = std::to_string(m_pTank2->GetHP()) + " ";
        WriteChar(szTemp, nX + 2, 23, 4);
        WriteChar("已击杀：", nX - 2, 25, 10);
        szTemp = std::to_string(m_pTank2->GetAldreaKill()) + " ";
        WriteChar(szTemp, nX + 2, 25, 4);
        nTop = 25;
    }

    WriteChar("-----汇总-----", nX - 5, nTop + 4, 4);

    WriteChar("关卡", nX - 2, nTop + 6, 4);
    szTemp = std::to_string(m_nLevel + 1) + " ";
    WriteChar(szTemp, nX + 2, nTop + 6, 4);

    WriteChar("未击杀数量", nX - 4, nTop + 8, 4);
    int nTemp1 = m_mapTankCount[m_nLevel] - m_mapTankDieCount[m_nLevel];
    szTemp = std::to_string(nTemp1) + " ";
    WriteChar(szTemp, nX + 2, nTop + 8, 4);

    WriteChar("杀敌总数", nX - 4, nTop + 10, 4);
    szTemp = std::to_string(m_mapTankDieCount[m_nLevel]) + " ";
    WriteChar(szTemp, nX + 2, nTop + 10, 4);
}

void Game::DecideIsGameOver() {
    if (m_pTank->GetHP() > 0) return;
    if (m_pTank2 != nullptr && m_pTank2->GetHP() > 0) return;
    WriteChar("游戏结束", 20, 31, 1, true);
    WriteChar("程序3秒后退出！！", 18, 32, 1, true);
    Sleep(3000);
    exit(EXIT_SUCCESS);
}

void Game::WriteFile() {
    GAME gameData;
    // 整合gameData的数据
    for (int i = 0; i < 6; i++) {
        gameData.AlReadyGeneratorTankCount[i] = m_mapAlReadyGeneratorTankCount[i];
        gameData.TankCount[i] = m_mapTankCount[i];
        gameData.TankDieCount[i] = m_mapTankDieCount[i];
    }
    gameData.nLevel = m_nLevel;
    gameData.nCurrentMenu = m_nCurrentMenu;
    gameData.nPlayerCount = m_nPlayerCount;

    // 整合为连贯的内存，用于存储。
    std::vector<CBullet> arrTempBullets;
    for (size_t i = 0; i < m_arrBullets.size(); i++) {
        arrTempBullets.push_back(*m_arrBullets[i]);
    }
    std::vector<CTank> arrTempTanks;
    for (size_t i = 0; i < m_arrTanks.size(); i++) {
        arrTempTanks.push_back(*m_arrTanks[i]);
    }
    // 写入文件
    ::WriteFile("buttles", sizeof(CBullet), m_arrBullets.size(), &arrTempBullets[0]);
    ::WriteFile("tanks", sizeof(CTank), arrTempTanks.size(), &arrTempTanks[0]);
    ::WriteFile("mapdata", sizeof(int), 61 * 43, m_pMap->m_arrData);
    ::WriteFile("gamedata", sizeof(GAME), 1, &gameData);
    ::WriteFile("player1", sizeof(CTank), 1, m_pTank);
    if (m_nPlayerCount == 2) {
        ::WriteFile("player2", sizeof(CTank), 1, m_pTank2);
    }
}

void Game::ReadFile() {
    // 读取文件
    GAME gameData;
    CBullet* pbs = nullptr;
    int nPbsSize = 0;
    CTank* pts = nullptr;
    int nPtsSize = 0;
    DWORD dwTankID = m_pTank->m_dwID;
    ::ReadFile("buttles", sizeof(CBullet), [](int nCount) -> void* { return new CBullet[nCount]; }, (void**)&pbs, nPbsSize);
    ::ReadFile("tanks", sizeof(CTank), [](int nCount) -> void* { return new CTank[nCount]; }, (void**)&pts, nPtsSize);
    ::ReadFile("mapdata", sizeof(int), m_pMap->m_arrData);
    ::ReadFile("gamedata", sizeof(GAME), &gameData);
    ::ReadFile("player1", sizeof(CTank), m_pTank);
    m_pTank->m_dwPrevID = m_pTank->m_dwID;
    m_pTank->m_dwID = dwTankID;
    if (gameData.nPlayerCount == 2) {
        dwTankID = m_pTank2->m_dwID;
        ::ReadFile("player2", sizeof(CTank), m_pTank2);
        m_pTank2->m_dwPrevID = m_pTank2->m_dwID;
        m_pTank2->m_dwID = dwTankID;
        m_pTank2->m_pMap = m_pMap;
    }
    m_pTank->m_pMap = m_pMap;

    // 还原游戏数据
    // 整合gameData的数据
    for (int i = 0; i < 6; i++) {
        m_mapAlReadyGeneratorTankCount[i] = gameData.AlReadyGeneratorTankCount[i];
        m_mapTankCount[i] = gameData.TankCount[i];
        m_mapTankDieCount[i] = gameData.TankDieCount[i];
    }
    m_nLevel = gameData.nLevel;
    m_nCurrentMenu = gameData.nCurrentMenu;
    m_nPlayerCount = gameData.nPlayerCount;

    // 还原坦克和子弹数据
    for (int i = 0; i < nPbsSize; i++) {
        auto& t = pbs[i];
        auto t1 = new CBullet(t.m_nX, t.m_nY, t.m_eDir, m_pMap, nullptr, t.m_dwTankID, t.m_nType);
        t1->m_dwTankID = t.m_dwTankID;
        m_arrBullets.push_back(t1);
    }
    for (int i = 0; i < nPtsSize; i++) {
        auto& t = pts[i];
        auto t1 = new CTank(m_pMap, t.m_nPosX, t.m_nPosY, t.m_eDir, t.m_nType, t.m_nBlood);
        t1->m_dwPrevID = t.m_dwID;
        m_arrTanks.push_back(t1);
    }
    delete[]pbs;
    delete[]pts;

    // 关联还原数据
    RelatedBulletAndTankAndMap();
}

void Game::RelatedBulletAndTankAndMap() {
    // 初始化数据
    for (size_t i = 0; i < m_arrBullets.size(); i++) {
        m_arrBullets[i]->m_pMap = m_pMap; // 关联地图指针
        for (size_t j = 0; j < m_arrTanks.size(); j++) {
            if (m_arrTanks[j]->m_dwPrevID == m_arrBullets[i]->m_dwTankID) {
                m_arrBullets[i]->m_dwTankID = m_arrTanks[j]->m_dwID;
                m_arrBullets[i]->m_pTank = m_arrTanks[j]; // 关联坦克和子弹的关系
            }
        }
        if (m_arrBullets[i]->m_dwTankID == m_pTank->m_dwPrevID) {
            m_arrBullets[i]->m_dwTankID = m_pTank->m_dwID;
            m_arrBullets[i]->m_pTank = m_pTank;
        }
        if (m_pTank2 != nullptr && m_arrBullets[i]->m_dwTankID == m_pTank2->m_dwPrevID) {
            m_arrBullets[i]->m_dwTankID = m_pTank2->m_dwID;
            m_arrBullets[i]->m_pTank = m_pTank2;
        }
    }
    m_bIsReadFromFile = true;
    PlayGame(m_nPlayerCount);
}


void Game::ChoiceMenu() {
    switch (m_nCurrentMenu) {
        case Game::ONEPLAY:
            m_nPlayerCount = 1;
            PlayGame(1); // 不要问我为什么这样写，因为原先没想到。。现在想到了。不想改原来的代码。
            //WriteChar("单人游戏", 1, 1, BACKGROUND_BLUE);
            break;
        case Game::TWOPLAY:
            m_nPlayerCount = 2;
            PlayGame(2);
            //WriteChar("双人游戏", 1, 1, BACKGROUND_BLUE);
            break;
        case Game::READFILE:
            ReadFile();
            //WriteChar("从存档开", 1, 1, BACKGROUND_BLUE);
            break;
        case Game::MAPEDIT:
            m_pMap->Edit();
            break;
        case Game::EXIT:
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}


void Game::SetWindowSize() {
	// 设置控制台标题
	HANDLE hStdOut, hStdin;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 获得最大控制台窗口大小
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X + 1,pos.Y + 1 };
	// 设置控制台缓冲区大小
	SetConsoleScreenBufferSize(hStdOut, BufferSize);

	SMALL_RECT srctWindow = { 0, 0, g_nWidth, g_nHeight };
	SetConsoleWindowInfo(hStdOut, 1, &srctWindow);

	COORD Buffer = { g_nWidth + 1, g_nWidth + 1 };
	// 设置控制台缓冲区大小
	SetConsoleScreenBufferSize(hStdOut, Buffer);
}

void Game::SetWindowTitle() {
	SetConsoleTitle(TEXT("坦克大战~"));
}
