#include "CBullet.h"

CBullet* CBullet::OpenUpSpaceForCount(int nCount) {
    return new CBullet[nCount];
}

void CBullet::Move() {
    Hide();
    switch (m_eDir) {
        case CBullet::DIR::UP:
            if (DecideIsDie(m_nX, m_nY - 1)) {
                Hide(m_nX, m_nY - 1);
                break;
            }
            m_nY--;
            Show();
            break;
        case CBullet::DIR::DOWN:
            if (DecideIsDie(m_nX, m_nY + 1)) {
                Hide(m_nX, m_nY + 1);
                break;
            }
            m_nY++;
            Show();
            break;
        case CBullet::DIR::LEFT:
            if (DecideIsDie(m_nX - 1, m_nY)) {
                Hide(m_nX - 1, m_nY);
                break;
            }
            m_nX--;
            Show();
            break;
        case CBullet::DIR::RIGHT:
            if (DecideIsDie(m_nX + 1, m_nY)) {
                Hide(m_nX + 1, m_nY); // �������ǽ������ǽ
                break;
            }
            m_nX++;
            Show();
            break;
    }
}

void CBullet::Hide() {
    m_pMap->PrintGlassForCoor(m_nX, m_nY, this);
}

void CBullet::Hide(int nX, int nY) {
    m_pMap->PrintGlassForCoor(nX, nY, this);
}

void CBullet::Show() {
    m_pMap->PrintGlassForCoor(m_nX, m_nY, szWord, wColor, this);
}

int CBullet::GetType() {
    return m_nType;
}

bool CBullet::GetDie() {
    return m_bIsDie;
}

bool CBullet::DecideIsDie(int nX, int nY) {
    MDType md = m_pMap->GetData();
    CMap::STATE eState = static_cast<CMap::STATE>(md[nY][nX]);
    CTank* pTank = CTank::oMapTank[std::to_string(nX) + "," + std::to_string(nY)];
    CBullet* pBullet = CBullet::oMapBullt[std::to_string(nX) + "," + std::to_string(nY)];
    
    if (pBullet != nullptr && pBullet != this && 
        this->m_pTank->GetType() != pBullet->m_pTank->GetType()) {  // �ӵ������ӵ�,����ֻ�в�ͬ����ӵ�����ײ�Ż����ӵ���ʧ
        pBullet->m_bIsDie = true;
        pBullet->Hide(); // ��һ��������
        m_bIsDie = true;
        return m_bIsDie;
    }

    if (pTank != nullptr && pTank != m_pTank && pTank->GetType() != m_pTank->GetType()) { // ��ʾ����̹��������̹�˲���ͬ��
        // �������ڶ���ѭ������
        m_bIsDie = true;
        m_pTank->Incoming();  // �ӷ�
        m_pTank->IncomKill(); // ��¼����
        pTank->Hited();       // �� ��������

        if (pTank->GetHP() <= 0) { // �жϻ���û��Ѫ��
            pTank->Hide();
            pTank->SetDie();
        }
        return m_bIsDie;
    }

    // ��Ե�ͼ���ж�
    int nType = arrBulletsCoor[nY][nX];
    switch (eState) { 
        case CMap::STATE::wall:
            m_bIsDie = true;
            break;
        case CMap::STATE::brickwall:
            m_bIsDie = true;
            md[nY][nX] = 0;
            break;
        case CMap::STATE::home:
            WriteChar("��Ϸ����", 20, 31, 1, true);
            WriteChar("����3����˳�����", 18, 32, 1, true);
            Sleep(3000);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
    if (nType != 0) {
        m_bIsDie = true;
        arrBulletsCoor[nY][nX] = 0;
    }

    return m_bIsDie;
}
