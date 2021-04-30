#include "framework.h"
#include "MapleBuffIcon.h"
#include "ResourcesMgr.h"
CMapleBuffIcon::CMapleBuffIcon()
{
}

CMapleBuffIcon::~CMapleBuffIcon()
{
}

void CMapleBuffIcon::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/BUFF/MapleWarrior_Icon.bmp", L"MapleWarrior_Icon");
	m_tInfo.iCX = 32;
	m_tInfo.iCY = 32;
	m_pFrameKey = L"MapleWarrior_Icon";

}

int CMapleBuffIcon::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMapleBuffIcon::Late_Update()
{
}

void CMapleBuffIcon::Render(HDC _DC)
{
	Update_Rect();
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CMapleBuffIcon::Release()
{
}
