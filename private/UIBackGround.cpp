#include "framework.h"
#include "UIBackGround.h"
#include "ResourcesMgr.h"

CUIBackGround::CUIBackGround()
{
}

CUIBackGround::~CUIBackGround()
{
}

void CUIBackGround::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;

	m_tInfo.iCX = 200;
	m_tInfo.iCY = 80;
}

int CUIBackGround::Update()
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CUIBackGround::Late_Update()
{
}

void CUIBackGround::Render(HDC _DC)
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

void CUIBackGround::Release()
{
}
