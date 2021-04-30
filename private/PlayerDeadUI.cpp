#include "framework.h"
#include "PlayerDeadUI.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "KeyMgr.h"
#include "../Editor/ScrollMgr.h"
CPlayerDeadUI::CPlayerDeadUI()
{
}

CPlayerDeadUI::~CPlayerDeadUI()
{
}

void CPlayerDeadUI::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/DEAD_POP_UP.bmp", L"DEAD_POP_UP");

	m_tInfo.iCX = 299;
	m_tInfo.iCY = 129;
	m_pFrameKey = L"DEAD_POP_UP";
}

int CPlayerDeadUI::Update()
{
	if (m_bDead)
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Init_HP();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Init_MP();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DeadCheck(false);
		return OBJ_DEAD;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		m_bDead = true;
	}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayerDeadUI::Late_Update()
{
}

void CPlayerDeadUI::Render(HDC _DC)
{
	Update_Rect();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CPlayerDeadUI::Release()
{
}
