#include "framework.h"
#include "StatUI.h"
#include "ResourcesMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

CStatUI::CStatUI()
{
}

CStatUI::~CStatUI()
{
}

void CStatUI::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Stat_main.bmp", L"Stat");	
	m_eRenderGroup = RENDER_SORT::UI;

	m_pFrameKey = L"Stat";
}

int CStatUI::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		m_bDead = true;
	}

	return OBJ_NOEVENT;
}

void CStatUI::Late_Update()
{
}

void CStatUI::Render(HDC _DC)
{
	// 숫자 표기	

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	BitBlt(_DC, 100, 200, 212, 318, hMemDC, 0, 0, SRCCOPY);

	TCHAR szBuff[64] = L"";
	swprintf_s(szBuff, L"%d", static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Stat().iAttack);
	TextOut(_DC, 170, 300, szBuff, lstrlen(szBuff));
}

void CStatUI::Release()
{
}
