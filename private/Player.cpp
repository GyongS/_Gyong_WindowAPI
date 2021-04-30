#include "framework.h" 
#include "Player.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "ResourcesMgr.h"
#include "ScrollMgr.h"
#include "Allow.h"
#include "AllowShotEffect.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "MonsterMapFloor.h"
#include "CollisionMgr.h"
#include "PlayerDeadUI.h"
#include "SoundMgr.h"
#include "DamageSkin.h"
#include "HowlingGailUsed.h"
#include "BUFFSKILL.h"
#include "SharpEyes.h"
#include "StatUI.h"

CPlayer::CPlayer() : m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f), m_fDelay(0.f)
, m_iJumpCnt(0), m_iPotionCnt(0), m_bPickupPotion(false), m_bGround(false), m_bMapLegHitCheck(false),m_bCurDead(false), m_bChangeDmgSkin(false)
,m_fSkillDelay(0.f), m_bSkillHitCheck(false), m_iSkillCnt(0), m_UsedMapleWarrior(false), m_UsedSharpEyes(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/IDLE/IDLE.bmp", L"PLAYER_IDLE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/JUMP/JUMP.bmp", L"PLAYER_JUMP");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ATTACK.bmp", L"PLAYER_ATTACK");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/WALK/WALK.bmp", L"PLAYER_WALK");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/DEAD/DEAD.bmp", L"PLAYER_DEAD");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/PLAYER_STRETCH.bmp", L"PLAYER_STRETCH");
	
	m_tInfo.iCX    = 100;
	m_tInfo.iCY    = 100;
	m_tInfo.iColX  =  40;
	m_tInfo.iColY  =  50;
	m_tStat.fMaxHp = 100.f;
	m_tStat.fHp    = m_tStat.fMaxHp;
	m_tStat.fMaxMp = 100.f;
	m_tStat.fMp    = m_tStat.fMaxMp;
	m_tStat.iAttack = 1500;
	m_fSpeed       = 5.f;
	m_fJumpPower   = 50.f;
	m_pFrameKey    = L"PLAYER_IDLE";
	m_pStretch     =  L"PLAYER_STRETCH";
	m_eRenderGroup = RENDER_SORT::OBJECT;
}

void CPlayer::Late_Init()
{
}

int CPlayer::Update()
{		
	CObj::Late_Init();		

	if (!m_bChangeDmgSkin)
	{
		int iDamage = rand() % m_tStat.iAttack * 50;
		m_tStat.iDamage = iDamage;
		m_bChangeDmgSkin = true;
	}

	m_fSkillDelay += 0.7f;
	if (m_fSkillDelay >= 10)
	{
		m_bSkillHitCheck = true;
		m_fSkillDelay = 0.f;
	}

	Key_Check();
	Jumping();
	OffSet();
	Change_State();
	Stop_Move();
	Update_Frame();
	Update_Rect();
	Update_CollisionRect();
	return OBJ_NOEVENT;
}


void CPlayer::Late_Update()
{
	if (0.f >= m_tStat.fHp)
	{
		m_bDead = true;
		m_eCurState = DEAD;
		m_pFrameKey = L"PLAYER_DEAD";
		if (!m_bCurDead)
		{
			CObj* pObj = CAbstractFactory<CPlayerDeadUI>::Create(WINCX >> 1, 250);
			CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);
			CSoundMgr::Get_Instance()->PlaySound(L"Tombstone.mp3", CSoundMgr::DEAD);
			m_bCurDead = true;
		}
	}
}

void CPlayer::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bRight)
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left + iScrollX, m_tRect.top + iScrollY);
	}
	else
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left + iScrollX, m_tRect.top + iScrollY);
	}
}

void CPlayer::Release()
{

}

void CPlayer::Jumping()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{
		float fY = 0.f;		
		RECT rcTemp = {};
		if (m_bJump)
		{
			m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f);
			m_fJumpTime += 0.25f;
			m_iJumpCnt = 0;
		}	
		else if (!m_bGround)
		{			
			m_tInfo.fY = 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
			m_fJumpTime += 0.25f;
		}
	}
	
	else
	{
		float fY = 0.f;
		bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
		
		if (m_bJump)
		{
			m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f);
			m_fJumpTime += 0.25f;

			if (bLineCol && fY < m_tInfo.fY)
			{
				m_bJump = false;
				m_tInfo.fY = fY;
				m_fJumpTime = 0.f;
			}
		}
		else if (bLineCol)
		{
			m_tInfo.fY = fY;
		}
	}
}

void CPlayer::DoubleJump()
{
	m_tInfo.fY += m_fJumpY - (m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f);
	m_fJumpTime += 0.25f;
}

void CPlayer::OffSet()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	int	iOffSetX = WINCX   >> 1;
	int	iOffSetY = WINCY   >> 1;

	if (iOffSetX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetX - (m_tInfo.fX + iScrollX));
	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetX - (m_tInfo.fX + iScrollX));

	if (iOffSetY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetY - (m_tInfo.fY + iScrollY));
	if (iOffSetY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetY - (m_tInfo.fY + iScrollY));
	
}

