#include "framework.h"
#include "HowlingGail.h"
#include "ResourcesMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CHowlingGail::CHowlingGail(): m_fDelay(0.f), m_eCurState(END), m_ePreState(END)
{
}

CHowlingGail::~CHowlingGail()
{
}

void CHowlingGail::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/HowlingGail/BALL.bmp", L"HowlingGail_BALL");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/HowlingGail/DEAD.bmp", L"HowlingGail_DEAD");
	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 800;
	m_tInfo.iCY = 950;
	m_tInfo.iColX = 500;
	m_tInfo.iColY = 800;
	m_fSpeed = 3.f;
	m_pFrameKey = L"HowlingGail_BALL";	
	m_eCurState = LOOP;
}

int CHowlingGail::Update()
{

	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_End.mp3", CSoundMgr::HOWLINGGAIL_END);
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Init_SKillCnt();
		return OBJ_DEAD;
	}
	m_fDelay += 1.f;

	if (m_fDelay <= 900.f)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Loop.mp3", CSoundMgr::HOWLINGGAIL_LOOP);
	}
	if (m_fDelay >= 1000.f)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::HOWLINGGAIL_LOOP);
		Set_State(DEAD);
		m_pFrameKey = L"HowlingGail_DEAD";
		if (m_eCurState == DEAD)
		{
			if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
			{
				m_bDead = true;
			}
		}
	}

	Change_State();
	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHowlingGail::Late_Update()
{
	if (m_pTarget == nullptr)
		return;
	if (m_eCurState == LOOP)
	{
		if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
		{
			m_tFrame.iStartX -= 8;
		}
	}
	
	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	m_fRotation = acosf(fX / fDist);

	if (m_tInfo.fX < m_pTarget->Get_Info().fX)
		m_fRotation *= -1.f;

	m_tInfo.fX += cosf(m_fRotation) * m_fSpeed;
}

void CHowlingGail::Render(HDC _DC)
{
	Update_Rect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);

;}

void CHowlingGail::Release()
{
}

void CHowlingGail::Change_State()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CHowlingGail::LOOP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 14;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CHowlingGail::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
