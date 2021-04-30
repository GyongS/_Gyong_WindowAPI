#include "framework.h"
#include "Phase3UI.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"

CPhase3UI::CPhase3UI()
{
}

CPhase3UI::~CPhase3UI()
{
}

void CPhase3UI::Init()
{
	m_eRenderGroup = RENDER_SORT::PAHSE3_UI;
	m_tInfo.iCX = 801;
	m_tInfo.iCY = 40;
}

int CPhase3UI::Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE3)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase3UI::Late_Update()
{
}

void CPhase3UI::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, 801, 40
		, RGB(255, 0, 255));
}

void CPhase3UI::Release()
{
}
