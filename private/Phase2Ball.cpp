#include "framework.h"
#include "Phase2Ball.h"
#include "ObjMgr.h"
#include "ResourcesMgr.h"

CPhase2Ball::CPhase2Ball() : m_bCheck(false)
{
}

CPhase2Ball::~CPhase2Ball()
{
}

void CPhase2Ball::Init()
{

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/SKILL_BALL/BALL.bmp", L"PHASE2_BALL");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/SKILL_BALL/BALL_STRETCH.bmp", L"PHASE2_BALL_STRETCH");
	m_tInfo.iCX         = 290;
	m_tInfo.iCY         = 173;
	m_tInfo.iColX = 200;
	m_tInfo.iColY = 250;

	m_fSpeed            = 5.f;
	m_pFrameKey         = L"PHASE2_BALL";
	m_pStretch          = L"PHASE2_BALL_STRETCH";
	m_tFrame.iStartX    = 0;
	m_tFrame.iEndX      = 8;
	m_tFrame.iScene     = 0;
	m_tFrame.dwTime     = GetTickCount();
	m_tFrame.dwNextTime = 100;
	m_eRenderGroup      = RENDER_SORT::OBJECT;
	if (CObjMgr::Get_Instance()->Get_Phase2()->Get_bRight())
	{
		m_bCheck = true;
	}
}

int CPhase2Ball::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	if (m_bCheck)
		m_tInfo.fX += m_fSpeed;
	else
		m_tInfo.fX -= m_fSpeed;

	Update_Rect();
	Update_CollisionRect();
	Update_Frame();

	return OBJ_NOEVENT;
}

void CPhase2Ball::Late_Update()
{
	if (0 >= m_tRect.left || WINCX <= m_tRect.right)
	{
		m_bDead = true;
	}
}

void CPhase2Ball::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();
	if (m_bCheck)
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left, m_tRect.top);
	}
	else
	{
		Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left, m_tRect.top);

	}
}

void CPhase2Ball::Release()
{
}
