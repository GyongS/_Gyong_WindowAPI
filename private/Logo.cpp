#include "framework.h"
#include "Logo.h"
#include "ResourcesMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Logo/Logo.bmp", L"Logo");
}

void CLogo::Update()
{
}

void CLogo::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::TITLE);
		return;
	}
}

void CLogo::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Logo");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
