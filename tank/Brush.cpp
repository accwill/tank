#include "Brush.h"

void CBrush::RealDraw1(int nX, int nY) {
	// ��ӡ�ַ�
	WriteChar(m_word, nX, nY, m_wColor, m_bBKG);
	// �洢/ɾ����ͼ����
	m_cMap->SaveMapEditPointer(nX, nY);
}

void CBrush::RealDraw2(int nX, int nY) {
	int nNewY = nY + 1;
	if (nX >= (m_cMap->m_nMaxWidth - 4) / 2) nX = m_cMap->m_nMaxWidth / 2 - 2;
	if (nNewY >= m_cMap->m_nMaxHeight) nNewY = m_cMap->m_nMaxHeight - 2;
	std::string str(m_word);
	str += str;
	// ��ӡ�ַ�
	WriteChar(str, nX, nY, m_wColor, m_bBKG);
	WriteChar(str, nX, nNewY, m_wColor, m_bBKG);

	// �洢/ɾ����ͼ����
	m_cMap->SaveMapEditPointer(nX, nY);
	m_cMap->SaveMapEditPointer(nX + 1, nY);
	m_cMap->SaveMapEditPointer(nX, nNewY);
	m_cMap->SaveMapEditPointer(nX + 1, nNewY);
}

CBrush::CBrush(CMap* pMap) {
    m_cMap = pMap;
}

void CBrush::operator++(int) {
	if (++m_nSize < 2) {
		return;
	}
	m_nSize = 2;
}

void CBrush::operator--(int) {
	if (--m_nSize > 1) {
		return;
	}
	m_nSize = 1;
}

void CBrush::Draw(int nX, int nY) {
	switch (m_nSize) {
		case 1:
			RealDraw1(nX, nY);
			break;
		case 2:
			RealDraw2(nX, nY);
			break;
	}
}