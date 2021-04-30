#include "framework.h"
#include "Phase1BlueHP.h"
#include "Phase1.h"
#include "ResourcesMgr.h"
#include "BossStage1.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

CPhase1BlueHP::CPhase1BlueHP()
{
}

CPhase1BlueHP::~CPhase1BlueHP()
{
	Release();
}

void CPhase1BlueHP::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/WILL_BLUEHP.bmp", L"BLUEHP");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/WILL_GRAYHP.bmp", L"GRAYHP");

	m_eRenderGroup = RENDER_SORT::PAHSE1_UI;
	m_pFrameKey = L"BLUEHP";
	m_tInfo.iCX = 757;
	m_tInfo.iCY = 6;
}

void CPhase1BlueHP::Late_Init()
{

}

int CPhase1BlueHP::Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE1)
		return OBJ_DEAD;
	Late_Init();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase1BlueHP::Late_Update()
{
	bool bSceneCheck = dynamic_cast<CBossStage1*>(CSceneMgr::Get_Instance()->Get_CurrentScene())->Get_bChangeMap();
	if (!bSceneCheck)
	{
		m_pFrameKey = L"BLUEHP";
	}
	else
	{
		m_pFrameKey = L"GRAYHP";
	}
}

void CPhase1BlueHP::Render(HDC _DC)
{
	float fFillAmount = dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_BlueHP() /
		dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_MaxBlueHP();

	if (0.f > fFillAmount)
		fFillAmount = 0.f;

	m_tRect.right = LONG(m_tInfo.iCX * fFillAmount);

	HDC hMemDC= CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tRect.right, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));

}

void CPhase1BlueHP::Release()
{
}
