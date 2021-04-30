#include "framework.h"
#include "Phase2Video.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CPhase2Video::CPhase2Video()
{
}

CPhase2Video::~CPhase2Video()
{
	Release();

}

void CPhase2Video::Init()
{
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, MCIWNDF_NOPLAYBAR | WS_CHILD | WS_VISIBLE
		, L"../Video/Phase2.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

void CPhase2Video::Update()
{
}

void CPhase2Video::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)
		|| MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo))
	{
		CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::PHASE2);
		return;
	}
}

void CPhase2Video::Render(HDC _DC)
{
}

void CPhase2Video::Release()
{
	MCIWndClose(m_hVideo);

}
