#include "framework.h"
#include "MainUI.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CMainUI::CMainUI()
{
}

CMainUI::~CMainUI()
{
	Release();
}

void CMainUI::Init()
{
	m_eRenderGroup = RENDER_SORT::BOSSMAIN_UI;

	m_tInfo.iCX = 1366;
	m_tInfo.iCY = 768;

}

void CMainUI::Late_Init()
{
}

int CMainUI::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMainUI::Late_Update()
{
}

void CMainUI::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, 1366, 768
		, RGB(255, 0, 255));
}

void CMainUI::Release()
{
}
