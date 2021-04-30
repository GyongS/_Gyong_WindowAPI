#include "framework.h"
#include "MoonCover.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"
CMoonCover::CMoonCover()
{
}

CMoonCover::~CMoonCover()
{
}

void CMoonCover::Init()
{
	m_eRenderGroup = RENDER_SORT::BOSSMAIN_UI;
	m_tInfo.iCX = 54;
	m_tInfo.iCY = 54;

}

int CMoonCover::Update()
{
	if (m_bDead || CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE1)
	{
		return OBJ_DEAD;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMoonCover::Late_Update()
{
}

void CMoonCover::Render(HDC _DC)
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

void CMoonCover::Release()
{
}
