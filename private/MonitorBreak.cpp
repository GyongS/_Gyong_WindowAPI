#include "framework.h"
#include "MonitorBreak.h"
#include "ResourcesMgr.h"
#include "Phase1.h"
#include "ObjMgr.h"
#include "MapPattern.h"
#include "SceneMgr.h"
#include "Player.h"
#include "SoundMgr.h"

CMonitorBreak::CMonitorBreak() : m_bCheck(false)
{
}

CMonitorBreak::~CMonitorBreak()
{
}

void CMonitorBreak::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/MONITORBREAK/MONITORBREAK.bmp", L"MONITORBREAK");
	m_eRenderGroup = RENDER_SORT::EFFECT;
	m_tInfo.iCX = 1366;
	m_tInfo.iCY = 768;
	m_pFrameKey = L"MONITORBREAK";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 35;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
	CSoundMgr::Get_Instance()->PlaySound(L"MonitorBreak.wav", CSoundMgr::MONITORBREAK);
}

void CMonitorBreak::Late_Init()
{

}

int CMonitorBreak::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONITORBREAK);
		return OBJ_DEAD;
	}

	Late_Init();


	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonitorBreak::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}

	if (m_tFrame.iStartX >= m_tFrame.iEndX - 14)
	{	
		if (!m_bDead)
		{
			if (static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Shiled_TriggerEnter())
			{
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledTriggerExit(false);
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_DeleteBlockHP(true);
				static_cast<CObj*>(CObjMgr::Get_Instance()->Get_BlockHPbar())->Set_Dead();
				static_cast<CObj*>(CObjMgr::Get_Instance()->Get_BlockServeHPbar())->Set_Dead();
				if (!m_bCheck)
				{
					static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->MonitorBreakDmg();
					static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_GroggyState(true);
					m_bCheck = true;
				}
			}
			else if (!static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Shiled_TriggerEnter())
			{
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Init_HP();
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledTriggerExit(true);
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_DeleteBlockHP(false);
				static_cast<CMapPattern*>(CObjMgr::Get_Instance()->Get_MapPattern())->Set_SpawnBeholderEye(false);
				static_cast<CMapPattern*>(CObjMgr::Get_Instance()->Get_MapPattern())->Set_SpawnMonitorBreak(false);
				if (!m_bCheck)
				{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(
						static_cast<CObj*>(CObjMgr::Get_Instance()->Get_Player())->Get_Stat().fMaxHp);
					m_bCheck = true;
				}
			}		
		}
	}
}


void CMonitorBreak::Render(HDC _DC)
{
	Update_Rect();
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CMonitorBreak::Release()
{
}
