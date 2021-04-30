#include "framework.h" 
#include "Phase1.h"
#include "BossStage1.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "LockHP.h"
#include "ObjMgr.h"
#include "SKILLBALL.h"
#include "Collision.h"

CPhase1::CPhase1() : m_ePreState(END), m_eCurState(END), m_fBlueHP(0.f), m_fMaxBlueHP(0.f), m_fPurpleHP(0.f), m_fMaxPurpleHP(0.f)
, m_bAnimisPlaying(false), m_fDelay(0.f), m_bCheck_LeftRight(false), m_bBlock_BlueHP(false), m_bBlock_PurpleHP(false)
, m_bDeleteBlockHP(false), m_bShiledSpawnCheck(false), m_bShiled_TriggerEnter(false), m_bShiled_TriggerExit(false)
, m_bChangeState(false), m_iPatternNum(0), m_fSaveTargetX(0.f), m_bGroggyState(false), m_bCreateCol(false)
{
}

CPhase1::~CPhase1()
{
	Release();
}

void CPhase1::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/IDLE/IDLE.bmp", L"PHASE1_IDLE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/WALK/WALK.bmp", L"PHASE1_WALK");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/Attack1/Attack1.bmp", L"PHASE1_Attack1");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/Attack2/Attack2.bmp", L"PHASE1_PUSH");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/BALL_START/BALL_START.bmp", L"PHASE1_BALL_START");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/Teleport_Start/Teleport_Start.bmp", L"PHASE1_Teleport_Start");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/Teleport_End/Teleport_End.bmp", L"PHASE1_Teleport_End");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/Groggy/GROGGY.bmp", L"PHASE1_Groggy");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/DEAD/DEAD.bmp", L"PHASE1_DEAD");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/PHASE1_STRETCH.bmp", L"PHASE1_STRETCH");

	m_tInfo.iCX = 1000;
	m_tInfo.iCY = 500;
	m_tInfo.iColX = 90;
	m_tInfo.iColY = 200;
	m_fSpeed = 1.f;

	m_fMaxBlueHP = 5000000;
	m_fBlueHP = m_fMaxBlueHP;
	m_fMaxPurpleHP = 5000000;
	m_fPurpleHP = m_fMaxPurpleHP;

	m_tStat.fMaxHp = m_fMaxBlueHP + m_fMaxPurpleHP;
	m_tStat.fHp = m_tStat.fMaxHp;
	m_eCurState = IDLE;
	m_pFrameKey = L"PHASE1_IDLE";
	m_pStretch = L"PHASE1_STRETCH";
	m_eRenderGroup = RENDER_SORT::OBJECT;

}

void CPhase1::Late_Init()
{
}

int CPhase1::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	Late_Init();
	

	Change_State();
	Phase1_Pattern();
	Check_LeftRight();
	Update_Block_HP();
	Update_Frame();
	Update_CollisionRect();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase1::Late_Update()
{
	if (m_bGroggyState)
	{
		Set_State(GROGGY);
		m_fDelay = 0.f;
		m_bGroggyState = false;
	}
	if (0.f >= m_tStat.fHp)
	{
		Set_State(DEAD);
		m_pFrameKey = L"PHASE1_DEAD";
		if (m_eCurState == DEAD)
		{
			if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
			{
				CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::PHASE2_VIDEO);
			}

		}
	}

}

void CPhase1::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();

	//Rectangle(_DC, m_tCollisionRect.left, m_tCollisionRect.top, m_tCollisionRect.right, m_tCollisionRect.bottom);

	if (m_bCheck_LeftRight)
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left, m_tRect.top);
		m_bRight = true;
	}
	else if (!m_bCheck_LeftRight)
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left, m_tRect.top);
		m_bRight = false;
	}
}

void CPhase1::Release()
{
}

void CPhase1::Take_Damage(int _Damage)
{
	bool bSceneCheck = dynamic_cast<CBossStage1*>(CSceneMgr::Get_Instance()->Get_CurrentScene())->Get_bChangeMap();

	if (!bSceneCheck)
	{
		if (m_bBlock_BlueHP)
			return;

		m_fBlueHP -= _Damage;
	}
	else if (bSceneCheck)
	{
		if (m_bBlock_PurpleHP)
			return;

		m_fPurpleHP -= _Damage;
	}

	if (m_fBlueHP <= 0 && m_fPurpleHP <= 0)
	{
		m_tStat.fHp -= _Damage;
	}
}

void CPhase1::Init_HP()
{
	m_fBlueHP = m_fMaxBlueHP;
	m_fPurpleHP = m_fMaxPurpleHP;
}

void CPhase1::MonitorBreakDmg()
{
	m_tStat.fHp = (int)m_tStat.fHp >> 1;
}

