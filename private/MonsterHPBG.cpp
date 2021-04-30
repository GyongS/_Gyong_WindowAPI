#include "framework.h"
#include "MonsterHPBG.h"
#include "ResourcesMgr.h"
#include "ScrollMgr.h"
CMonsterHPBG::CMonsterHPBG()
{
}

CMonsterHPBG::~CMonsterHPBG()
{
}

void CMonsterHPBG::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/MonsterHP/MonsterHPBack.bmp", L"MonsterHPBG");
	m_eRenderGroup = RENDER_SORT::UI;

	m_tInfo.iCX = 52;
	m_tInfo.iCY = 10;
	m_pFrameKey = L"MonsterHPBG";
}

int CMonsterHPBG::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterHPBG::Late_Update()
{
	if (nullptr == m_pTarget)
	{
		m_bDead = true;
		return;
	}

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY - 100.f;
}

void CMonsterHPBG::Render(HDC _DC)
{
	Update_Rect();
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CMonsterHPBG::Release()
{
}
