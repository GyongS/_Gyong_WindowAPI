#include "framework.h"
#include "DamageSkin.h"
#include "Player.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "ResourcesMgr.h"

CDamageSkin::CDamageSkin() : m_fDelay(0.f)
{
}

CDamageSkin::~CDamageSkin()
{
}

void CDamageSkin::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/DefaultDmgSkin/DefaultDmgSkin.bmp", L"DefaultDmgSkin");
	m_eRenderGroup = RENDER_SORT::OBJECT;

	m_tInfo.iCX = 31;
	m_tInfo.iCY = 33;
}

int CDamageSkin::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	m_fDelay += 1.f;
	m_tInfo.fY -= 1.5f;
	if (m_fDelay >= 100.f)
	{
		m_bDead = true;
	}

	return OBJ_NOEVENT;
}

void CDamageSkin::Late_Update()
{
}

void CDamageSkin::Render(HDC _DC)
{
	Update_Rect();

	int iCorrectionX = 0;
	int iDamage = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Stat().iDamage;

	while (iDamage != 0)
	{
		int value = iDamage % 10;
		iDamage /= 10;

		int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"DefaultDmgSkin");
		GdiTransparentBlt(_DC
			, m_tInfo.fX + iScrollX - iCorrectionX, m_tInfo.fY + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tInfo.iCX * value, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));

		iCorrectionX += m_tInfo.iCX - 5;
	}
}

void CDamageSkin::Release()
{
}
