#include "framework.h"
#include "PotionUI.h"
#include "ResourcesMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CPotionUI::CPotionUI()
{
}

CPotionUI::~CPotionUI()
{
}

void CPotionUI::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;
	m_tInfo.iCX = 32;
	m_tInfo.iCY = 32;
	m_pFrameKey = L"Potion_NoEnabled";
}

int CPotionUI::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPotionUI::Late_Update()
{
}

void CPotionUI::Render(HDC _DC)
{
	Update_Rect();	

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));

	
}

void CPotionUI::Release()
{
}
