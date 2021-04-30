#include "framework.h"
#include "Phase1MainHP.h"
#include "Phase1.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CPhase1MainHP::CPhase1MainHP()
{
}

CPhase1MainHP::~CPhase1MainHP()
{
	Release();
}

void CPhase1MainHP::Init()
{
	m_eRenderGroup = RENDER_SORT::PAHSE1_UI;

	m_tInfo.iCX = 757;
	m_tInfo.iCY = 12;
}

void CPhase1MainHP::Late_Init()
{
}

int CPhase1MainHP::Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE1)
		return OBJ_DEAD;
	Late_Init();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase1MainHP::Late_Update()
{
}

void CPhase1MainHP::Render(HDC _DC)
{
	float fFillAmount = dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Stat().fHp /
		dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Stat().fMaxHp;

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

void CPhase1MainHP::Release()
{
}
