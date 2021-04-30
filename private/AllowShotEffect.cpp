#include "framework.h"
#include "AllowShotEffect.h"
#include "ResourcesMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CAllowShotEffect::CAllowShotEffect() : m_bEndSkill(false), m_bCheck(false)
{

}


CAllowShotEffect::~CAllowShotEffect()
{
	Release();
}

void CAllowShotEffect::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ALLOW/KeyPressing.bmp", L"KeyPressing");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ALLOW/PRESSING_STRETCH.bmp", L"PRESSING_STRETCH");

	m_eRenderGroup = RENDER_SORT::EFFECT;

	m_tInfo.iCX         = 251;
	m_tInfo.iCY         = 328;
	m_pFrameKey         = L"KeyPressing";
	m_pStretch          = L"PRESSING_STRETCH";
	m_tFrame.iStartX    = 0;
	m_tFrame.iEndX      = 6;
	m_tFrame.iScene     = 0;
	m_tFrame.dwTime     = GetTickCount();
	m_tFrame.dwNextTime = 100;
	m_bEndSkill = true;
	if (CObjMgr::Get_Instance()->Get_Player()->Get_bRight())
	{
		m_bCheck = true;
	}	
}

void CAllowShotEffect::Late_Init()
{
	if (m_bCheck)
	{
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + 60;
	}
	else
	{
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 60;
	}
}

int CAllowShotEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Late_Init();

	Update_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CAllowShotEffect::Late_Update()
{

}

void CAllowShotEffect::Render(HDC _DC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{
		if (m_bCheck)
		{
			Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, true, m_tRect.left + iScrollX, m_tRect.top+ iScrollY);
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
			Reverse_Bmp(_DC, m_pFrameKey, m_pStretch, false, m_tRect.left , m_tRect.top);

		}
	}
}

void CAllowShotEffect::Release()
{
	
}