void CPlayer::Stop_Move()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{
		if (m_tInfo.fX > MONSTERMAP_CX - 40)
		{
			m_tInfo.fX = MONSTERMAP_CX - 40;
		}
		if (m_tInfo.fX < 10)
		{
			m_tInfo.fX = 10;
		}
	}
	else
	{
		if (m_tInfo.fX > WINCX - 40)
		{
			m_tInfo.fX = WINCX - 40;
		}
		if (m_tInfo.fX < 10)
		{
			m_tInfo.fX = 10;
		}
	}

}

void CPlayer::Key_Check()
{

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && m_eCurState != Player_STATE::ATTACK)
	{
		if (!m_bJump)
		{
			m_eCurState = JUMP;
			m_pFrameKey = L"PLAYER_JUMP";
			m_bJump = true;
			m_iJumpCnt++;
			m_fJumpY = m_tInfo.fY;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::JUMP);
			CSoundMgr::Get_Instance()->PlaySound(L"Jump.mp3", CSoundMgr::JUMP);
		}		
		else if (m_iJumpCnt < 2)
		{
		    m_eCurState = JUMP;
		    m_pFrameKey = L"PLAYER_JUMP";
			m_bJump = true;
			m_iJumpCnt++;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) && m_eCurState != Player_STATE::ATTACK)
	{
		if (!m_bJump)
		{
			m_eCurState = WALK;
			m_pFrameKey = L"PLAYER_WALK";
			m_bRight = false;
		}
		m_tInfo.fX -= m_fSpeed;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) && m_eCurState != Player_STATE::ATTACK)
	{
		if (!m_bJump)
		{
			m_eCurState = WALK;
			m_pFrameKey = L"PLAYER_WALK";
			m_bRight = true;
		}
		m_tInfo.fX += m_fSpeed;
	}	
	else if (!m_bJump)
	{
		m_eCurState = IDLE;
		m_pFrameKey = L"PLAYER_IDLE";
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LCONTROL) && m_eCurState != Player_STATE::JUMP)
	{
		m_eCurState = ATTACK;
		m_pFrameKey = L"PLAYER_ATTACK";
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ALLOW_START);
		CSoundMgr::Get_Instance()->PlaySound(L"ALLOWUse.mp3", CSoundMgr::ALLOW_START);
		CObjMgr::Get_Instance()->Add_Object(OBJID::ALLOW, Create_Allow<CAllow>());
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, Create_Effect<CAllowShotEffect>());		
	}
	else if (CKeyMgr::Get_Instance()->key_Up(VK_LCONTROL) && m_eCurState != Player_STATE::JUMP)
	{
		if (CObjMgr::Get_Instance()->Get_AllowEffect(OBJID::EFFECT) != nullptr)
		{
			dynamic_cast<CObj*>(CObjMgr::Get_Instance()->Get_AllowEffect(OBJID::EFFECT))->Set_Dead();
			CObjMgr::Get_Instance()->DeleteID(OBJID::EFFECT);
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LCONTROL) && m_eCurState != Player_STATE::JUMP)
	{
		m_eCurState = ATTACK;
		m_pFrameKey = L"PLAYER_ATTACK";
		Allow_Shot();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A') && m_iSkillCnt <= 0)
	{
		m_eCurState = HOWLINGGAIL;
		m_pFrameKey = L"PLAYER_ATTACK";
		m_iSkillCnt++;
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::HOWLINGGAIL_START);
		CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Use.mp3", CSoundMgr::HOWLINGGAIL_START);
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, Create_Effect<CHowlingGailUsed>());
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_END) && m_bPickupPotion)
	{
		m_tStat.fHp = m_tStat.fMaxHp;
		m_tStat.fMp = m_tStat.fMaxMp;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_HOME))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, Create_BUFF<CBUFFSKILL>());
		CSoundMgr::Get_Instance()->PlaySound(L"MapleWarrior.mp3", CSoundMgr::MAPLEWARRIOR);
		if (!m_UsedMapleWarrior)
		{
			m_tStat.iAttack += m_tStat.iAttack * (1 + 30 / 100); // 데미지를 30% 증가
			m_UsedMapleWarrior = true;
		}
	}

	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_PRIOR)) // PgUP 키
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, Create_BUFF<CSharpEyes>());
		CSoundMgr::Get_Instance()->PlaySound(L"SharpEyes.mp3", CSoundMgr::SHARPEYES);
		if (!m_UsedSharpEyes)
		{
			m_tStat.iAttack += m_tStat.iAttack * (1 + 30 / 100);
			m_UsedSharpEyes = true;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CObj* pObj = CAbstractFactory<CStatUI>::Create(200, 200);
		CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);
	}
}

void CPlayer::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 300;
			break;
		case CPlayer::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPlayer::JUMP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPlayer::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPlayer::HOWLINGGAIL:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPlayer::DEAD:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer::Allow_Shot()
{
	if (m_fDelay > 1.f)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::ALLOW, Create_Allow<CAllow>());
		m_fDelay = 0.f;
	}

	m_fDelay += 0.1f;
}