#include "framework.h"
#include "HowlingGailUsed.h"
#include "ResourcesMgr.h"
#include "HowlingGail.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CHowlingGailUsed::CHowlingGailUsed() : m_bCheck(false)
{
}

CHowlingGailUsed::~CHowlingGailUsed()
{
}

void CHowlingGailUsed::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/HowlingGail/HowlingGail_USED.bmp", L"HowlingGail_USED");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/HowlingGail/STRETCH.bmp", L"STRETCH");
	m_eRenderGroup = RENDER_SORT::EFFECT;
	m_pFrameKey = L"HowlingGail_USED";
	m_pStretch = L"STRETCH";
	m_tInfo.iCX = 615;
	m_tInfo.iCY = 556;

	m_tFrame.iStartX = 0;
	m_tFrame.iEndX  = 15;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
	if (CObjMgr::Get_Instance()->Get_Player()->Get_bRight())
	{
		m_bCheck = true;
	}
}

void CHowlingGailUsed::Late_Init()
{
	if (m_bCheck)
	{
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + 60;
	}
	else
	{
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 60;
	}
}

int CHowlingGailUsed::Update()
{
	CObj::Late_Init();
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHowlingGailUsed::Late_Update()
{

	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1)
		{
			CObj* pObj = CAbstractFactory<CHowlingGail>::Create(m_tInfo.fX, m_tInfo.fY - 300);
			pObj->Set_Target(CObjMgr::Get_Instance()->Get_Phase1());
			CObjMgr::Get_Instance()->Add_Object(OBJID::HOWLING, pObj);
			m_bDead = true;
		}
		if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
		{
			CObj* pObj = CAbstractFactory<CHowlingGail>::Create(m_tInfo.fX, m_tInfo.fY - 300);
			pObj->Set_Target(CObjMgr::Get_Instance()->Get_Phase2());
			CObjMgr::Get_Instance()->Add_Object(OBJID::HOWLING, pObj);
			m_bDead = true;
		}
		if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
		{
			CObj* pObj = CAbstractFactory<CHowlingGail>::Create(m_tInfo.fX, m_tInfo.fY - 300);
			pObj->Set_Target(CObjMgr::Get_Instance()->Get_Phase3());
			CObjMgr::Get_Instance()->Add_Object(OBJID::HOWLING, pObj);
			m_bDead = true;
		}
		
	}
}

void CHowlingGailUsed::Render(HDC _DC)
{
	Update_Rect();
	if (m_bCheck)
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left, m_tRect.top);
	}
	else
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left, m_tRect.top);

	}
}

void CHowlingGailUsed::Release()
{
}
