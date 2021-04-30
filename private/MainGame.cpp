#include "framework.h"
#include "MainGame.h"
#include "Player.h"
#include "Phase1.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"
#include "time.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_iFPS(0), m_dwTime(GetTickCount())
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Init()
{
	srand((unsigned)time(NULL));

	m_DC = GetDC(g_hWnd);

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Title/Title.bmp", L"Back");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Title/Title.bmp", L"BackBuffer");
	CSoundMgr::Get_Instance()->Initialize();

	CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::LOGO);

}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CMainGame::Render()
{
	if (CSceneMgr::PHASE1_VIDEO == CSceneMgr::Get_Instance()->Get_SceneID() || CSceneMgr::PHASE2_VIDEO == CSceneMgr::Get_Instance()->Get_SceneID()
		|| CSceneMgr::PHASE3_VIDEO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC hBackBuffer = CResourcesMgr::Get_Instance()->Find_DC(L"BackBuffer");
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Back");

	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);

	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		TCHAR szFPS[64] = L"";
		swprintf_s(szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	CLineMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CResourcesMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}
