#include "framework.h"
#include "MonsterHPbar.h"
#include "ResourcesMgr.h"
#include "ScrollMgr.h"

CMonsterHPbar::CMonsterHPbar()
{
}

CMonsterHPbar::~CMonsterHPbar()
{
	Release();
}

void CMonsterHPbar::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/MonsterHP/MonsterHP.bmp", L"MonsterHP");
	m_tInfo.iCX = 46;
	m_tInfo.iCY = 4;
	m_pFrameKey = L"MonsterHP";
}

int CMonsterHPbar::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CMonsterHPbar::Late_Update()
{
	if (nullptr == m_pTarget)
	{
		m_bDead = true;
		return;
	}

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY - 100.f;
}

void CMonsterHPbar::Render(HDC _DC)
{
	if (nullptr == m_pTarget)
		return;

	Update_Rect();
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	float fFillAmount = m_pTarget->Get_Stat().fHp / m_pTarget->Get_Stat().fMaxHp;

	if (0.f > fFillAmount)
		fFillAmount = 0.f;

	m_tRect.right = LONG(m_tInfo.iCX * fFillAmount);	

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tRect.right, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));

	
}

void CMonsterHPbar::Release()
{

}
