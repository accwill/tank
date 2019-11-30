#pragma once

#include "Tank.h"
#include "Tools.h"

CTank::CTank(CMap* pMap) {
    m_pMap = pMap;
}

void CTank::Show(DIR eDir) {
    m_eDir = eDir;
    switch (m_eDir) {
        //TODO：边界判定
        case DIR::UP:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY - 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY + 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY + 1, m_cWord, m_wColor, this);
            break;
        case DIR::DOWN:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY + 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY - 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY - 1, m_cWord, m_wColor, this);
            break;
        case DIR::LEFT:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY + 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY - 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY + 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY - 1, m_cWord, m_wColor, this);
            break;
        case DIR::RIGHT:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY + 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY - 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY + 1, m_cWord, m_wColor, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY - 1, m_cWord, m_wColor, this);
            break;
    }
}

void CTank::Hide() {
    //TODO: 不一定是A 可能是森林。以及边界判定
    switch (m_eDir) {
        case DIR::UP:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY - 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY + 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY + 1, this);
            break;
        case DIR::DOWN:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY + 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY - 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY - 1, this);
            break;
        case DIR::LEFT:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY + 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY - 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY + 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY - 1, this);
            break;
        case DIR::RIGHT:
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX + 1, m_nPosY, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY + 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX, m_nPosY - 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY + 1, this);
            m_pMap->PrintGlassForCoor(m_nPosX - 1, m_nPosY - 1, this);
            break;
    }
}

void CTank::Move(CTank::DIR eDir) {
    if (m_nBlood == 0) return;
    Hide();
    m_eDir = eDir;
    switch (eDir) {
        case DIR::UP:
            if (isValidMove(eDir, m_nPosX, m_nPosY - 1)) { // 如果不是有效的移动则只转向
                m_nPosY--;
            }
            Show(eDir);
            break;
        case DIR::DOWN:
            if (isValidMove(eDir, m_nPosX, m_nPosY + 1)) {
                m_nPosY++;
            }
            Show(eDir);
            break;
        case DIR::LEFT:
            if (isValidMove(eDir, m_nPosX - 1, m_nPosY)) {
                m_nPosX--;
            }
            Show(eDir);
            break;
        case DIR::RIGHT:
            if (isValidMove(eDir, m_nPosX + 1, m_nPosY)) {
                m_nPosX++;
            }
            Show(eDir);
            break;
    }
}

