#include "framework.h"
#include "MPbar.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"

CMPbar::CMPbar()
{
}

CMPbar::~CMPbar()
{
}

void CMPbar::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;

	m_tInfo.iCX = 171;
	m_tInfo.iCY = 13;
}

int CMPbar::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMPbar::Late_Update()
{
}

void CMPbar::Render(HDC _DC)
{
	float fFillAmount = CObjMgr::Get_Instance()->Get_Player()->Get_Stat().fMp / CObjMgr::Get_Instance()->Get_Player()->Get_Stat().fMaxMp;

	if (0.f > fFillAmount)
		fFillAmount = 0.f;

	m_tRect.right = LONG(m_tInfo.iCX * fFillAmount);

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tRect.right, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CMPbar::Release()
{
}
