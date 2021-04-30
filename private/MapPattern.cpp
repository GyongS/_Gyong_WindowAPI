#include "framework.h"
#include "MapPattern.h"
#include "ResourcesMgr.h"
#include "SpyderLeg.h"
#include "Beholder.h"
#include "BeholderEye.h"
#include "Phase1.h"
#include "Player.h"
#include "MonitorBreak.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CMapPattern::CMapPattern() : m_fSpyderLegDelay(0.f), m_fBeholderDelay(0.f), m_bSpawnBeholderEye(false), m_fMonitorBreakDelay(0.f)
, m_bSpawnMonitorBreak(false)
{

}


CMapPattern::~CMapPattern()
{
	Release();
}

void CMapPattern::Init()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	m_eRenderGroup = RENDER_SORT::OBJECT;
}


int CMapPattern::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (!m_bSpawnBeholderEye)
	{
		PATTERN_SPYDERLEG();
		PATTERN_BEHOLDER();
	}

	PATTERN_BEHOLDER_EYE();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMapPattern::Late_Update()
{
}

void CMapPattern::Render(HDC _DC)
{
}

void CMapPattern::Release()
{
}

void CMapPattern::PATTERN_SPYDERLEG()
{
	m_fSpyderLegDelay += 1.f;

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
	{
		if (m_fSpyderLegDelay >= 300.f)
		{
			float fX = 0.f;

			for (int i = 0; i < 4; ++i)
			{
				CObj* pObj = CAbstractFactory<CSpyderLeg>::Create((m_tInfo.fX + fX) + fX,
					m_tInfo.fY + 100);
				CObjMgr::Get_Instance()->Add_Object(OBJID::SPYDERLEG, pObj);
				fX += (rand() % 100) + 150.f;
			}

			fX = 0.f;
			m_fSpyderLegDelay = 0.f;
		}

	}
	else
	{
		if (m_fSpyderLegDelay >= 300.f)
		{
			float fX = 0.f;

			for (int i = 0; i < 4; ++i)
			{
				CObj* pObj = CAbstractFactory<CSpyderLeg>::Create((m_tInfo.fX + fX) + fX, m_tInfo.fY + 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::SPYDERLEG, pObj);
				fX += (rand() % 100) + 150.f;
			}
			fX = 0.f;
			m_fSpyderLegDelay = 0.f;
		}

	}
}

void CMapPattern::PATTERN_BEHOLDER()
{
	m_fBeholderDelay += 1.f;
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1)
	{
		if (m_fBeholderDelay >= 700.f)
		{
			float fX = 200.f;

			for (int i = 0; i < 2; ++i)
			{
				CObj* pObj = CAbstractFactory<CBeholder>::Create(m_tInfo.fX + fX, m_tInfo.fY + 150);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_PATTERN, pObj);
				fX += 800.f;
			}
			fX = 0.f;
			m_fBeholderDelay = 0.f;
		}
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
	{
		if (m_fBeholderDelay >= 700.f)
		{
			float fX = 200.f;

			for (int i = 0; i < 2; ++i)
			{
				CObj* pObj = CAbstractFactory<CBeholder>::Create(m_tInfo.fX + fX, m_tInfo.fY + 50);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_PATTERN, pObj);
				fX += 800.f;
			}
			fX = 0.f;
			m_fBeholderDelay = 0.f;
		}
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
	{
		if (m_fBeholderDelay >= 700.f)
		{
			float fX = 200.f;

			for (int i = 0; i < 2; ++i)
			{
				CObj* pObj = CAbstractFactory<CBeholder>::Create(m_tInfo.fX + fX, m_tInfo.fY + 150);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_PATTERN, pObj);
				fX += 800.f;
			}
			fX = 0.f;
			m_fBeholderDelay = 0.f;
		}
	}

}

void CMapPattern::PATTERN_BEHOLDER_EYE()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1)
	{
		if (dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Block_BlueHP() &&
			dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Block_PurpleHP() &&
			!m_bSpawnBeholderEye)
		{
			CObj* pObj = CAbstractFactory<CBeholderEye>::Create(700, 580);
			CObjMgr::Get_Instance()->Add_Object(OBJID::BEHOLDER_EYE, pObj);
			m_bSpawnBeholderEye = true;
		}

		else if (m_bSpawnBeholderEye && !m_bSpawnMonitorBreak)
		{
			m_fMonitorBreakDelay += 1.f;
			if (m_fMonitorBreakDelay >= 500.f)
			{
				CObj* pObj = CAbstractFactory<CMonitorBreak>::Create(680, 380);
				CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSSKILL, pObj);
				m_bSpawnMonitorBreak = true;
				m_fMonitorBreakDelay = 0.f;
			}
		}
	}
}


