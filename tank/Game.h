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
	enum DIR { // ѡ��
		UP = 'w', 
		DOWN = 's',
		OK = '\r'
	};

    enum OPERATION { // ����
        ONEPLAY,     // ������Ϸ
        TWOPLAY,     // ˫����Ϸ
        READFILE,    // ��ȡ��Ϸ
        MAPEDIT,     // ��ͼ�༭
        EXIT         // �˳���Ϸ
    };
    int m_nCurrentMenu = 0; // �ü���ѡ�еĲ˵�
    int m_nPlayerCount = 1;
    bool m_bNextLevel = false;
    int m_nLevel = 0;       // �ؿ�
    const int m_nMAXLEVEL = 5;
    Map m_mapTankCount;     // ��Ӧ�ؿ���̹�˵�����
    Map m_mapTankDieCount;  // ��Ӧ�ؿ����Ѿ���ȥ������
    CMap* m_pMap;
    CTank* m_pTank;
    CTank* m_pTank2;

    strings m_szMenus = { // �˵�
		" ������Ϸ ",
		" ˫����Ϸ ",
		" ��ȡ��Ϸ ",
		" ��ͼ�༭ ",
		" ������Ϸ "
	};
    Bullets m_arrBullets;
    Tanks m_arrTanks;                       // ÿһ�ض�Ӧ��̹������
    Map m_mapAlReadyGeneratorTankCount;     // ��Ӧ�ؿ����Ѿ����ɵ�̹������ͳ��
    int m_mapEverGeneratorTankCout = 6;     // ÿ�����ɶ��ٸ�̹��
    bool m_bIsReadFromFile = false;         // �Ƿ���������
    // ѡ��˵�
    void ChoiceMenu();
    // ����NPC
    void GeneratorNPC();

    // ������һ��
    void NextLevel();

    // չʾ�Ҳ�Ĳ˵�
    void ShowMenu();

    // �ж��Ƿ���Ϸ������
    void DecideIsGameOver();

    // �浵
    void WriteFile();

    // ����
    void ReadFile();

    // ����̹�˺��ӵ����Լ�̹�˺͵�ͼ���ӵ��͵�ͼ
    void RelatedBulletAndTankAndMap();

    // ���˵�
    void WriteMenu();

    // ��ӡ����
    void WriteTitle();

    // ѡ��˵�
    void SelectMenu();
public:
    Game();

    // ��ʼ��Ϸ
    void StartGame();

    // ����Ϸ
    void PlayGame(int n);

	// ���ô��ڵĴ�С
	void SetWindowSize(); 
	
	// ����window�ı���
	void SetWindowTitle(); 

    // �����¼�
    void KeyEvent();


};