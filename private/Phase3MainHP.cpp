#include "framework.h"
#include "Phase3MainHP.h"
#include "SceneMgr.h"
#include "Phase3.h"
#include "ObjMgr.h"
#include "ResourcesMgr.h"

CPhase3MainHP::CPhase3MainHP()
{
}

CPhase3MainHP::~CPhase3MainHP()
{
}

void CPhase3MainHP::Init()
{
	m_eRenderGroup = RENDER_SORT::PAHSE3_UI;
	m_tInfo.iCX = 757;
	m_tInfo.iCY = 12;
}

int CPhase3MainHP::Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE3)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase3MainHP::Late_Update()
{
}

void CPhase3MainHP::Render(HDC _DC)
{
	Update_Rect();

	float fFillAmount = dynamic_cast<CPhase3*>(CObjMgr::Get_Instance()->Get_Phase3())->Get_Stat().fHp /
		dynamic_cast<CPhase3*>(CObjMgr::Get_Instance()->Get_Phase3())->Get_Stat().fMaxHp;

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

void CPhase3MainHP::Release()
{
}
