#include "framework.h"
#include "Phase2UI.h"
#include "SceneMgr.h"
#include "ResourcesMgr.h"

CPhase2UI::CPhase2UI()
{
}

CPhase2UI::~CPhase2UI()
{
}

void CPhase2UI::Init()
{
	m_eRenderGroup = RENDER_SORT::PAHSE2_UI;
	m_tInfo.iCX = 801;
	m_tInfo.iCY = 40;
}

int CPhase2UI::Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE2)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase2UI::Late_Update()
{
}

void CPhase2UI::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, 801, 40
		, RGB(255, 0, 255));
}

void CPhase2UI::Release()
{
}