void CPhase1::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPhase1::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 150;
			break;
		case CPhase1::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 150;
			break;
		case CPhase1::ATTACK1:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase1::PUSHATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase1::BALL_SKILL:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase1::TELEPORT_START:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 9;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase1::TELEPORT_END:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase1::GROGGY:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase1::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 7;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPhase1::WALK_STATE()
{
	m_eCurState = WALK;
	m_pFrameKey = L"PHASE1_WALK";

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	m_fSpeed = 1.f;

	m_fRotation = acosf(fX / fDist);

	if (m_tInfo.fX < m_pTarget->Get_Info().fX)
		m_fRotation *= -1.f;

	m_tInfo.fX += cosf(m_fRotation) * m_fSpeed;
	m_iPatternNum = (rand() % 2) + 1;

	if (fDist <= 200.f)
	{
		switch (m_iPatternNum)
		{
		case 1:
			Set_State(ATTACK1);
			break;
		case 2:
			Set_State(PUSHATTACK);
			break;
		}
	}
	else if (fDist >= 600.f)
	{
		m_iPatternNum += 2;

		switch (m_iPatternNum)
		{
		case 3:
			Set_State(BALL_SKILL);
			break;
		case 4:
			Set_State(TELEPORT_START);
			break;
		}
	}
}

void CPhase1::Phase1_Pattern()
{
	switch (m_eCurState)
	{
	case CPhase1::IDLE:
		IDLE_STATE();
		break;
	case CPhase1::WALK:
		WALK_STATE();
		break;
	case CPhase1::ATTACK1:
		ATTACK_STATE();
		break;
	case CPhase1::PUSHATTACK:
		ATTACK_PUSH_STATE();
		break;
	case CPhase1::BALL_SKILL:
		SKILL_BALL_STATE();
		break;
	case CPhase1::TELEPORT_START:
		SKILL_TELEPORT_START();
		break;
	case CPhase1::TELEPORT_END:
		SKILL_TELEPORT_END();
		break;
	case CPhase1::GROGGY:
		GROGGY_STATE();
		break;
	}
}

void CPhase1::Check_LeftRight()
{
	if (!m_bAnimisPlaying)
	{
		if (m_pTarget->Get_Info().fX < m_tInfo.fX)
		{
			m_bCheck_LeftRight = false;
		}
		else if (m_pTarget->Get_Info().fX > m_tInfo.fX)
		{
			m_bCheck_LeftRight = true;
		}
	}
}

void CPhase1::Update_Block_HP()
{
	if (m_bDeleteBlockHP)
	{
		m_bBlock_BlueHP = false;
		m_bBlock_PurpleHP = false;
		return;
	}

	if ((int)m_fBlueHP <= (int)m_fMaxBlueHP >> 1)
	{
		m_bBlock_BlueHP = true;
		m_fBlueHP = (int)m_fMaxBlueHP >> 1;
	}
	else
	{
		m_bBlock_BlueHP = false;
	}
	if ((int)m_fPurpleHP <= (int)m_fMaxPurpleHP >> 1)
	{
		m_bBlock_PurpleHP = true;
		m_fPurpleHP = (int)m_fMaxPurpleHP >> 1;
	}
	else
	{
		m_bBlock_PurpleHP = false;
	}
}

void CPhase1::ATTACK_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE1_Attack1";

	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX + 2 >> 1)
	{
		if (!m_bCreateCol)
		{
			if (!m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX - 100, m_tInfo.fY, 300, 100);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_ATTACK, pObJ);
				m_bCreateCol = true;
			}
			else if (m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 100, m_tInfo.fY, 300, 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_ATTACK, pObJ);
				m_bCreateCol = true;
			}
		}
		else if (m_bCreateCol)
		{
			CObjMgr::Get_Instance()->DeleteID(OBJID::WILL_ATTACK);
		}
	}
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE1_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;

	}
}

void CPhase1::ATTACK_PUSH_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE1_PUSH";
	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX + 2 >> 1)
	{
		if (!m_bCreateCol)
		{
			if (!m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX - 100, m_tInfo.fY, 400, 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_PUSH, pObJ);
				m_bCreateCol = true;
			}
			else if (m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 100, m_tInfo.fY, 400, 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_PUSH, pObJ);
				m_bCreateCol = true;
			}
		}
		else if (m_bCreateCol)
		{
			CObjMgr::Get_Instance()->DeleteID(OBJID::WILL_PUSH);
		}
	}
	
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bAnimisPlaying = false;

		Set_State(IDLE);
		m_pFrameKey = L"PHASE1_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}

}

void CPhase1::SKILL_BALL_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE1_BALL_START";
	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 4)
	{
		CObj* pObj = CAbstractFactory<CSKILLBALL>::Create(m_tInfo.fX, m_tInfo.fY - 150);
		CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_BALL, pObj);
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE1_IDLE";
		m_fDelay = 0.f;
	}

}

void CPhase1::SKILL_TELEPORT_START()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE1_Teleport_Start";
	m_bAnimisPlaying = true;

	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		Set_State(TELEPORT_END);
		m_fSaveTargetX = m_pTarget->Get_Info().fX;
	}
}

void CPhase1::SKILL_TELEPORT_END()
{
	m_pFrameKey = L"PHASE1_Teleport_End";
	m_tInfo.fX = m_fSaveTargetX;
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE1_IDLE";
		m_fDelay = 0.f;
	}
}

void CPhase1::IDLE_STATE()
{
	m_fSpeed = 0.f;
	m_fDelay += 1.f;
	if (m_fDelay >= 100.f)
	{
		Set_State(WALK);
	}
}

void CPhase1::GROGGY_STATE()
{
	m_pFrameKey = L"PHASE1_Groggy";
	m_fSpeed = 0.f;
	m_fDelay += 1.f;

	if (m_fDelay >= 1000.f)
	{
		Set_State(IDLE);
		m_pFrameKey = L"PHASE1_IDLE";
		m_fDelay = 0.f;
	}
}