bool CTank::isValidMove(DIR eDir, int nX, int nY) {
    //if (m_bIsDie) return false;
    // 坦克和坦克，坦克和地图的碰撞检测
    bool isValid = true;
    MDType md = m_pMap->GetData();
    CMap::STATE state[5] = { CMap::STATE::zero };
    int arrType[5] = { 0 };
    switch (eDir) {
        case CTank::DIR::UP:
            state[0] = static_cast<CMap::STATE>(md[nY - 1][nX]);
            state[1] = static_cast<CMap::STATE>(md[nY][nX - 1]);
            state[2] = static_cast<CMap::STATE>(md[nY][nX + 1]);
            state[3] = static_cast<CMap::STATE>(md[nY + 1][nX - 1]);
            state[4] = static_cast<CMap::STATE>(md[nY + 1][nX + 1]);
            arrType[0] = arrTanksCoor[nY - 1][nX];
            arrType[1] = arrTanksCoor[nY][nX - 1];
            arrType[2] = arrTanksCoor[nY][nX + 1];
            arrType[3] = arrTanksCoor[nY + 1][nX - 1];
            arrType[4] = arrTanksCoor[nY + 1][nX + 1];
            break;
        case CTank::DIR::DOWN:
            state[0] = static_cast<CMap::STATE>(md[nY + 1][nX]);
            state[1] = static_cast<CMap::STATE>(md[nY][nX - 1]);
            state[2] = static_cast<CMap::STATE>(md[nY][nX + 1]);
            state[3] = static_cast<CMap::STATE>(md[nY - 1][nX - 1]);
            state[4] = static_cast<CMap::STATE>(md[nY - 1][nX + 1]);
            arrType[0] = arrTanksCoor[nY + 1][nX];
            arrType[1] = arrTanksCoor[nY][nX - 1];
            arrType[2] = arrTanksCoor[nY][nX + 1];
            arrType[3] = arrTanksCoor[nY - 1][nX - 1];
            arrType[4] = arrTanksCoor[nY - 1][nX + 1];
            break;
        case CTank::DIR::LEFT:
            state[0] = static_cast<CMap::STATE>(md[nY][nX - 1]);
            state[1] = static_cast<CMap::STATE>(md[nY + 1][nX]);
            state[2] = static_cast<CMap::STATE>(md[nY - 1][nX]);
            state[3] = static_cast<CMap::STATE>(md[nY - 1][nX + 1]);
            state[4] = static_cast<CMap::STATE>(md[nY + 1][nX + 1]);
            arrType[0] = arrTanksCoor[nY][nX - 1];
            arrType[1] = arrTanksCoor[nY + 1][nX];
            arrType[2] = arrTanksCoor[nY - 1][nX];
            arrType[3] = arrTanksCoor[nY - 1][nX + 1];
            arrType[4] = arrTanksCoor[nY + 1][nX + 1];
        case CTank::DIR::RIGHT:
            state[0] = static_cast<CMap::STATE>(md[nY][nX + 1]);
            state[1] = static_cast<CMap::STATE>(md[nY + 1][nX]);
            state[2] = static_cast<CMap::STATE>(md[nY - 1][nX]);
            state[3] = static_cast<CMap::STATE>(md[nY - 1][nX - 1]);
            state[4] = static_cast<CMap::STATE>(md[nY + 1][nX - 1]);
            arrType[0] = arrTanksCoor[nY][nX + 1];
            arrType[1] = arrTanksCoor[nY + 1][nX];
            arrType[2] = arrTanksCoor[nY - 1][nX];
            arrType[3] = arrTanksCoor[nY - 1][nX - 1];
            arrType[4] = arrTanksCoor[nY + 1][nX - 1];
            break;
    }

    for (int nI = 0; nI < 5; nI++) {
        switch (state[nI]) {
            case CMap::STATE::river:
            case CMap::STATE::wall:
            case CMap::STATE::brickwall:
                isValid = false;
        }
        if (!isValid) break;
    }

    for (int nI = 0; nI < 5; nI++) { // 判断是否为坦克
        if (arrType[nI] != 0) {
            isValid = false;
            break;
        }
    }

    return isValid;
}
int CTank::GetType() {
    return m_nType;
}
void CTank::SetDie() {
    m_bIsDie = true;
}
int CTank::GetX(bool isBullet) {
    switch (m_eDir) {
        case CTank::DIR::UP:
            return m_nPosX;
        case CTank::DIR::DOWN:
            return m_nPosX;
        case CTank::DIR::LEFT:
            return m_nPosX - 1;
        case CTank::DIR::RIGHT:
            return m_nPosX + 1;
    }
    return 0;
}
int CTank::GetY(bool isBullet) {
    switch (m_eDir) {
        case CTank::DIR::UP:
            return m_nPosY - 1;
        case CTank::DIR::DOWN:
            return m_nPosY + 1;
        case CTank::DIR::LEFT:
            return m_nPosY;
        case CTank::DIR::RIGHT:
            return m_nPosY;
    }
    return 0;
}
//
//上
//x, y
//x, y - 1
//
//x - 1, y
//x + 1, y
//
//x + 1, y + 1
//x - 1, y + 1
//
//下
//x, y
//x, y + 1
//
//x - 1, y
//x + 1, y
//
//x - 1, y + 1
//x - 1, y - 1
//
//
//左
//x, y
//x - 1, y
//
//x, y + 1
//x, y - 1
//
//x + 1, y - 1
//x + 1, y + 1
//
//右
//x, y
//x + 1, y
//
//x, y + 1
//x, y - 1
//
//x - 1, y + 1
//x - 1, y - 1
