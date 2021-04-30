#include "framework.h"
#include "Entrance.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
CEntrance::CEntrance()
{
	ZeroMemory(&m_tPortalRect, sizeof(m_tPortalRect));
}

CEntrance::~CEntrance()
{
	Release();
}

void CEntrance::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Map/Entrance.bmp", L"Entrance");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/SelectMode.bmp", L"SelectMode");
	CLineMgr::Get_Instance()->Init();

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(100, 700);
	m_tPortalRect = { 940,500,1017,676 };
}

void CEntrance::Update()
{
	CObjMgr::Get_Instance()->Update();
	RECT rc = {};
	if (IntersectRect(&rc, &m_tPortalRect, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect()))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
		{
			m_bNextScene = true;
		}
		if (m_bNextScene)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			{
				CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::PHASE1_VIDEO);
			}
		}
	}
}

void CEntrance::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CEntrance::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Entrance");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	if (m_bNextScene)
	{
		hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"SelectMode");

		BitBlt(_DC, 300, 300, 825, 267, hMemDC, 0, 0, SRCCOPY);
	}	

	CLineMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);	
}

void CEntrance::Release()
{
	CSoundMgr::Get_Instance()->StopBGM();
}
