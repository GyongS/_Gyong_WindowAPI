#include "framework.h"
#include "LockHP.h"
#include "ResourcesMgr.h"

CLockHP::CLockHP()
{
}

CLockHP::~CLockHP()
{
}

void CLockHP::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/Phase1_will_Mainhp_Block.bmp", L"HPBLOCK");
	m_eRenderGroup = RENDER_SORT::PAHSE1_UI;

	m_tInfo.iCX = 4;
	m_tInfo.iCY = 12;
}

int CLockHP::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CLockHP::Late_Update()
{
}

void CLockHP::Render(HDC _DC)
{
	Update_Rect();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"HPBLOCK");

	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CLockHP::Release()
{
}
