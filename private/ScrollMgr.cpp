#include "framework.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0 < m_fScrollX)
		m_fScrollX = 0.f;

	if (0 < m_fScrollY)
		m_fScrollY = 0.f;

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{
		if (m_fScrollX < WINCX - MONSTERMAP_CX)
			m_fScrollX = WINCX - MONSTERMAP_CX;

		if (m_fScrollY < WINCY - MONSTERMAP_CY)
			m_fScrollY = WINCY - MONSTERMAP_CY;
	}
	else
	{
		if (m_fScrollX < WINCX - WINCX)
			m_fScrollX = WINCX - WINCX;

		if (m_fScrollY < WINCY - WINCY)
			m_fScrollY = WINCY - WINCY;
	}
}
