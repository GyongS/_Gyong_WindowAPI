#include "framework.h"
#include "Phase3.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "WhiteEyePattern.h"
#include "RedEyePattern.h"
#include "Collision.h"
#include "SoundMgr.h"
CPhase3::CPhase3() : m_ePreState(END), m_eCurState(END), m_iPatternNum(0), m_fDelay(0.f)
, m_bAnimisPlaying(false), m_bCheck_LeftRight(false), m_fSaveTargetPosX(0.f), m_bCheck_PatternLeg(false)
, m_fSpawnPosX(0.f), m_bCreateCol(false)
{
}

CPhase3::~CPhase3()
{
}

void CPhase3::Init()
{	

	m_tInfo.iCX = 1200;
	m_tInfo.iCY = 1000;
	m_tInfo.iColX = 80;
	m_tInfo.iColY = 600;
	m_fSpeed = 1.f;

	m_tStat.fMaxHp = 1000000;
	m_tStat.fHp = m_tStat.fMaxHp;
	m_eCurState = IDLE;
	m_pFrameKey = L"PHASE3_IDLE";
	m_pStretch = L"PHASE3_STRETCH";
	m_eRenderGroup = RENDER_SORT::OBJECT;
}

int CPhase3::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (0.f >= m_tStat.fHp)
	{
		Set_State(DEAD);
		m_pFrameKey = L"PHASE3_DEAD";
		if (m_eCurState == DEAD)
		{
			if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
			{
				m_tFrame.iStartX = m_tFrame.iEndX;
				return OBJ_DEAD;
			}

		}
	}
	Change_State();
	Phase3_Pattern();
	Check_LeftRight();
	Update_Frame();
	Update_CollisionRect();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPhase3::Late_Update()
{

}

void CPhase3::Render(HDC _DC)
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

void CPhase3::Release()
{
}

void CPhase3::Take_Damage(int _Damage)
{
	m_tStat.fHp -= _Damage;
}


void CPhase3::Phase3_Pattern()
{
	switch (m_eCurState)
	{
	case CPhase3::IDLE:
		IDLE_STATE();
		break;
	case CPhase3::DEFAULT_ATTACK1:
		DEFAULT_ATTACK1_STATE();
		break;
	case CPhase3::DEFAULT_ATTACK2:
		DEFAULT_ATTACK2_STATE();
		break;
	case CPhase3::ATTACK_PUSH:
		ATTACK_PUSH_STATE();
		break;
	case CPhase3::WHITE_EYE:
		WHITE_EYE_STATE();
		break;
	case CPhase3::RED_EYE:
		RED_EYE_STATE();
		break;
	}
}

void CPhase3::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPhase3::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase3::DEFAULT_ATTACK1:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 25;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase3::DEFAULT_ATTACK2:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 25;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase3::ATTACK_PUSH:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 25;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase3::WHITE_EYE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 25;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase3::RED_EYE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 25;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase3::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 25;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPhase3::Check_LeftRight()
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

void CPhase3::IDLE_STATE()
{
	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fX * fX + fY * fY);
	m_fSpeed = 0.f;
	m_fDelay += 1.f;
	m_iPatternNum = (rand() % 3) + 1;
	m_fSaveTargetPosX = m_pTarget->Get_Info().fX;
	if (m_fDelay >= 100.f)
	{
		if (fDist <= 200.f)
		{
			switch (m_iPatternNum)
			{
			case 1:
				Set_State(DEFAULT_ATTACK1);
				break;
			case 2:
				Set_State(DEFAULT_ATTACK2);
				break;
			case 3:
				Set_State(ATTACK_PUSH);
				break;
			}
		}
		else if (fDist <= 300.f)
		{
			switch (m_iPatternNum)
			{
			case 1:
			case 2:
				Set_State(DEFAULT_ATTACK2);
				break;
			case 3:
				Set_State(ATTACK_PUSH);
				break;
			}
		}
		else if (fDist > 300.f)
		{
			m_iPatternNum += 2;

			switch (m_iPatternNum)
			{
			case 4:
				Set_State(WHITE_EYE);
				break;
			case 5:
				Set_State(RED_EYE);
				break;
			}
		}
	}
}

void CPhase3::DEFAULT_ATTACK1_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE3_DEFAULT_ATTACK1";

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
		m_pFrameKey = L"PHASE3_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase3::DEFAULT_ATTACK2_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE3_DEFAULT_ATTACK2";

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
		m_pFrameKey = L"PHASE3_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase3::ATTACK_PUSH_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE3_ATTACK_PUSH";
	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX + 2 >> 1)
	{
		if (!m_bCreateCol)
		{
			if (!m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX - 100, m_tInfo.fY, 500, 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::WILL_PUSH, pObJ);
				m_bCreateCol = true;
			}
			else if (m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 100, m_tInfo.fY, 500, 200);
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
		m_pFrameKey = L"PHASE3_IDLE";
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}

void CPhase3::WHITE_EYE_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE3_WhiteEye";
	m_bAnimisPlaying = true;

	if (m_tFrame.iStartX >= m_tFrame.iEndX - 10 && !m_bCheck_PatternLeg)
	{
		CObj* pObj = CAbstractFactory<CWhiteEyePattern>::Create(m_fSaveTargetPosX, m_tInfo.fY + 100);
		CObjMgr::Get_Instance()->Add_Object(OBJID::WHITE_LEG, pObj);
		m_bCheck_PatternLeg = true;
	}
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{		
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE3_IDLE";
		m_fDelay = 0.f;
		m_bCheck_PatternLeg = false;
	}
}

void CPhase3::RED_EYE_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"PHASE3_RedEye";
	m_bAnimisPlaying = true;

	if (m_tFrame.iStartX >= m_tFrame.iEndX - 10 && !m_bCheck_PatternLeg)
	{
		// 여기서 플레이어 위치빼고 나머지에 거미다리 소환
		for (int i = 0; i < 8; ++i)
		{
			CObj* pObj = CAbstractFactory<CRedEyePattern>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + (m_fSpawnPosX + 250), m_tInfo.fY - 100);
			CObjMgr::Get_Instance()->Add_Object(OBJID::RED_LEG, pObj);
			pObj = CAbstractFactory<CRedEyePattern>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - (m_fSpawnPosX + 250), m_tInfo.fY - 100);
			CObjMgr::Get_Instance()->Add_Object(OBJID::RED_LEG, pObj);
			m_fSpawnPosX += 100;			
		}
		m_fSpawnPosX = 0.f;
		m_bCheck_PatternLeg = true;
	}
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{	
		m_bAnimisPlaying = false;
		Set_State(IDLE);
		m_pFrameKey = L"PHASE3_IDLE";
		m_fDelay = 0.f;
		m_bCheck_PatternLeg = false;
	}
}
