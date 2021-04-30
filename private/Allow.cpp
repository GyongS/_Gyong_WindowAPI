#include "framework.h"
#include "Allow.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CAllow::CAllow() : m_bCheck(false)
{
}

CAllow::~CAllow()
{
	Release();
}

void CAllow::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ALLOW/BALL.bmp", L"ALLOW");	
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ALLOW/BALL_STRETCH.bmp", L"BALL_STRETCH");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ALLOW/HIT.bmp", L"ALLOW_HIT");

	m_eRenderGroup = RENDER_SORT::OBJECT;	
	m_tInfo.iCX         = 119;
	m_tInfo.iCY         = 36;	
	m_fSpeed            = 10.f;
	m_pFrameKey         = L"ALLOW";
	m_pStretch          = L"BALL_STRETCH";
	m_tFrame.iStartX    = 0;
	m_tFrame.iEndX      = 1;
	m_tFrame.iScene     = 0;
	m_tFrame.dwTime     = GetTickCount();
	m_tFrame.dwNextTime = 100;	

	if (CObjMgr::Get_Instance()->Get_Player()->Get_bRight())
	{
		m_bCheck = true;
	}

}

void CAllow::Late_Init()
{
}

int CAllow::Update()
{

	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Late_Init();

	if(m_bCheck)
		m_tInfo.fX += m_fSpeed;
	else
		m_tInfo.fX -= m_fSpeed;

	Update_FrameLoopEnd();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CAllow::Late_Update()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{

		if (0 >= m_tRect.left || 0 >= m_tRect.top
			|| MONSTERMAP_CX <= m_tRect.right || MONSTERMAP_CY <= m_tRect.bottom)
		{
			m_bDead = true;
		}

		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 500 > m_tInfo.fX ||
			CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + 500 < m_tInfo.fX)
		{
			m_bDead = true;
		}
	}
	else
	{
		if (0 >= m_tRect.left || 0 >= m_tRect.top
			|| WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
		{
			m_bDead = true;
		}
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 500 > m_tInfo.fX ||
			CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + 500 < m_tInfo.fX)
		{
			m_bDead = true;
		}
	}
}

void CAllow::Render(HDC _DC)
{
	Update_Rect();	
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{
		if (m_bCheck)
		{
			Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left + iScrollX, m_tRect.top + iScrollY);
		}
		else
		{
			Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left + iScrollX, m_tRect.top + iScrollY);

		}
	}
	else
	{
		if (m_bCheck)
		{
			Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left, m_tRect.top);
		}
		else
		{
			Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left, m_tRect.top);

		}
	}
}

void CAllow::Release()
{

}
