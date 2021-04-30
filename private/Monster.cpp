#include "framework.h"
#include "Monster.h"
#include "ResourcesMgr.h"
#include "ScrollMgr.h"
#include "MonsterHPbar.h"
#include "MonsterHPBG.h"
#include "ObjMgr.h"
#include "Potion.h"
#include "Collision.h"
#include "SoundMgr.h"

CMonster::CMonster(): m_eCurState(END), m_ePreState(END), m_fDelay(0.f), m_bAnimisPlaying(false)
, m_bCheck_LeftRight(false), m_bHitCheck(false), m_iDir(0), m_bCreateCol(false)
{
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/IDLE_LEFT.bmp", L"MONSTER_IDLE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/WALK_LEFT.bmp", L"MONSTER_WALK");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/ATTACK_LEFT.bmp", L"MONSTER_ATTACK");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/DEAD_LFET.bmp", L"MONSTER_DEAD");

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/IDLE_RIGHT.bmp", L"MONSTER_IDLE_RIGHT");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/WALK_RIGHT.bmp", L"MONSTER_WALK_RIGHT");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/ATTACK_RIGHT.bmp", L"MONSTER_ATTACK_RIGHT");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Monster/Monster/DEAD_RIGHT.bmp", L"MONSTER_DEAD_RIGHT");

	CObj* pObj = CAbstractFactory<CMonsterHPbar>::Create();
	pObj->Set_Target(this);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_HP, pObj);

	pObj = CAbstractFactory<CMonsterHPBG>::Create();
	pObj->Set_Target(this);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_HP, pObj);

	m_tInfo.iCX    = 700;
	m_tInfo.iCY    = 400;
	m_tInfo.iColX  = 200;
	m_tInfo.iColY  = 300;
	m_tStat.fMaxHp = 500000.f;
	m_tStat.fHp    = m_tStat.fMaxHp;
	m_fSpeed       = 2.f;
	m_eCurState    = IDLE;
	m_pFrameKey    = L"MONSTER_IDLE";
	m_pFrameKey_Right = L"MONSTER_IDLE_RIGHT";
	m_eRenderGroup = RENDER_SORT::OBJECT;


}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	Change_State();
	Monster_Pattern();
	Check_LeftRight();
	Update_Frame();
	Update_CollisionRect();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (0.f >= m_tStat.fHp)
	{
		Set_State(DEAD);
		if (m_bCheck_LeftRight)
		{
			m_pFrameKey_Right = L"MONSTER_DEAD_RIGHT";
		}
		else if (!m_bCheck_LeftRight)
		{
			m_pFrameKey = L"MONSTER_DEAD";
		}

		if (m_eCurState == DEAD)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_Dead.mp3", CSoundMgr::MONSTER_DEAD);
			if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
			{
				CObj* pObj = CAbstractFactory<CPotion>::Create(m_tInfo.fX, m_tInfo.fY);
				pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				CObjMgr::Get_Instance()->Add_Object(OBJID::ITEM, pObj);
				m_bDead = true;
			}
		}
	}
}

void CMonster::Render(HDC _DC)
{
	Update_CollisionRect();
	Update_Rect();
	
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bCheck_LeftRight)
	{
		Anim_TransparentBlt(_DC, m_pFrameKey_Right, m_tRect.left + iScrollX, m_tRect.top+ iScrollY);
		m_bRight = true;
	}
	else if (!m_bCheck_LeftRight)
	{
		Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left + iScrollX, m_tRect.top + iScrollY);
		m_bRight = false;
	}
}

void CMonster::Release()
{
}

