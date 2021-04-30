#include "framework.h"
#include "Phase3Video.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ResourcesMgr.h"

CPhase3Video::CPhase3Video()
{
}

CPhase3Video::~CPhase3Video()
{
	Release();
}

void CPhase3Video::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/IDLE.bmp", L"PHASE3_IDLE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/DEFAULT_ATTACK1.bmp", L"PHASE3_DEFAULT_ATTACK1");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/DEFAULT_ATTACK2.bmp", L"PHASE3_DEFAULT_ATTACK2");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/ATTACK_PUSH.bmp", L"PHASE3_ATTACK_PUSH");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/WhiteEye/WHITE_EYE.bmp", L"PHASE3_WhiteEye");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/RedEye/RED_EYE.bmp", L"PHASE3_RedEye");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/DEAD.bmp", L"PHASE3_DEAD");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/STRETCH.bmp", L"PHASE3_STRETCH");

	m_hVideo = MCIWndCreate(g_hWnd, nullptr, MCIWNDF_NOPLAYBAR | WS_CHILD | WS_VISIBLE
		, L"../Video/Phase3.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

void CPhase3Video::Update()
{
}

void CPhase3Video::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)
		|| MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo))
	{
		CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::PHASE3);
		return;
	}
}

void CPhase3Video::Render(HDC _DC)
{
}

void CPhase3Video::Release()
{
	MCIWndClose(m_hVideo);
}
