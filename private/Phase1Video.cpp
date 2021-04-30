#include "framework.h"
#include "Phase1Video.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CPhase1Video::CPhase1Video()
{
}

CPhase1Video::~CPhase1Video()
{
	Release();
}

void CPhase1Video::Init()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Phase1BGM.mp3");

	m_hVideo = MCIWndCreate(g_hWnd, nullptr, MCIWNDF_NOPLAYBAR | WS_CHILD | WS_VISIBLE
		, L"../Video/Phase1.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

void CPhase1Video::Update()
{
}

void CPhase1Video::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)
		|| MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo))
	{
		CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::PHASE1);
		return;
	}
}

void CPhase1Video::Render(HDC _DC)
{

}

void CPhase1Video::Release()
{
	MCIWndClose(m_hVideo);
}
