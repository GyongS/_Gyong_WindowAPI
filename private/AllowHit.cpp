#include "framework.h"
#include "AllowHit.h"
#include "Allow.h"
#include "ResourcesMgr.h"
#include "ScrollMgr.h"


CAllowHit::CAllowHit()
{
}

CAllowHit::~CAllowHit()
{
}

void CAllowHit::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/ALLOW/HIT.bmp", L"ALLOW_HIT");
	m_eRenderGroup = RENDER_SORT::OBJECT;	
	m_tInfo.iCX = 191;
	m_tInfo.iCY = 177;
	m_pFrameKey = L"ALLOW_HIT";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 5;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CAllowHit::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CAllowHit::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
}

void CAllowHit::Render(HDC _DC)
{
	Update_Rect();
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left + iScrollX, m_tRect.top + iScrollY);
}

void CAllowHit::Release()
{
}