void CMonster::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CMonster::IDLE:
			m_tFrame.iStartX    = 0;
			m_tFrame.iEndX      = 8;
			m_tFrame.iScene     = 0;
			m_tFrame.dwTime     = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CMonster::WALK:
			m_tFrame.iStartX    = 0;
			m_tFrame.iEndX      = 8;
			m_tFrame.iScene     = 0;
			m_tFrame.dwTime     = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CMonster::ATTACK:
			m_tFrame.iStartX    = 0;
			m_tFrame.iEndX      = 18;
			m_tFrame.iScene     = 0;
			m_tFrame.dwTime     = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CMonster::DEAD:
			m_tFrame.iStartX    = 0;
			m_tFrame.iEndX      = 17;
			m_tFrame.iScene     = 0;
			m_tFrame.dwTime     = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMonster::Check_LeftRight()
{
	if (!m_bAnimisPlaying && m_bHitCheck)
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

void CMonster::Monster_Pattern()
{
	switch (m_eCurState)
	{
	case CMonster::IDLE:
		IDLE_STATE();
		break;
	case CMonster::WALK:
		WALK_STATE();
		break;
	case CMonster::ATTACK:
		ATTACK_STATE();
		break;
	}
}

void CMonster::IDLE_STATE()
{
	m_fDelay += 1.f;
	m_iDir = (rand() % 2) + 1;

	if (m_bHitCheck)
	{	
		Set_State(WALK);
	}
	else if(m_fDelay >= 100.f && !m_bHitCheck)
	{
		switch (m_iDir)
		{
		case 1:
			m_fDelay = 0.f;
			m_bCheck_LeftRight = true;
			break;
		case 2:
			m_fDelay = 0.f;
			m_bCheck_LeftRight = false;
			break;
		}
		Set_State(WALK);
	}
}

void CMonster::WALK_STATE()
{
	if (!m_bCheck_LeftRight)
	{
		m_pFrameKey = L"MONSTER_WALK";
	}
	else if(m_bCheck_LeftRight)
	{
		m_pFrameKey_Right = L"MONSTER_WALK_RIGHT";
	}
	m_fDelay += 1.f;
	m_fSpeed = 3.f;

	if (m_bHitCheck)
	{
		float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDist = sqrtf(fX * fX + fY * fY);
		m_fSpeed = 2.f;

		m_fRotation = acosf(fX / fDist);

		if (m_tInfo.fX < m_pTarget->Get_Info().fX)
			m_fRotation *= -1.f;

		m_tInfo.fX += cosf(m_fRotation) * m_fSpeed;

		if (fDist <= 200.f && m_tInfo.fY <= m_pTarget->Get_Info().fY)
		{
			Set_State(ATTACK);
		}
		else if (fDist >= 800.f)
		{
			m_bHitCheck = false;
		}
	}
	else
	{
		if (m_fDelay >= 150.f)
		{
			Set_State(IDLE);
			m_pFrameKey = L"MONSTER_IDLE";
			m_pFrameKey_Right = L"MONSTER_IDLE_RIGHT";

			m_fDelay = 0.f;
			m_fSpeed = 0.f;
		}
		if (m_tInfo.fX <= 0)
		{
			m_tInfo.fX = 0;
		}
		else if (m_tInfo.fX >= MONSTERMAP_CX)
		{
			m_tInfo.fX = MONSTERMAP_CX;
		}

		if (m_iDir == 1)
			m_tInfo.fX += m_fSpeed;
		else
			m_tInfo.fX -= m_fSpeed;
	}

}

void CMonster::ATTACK_STATE()
{
	m_fSpeed = 0.f;
	m_pFrameKey = L"MONSTER_ATTACK";
	m_pFrameKey_Right = L"MONSTER_ATTACK_RIGHT";
	CSoundMgr::Get_Instance()->PlaySound(L"Monster_Attack1.mp3", CSoundMgr::MONSTER_ATTACK);

	m_bAnimisPlaying = true;
	if (m_tFrame.iStartX >= m_tFrame.iEndX + 2 >> 1)
	{
		if (!m_bCreateCol)
		{
			if (!m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX - 100, m_tInfo.fY, 300, 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_ATTACK, pObJ);
				m_bCreateCol = true;
			}
			else if (m_bCheck_LeftRight)
			{
				CObj* pObJ = CAbstractFactory<CCollision>::CreateCollision(m_tInfo.fX + 100, m_tInfo.fY, 300, 200);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_ATTACK, pObJ);
				m_bCreateCol = true;
			}
		}
		else if (m_bCreateCol)
		{
			CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER_ATTACK);
		}
	}
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bAnimisPlaying = false;
		if (!m_bCheck_LeftRight)
		{
			Set_State(IDLE);
			m_pFrameKey = L"MONSTER_IDLE";
		}
		else if (m_bCheck_LeftRight)
		{
			Set_State(IDLE);
			m_pFrameKey_Right = L"MONSTER_IDLE_RIGHT";
		}
		m_fDelay = 0.f;
		m_bCreateCol = false;
	}
}
