#pragma once
typedef struct _GAME {
    int nLevel;
    int nCurrentMenu;
    int TankCount[6];
    int TankDieCount[6];
    int AlReadyGeneratorTankCount[6];
    int nPlayerCount;
} GAME;