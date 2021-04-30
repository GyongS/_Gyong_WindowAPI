#include "framework.h"
#include "Phase2MainHP.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Phase2.h"
#include "ResourcesMgr.h"

CPhase2MainHP::CPhase2MainHP()
{
}

CPhase2MainHP::~CPhase2MainHP()
{
}

void CPhase2MainHP::Init()
{
	m_eRenderGroup = RENDER_SORT::PAHSE2_UI;
	m_tInfo.iCX = 757;
	m_tInfo.iCY = 12;
}

int CPhase2MainHP::Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE2)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase2MainHP::Late_Update()
{
}

void CPhase2MainHP::Render(HDC _DC)
{
	float fFillAmount = dynamic_cast<CPhase2*>(CObjMgr::Get_Instance()->Get_Phase2())->Get_Stat().fHp /
		dynamic_cast<CPhase2*>(CObjMgr::Get_Instance()->Get_Phase2())->Get_Stat().fMaxHp;

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

void CPhase2MainHP::Release()
{
}
