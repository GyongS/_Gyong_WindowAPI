#include "framework.h"
#include "Phase2.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Phase2Ball.h"
#include "Phase2_WALL.h"
#include "Collision.h"

CPhase2::CPhase2() : m_eCurState(END), m_ePreState(END), m_fDelay(0.f), m_bAnimisPlaying(false), m_bCheck_LeftRight(false), m_iPatternNum(0), m_WallCnt(0)
, m_bCreateCol(false)
{
}

CPhase2::~CPhase2()
{
}

void CPhase2::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/IDLE.bmp", L"PHASE2_IDLE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/WALK.bmp", L"PHASE2_WALK");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/DEFAULT_ATTACK1.bmp", L"PHASE2_DEFAULT_ATTACK1");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/ATTACK_PUSH.bmp", L"PHASE2_ATTACK_PUSH");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/ATTACK_FAKE.bmp", L"PHASE2_ATTACK_FAKE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/DEFAULT_ATTACK2.bmp", L"PHASE2_DEFAULT_ATTACK2");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/SKILL_WALL.bmp", L"PHASE2_SKILL_WALL");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/SKILL_BALL/SKILL_BALL_START.bmp", L"PHASE2_SKILL_BALL_START");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/DEAD.bmp", L"PHASE2_DEAD");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/STRETCH.bmp", L"PHASE2_STRETCH");

	m_tInfo.iCX = 1000;
	m_tInfo.iCY = 600;
	m_tInfo.iColX = 80;
	m_tInfo.iColY = 200;
	m_fSpeed = 1.f;

	m_tStat.fMaxHp = 1000000.f;
	m_tStat.fHp = m_tStat.fMaxHp;
	m_eCurState = IDLE;
	m_pFrameKey = L"PHASE2_IDLE";
	m_pStretch = L"PHASE2_STRETCH";
	m_eRenderGroup = RENDER_SORT::OBJECT;

}

int CPhase2::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Change_State();
	Phase2_Pattern();
	Check_LeftRight();
	if (m_eCurState == DEAD)
	{
		Update_FrameLoopEnd();
	}
	else
	{
		Update_Frame();
	}
	Update_CollisionRect();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase2::Late_Update()
{
	if (0.f >= m_tStat.fHp)
	{
		Set_State(DEAD);
		m_pFrameKey = L"PHASE2_DEAD";
		if (m_eCurState == DEAD)
		{
			if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
			{
				CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::PHASE3_VIDEO);
			}

		}
	}
}

void CPhase2::Render(HDC _DC)
{
	Update_CollisionRect();
	Update_Rect();

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

void CPhase2::Release()
{
}

void CPhase2::Take_Damage(int _Damage)
{
	m_tStat.fHp -= _Damage;
}

void CPhase2::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPhase2::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::DEFAULT_ATTACK1:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::ATTACK_PUSH:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::ATTACK_FAKE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 30;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::DEFAULT_ATTACK2:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::SKILL_BALL:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::SKILL_WALL:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPhase2::Check_LeftRight()
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

void CPhase2::Phase2_Pattern()
{
	switch (m_eCurState)
	{
	case CPhase2::IDLE:
		IDLE_STATE();
		break;
	case CPhase2::WALK:
		WALK_STATE();
		break;
	case CPhase2::DEFAULT_ATTACK1:
		DEFAULT_ATTACK1_STATE();
		break;
	case CPhase2::DEFAULT_ATTACK2:
		DEFAULT_ATTACK2_STATE();
		break;
	case CPhase2::ATTACK_PUSH:
		ATTACK_PUSH_STATE();
		break;
	case CPhase2::ATTACK_FAKE:
		ATTACK_FAKE_STATE();
		break;
	case CPhase2::SKILL_BALL:
		SKILL_BALL_STATE();
		break;
	case CPhase2::SKILL_WALL:
		if (m_WallCnt <= 0)
		{
			SKILL_WALL_STATE();
		}
		else
		{
			SKILL_BALL_STATE();
		}
		break;
	}
}

void CPhase2::IDLE_STATE()
{
	m_fSpeed = 0.f;
	m_fDelay += 1.f;
	if (m_fDelay >= 100.f)
	{
		Set_State(WALK);
	}
}

void CPhase2::WALK_STATE()
{
	m_pFrameKey = L"PHASE2_WALK";

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	m_fSpeed = 1.f;

	m_fRotation = acosf(fX / fDist);

	if (m_tInfo.fX < m_pTarget->Get_Info().fX)
		m_fRotation *= -1.f;

	m_tInfo.fX += cosf(m_fRotation) * m_fSpeed;
	m_iPatternNum = (rand() % 4) + 1;

	if (fDist <= 200.f)
	{
		switch (m_iPatternNum)
		{
		case 1:
			Set_State(DEFAULT_ATTACK1);
			break;
		case 2:
			Set_State(ATTACK_PUSH);
			break;
		case 3:
			Set_State(ATTACK_FAKE);
			break;
		case 4:
			Set_State(DEFAULT_ATTACK2);
			break;
		}
	}
	else if (fDist >= 600.f)
	{
		m_iPatternNum += 2;

		switch (m_iPatternNum)
		{
		case 5:
			Set_State(SKILL_BALL);
			break;
		case 6:
			Set_State(SKILL_WALL);
			break;
		}
	}
}

void CPhase2::DEFAULT_ATTACK1_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE2_DEFAULT_ATTACK1";

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
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 100, m_tInfo.fY, 300, 100);
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
		m_pFrameKey = L"PHASE2_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase2::DEFAULT_ATTACK2_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE2_DEFAULT_ATTACK2";

	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX + 2 >> 1)
	{
		if (!m_bCreateCol)
		{
			if (!m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX - 200, m_tInfo.fY, 400, 100);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_ATTACK, pObJ);
				m_bCreateCol = true;
			}
			else if (m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 200, m_tInfo.fY, 400, 100);
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
		m_pFrameKey = L"PHASE2_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase2::ATTACK_PUSH_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE2_ATTACK_PUSH";
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
		m_pFrameKey = L"PHASE2_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase2::ATTACK_FAKE_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE2_ATTACK_FAKE";
	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX + 2 >> 1)
	{
		if (!m_bCreateCol)
		{
			if (!m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX - 200, m_tInfo.fY, 300, 100);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_ATTACK, pObJ);
				m_bCreateCol = true;
			}
			else if (m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 200, m_tInfo.fY, 300, 100);
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
		m_pFrameKey = L"PHASE2_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase2::SKILL_BALL_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE2_SKILL_BALL_START";
	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		CObj* pObj = CAbstractFactory<CPhase2Ball>::Create(m_tInfo.fX, m_tInfo.fY + 150);
		CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_BALL, pObj);
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE2_IDLE";
		m_fDelay = 0.f;
	}
}

void CPhase2::SKILL_WALL_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE2_SKILL_WALL";
	m_bAnimisPlaying = true;
	float fX = 0.f;
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		for (int i = 0; i < 2; ++i)
		{
			CObj* pObj = CAbstractFactory<CPhase2_WALL>::Create(50 + fX, m_tInfo.fY + 200);
			CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_WALL, pObj);
			fX += 1250.f;
			m_WallCnt++;
		}
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE2_IDLE";
		m_fDelay = 0.f;
	}
}
