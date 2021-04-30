#include "framework.h"
#include "Title.h"
#include "ResourcesMgr.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
	Release();
}

void CTitle::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Title/Title.bmp", L"Title");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Button/Quit.bmp", L"Quit");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Button/Start.bmp", L"Start");

	CObj* pObj = CAbstractFactory<CMyButton>::Create(660.f, 300.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJID::TITLEUI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(660.f, 370);
	pObj->Set_FrameKey(L"Quit");
	CObjMgr::Get_Instance()->Add_Object(OBJID::TITLEUI, pObj);

	CSoundMgr::Get_Instance()->PlayBGM(L"FloralLife.mp3");

}

void CTitle::Update()
{
	CObjMgr::Get_Instance()->Update();	
}

void CTitle::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CTitle::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Title");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(_DC);
}

void CTitle::Release()
{
	CSoundMgr::Get_Instance()->StopBGM();
	CObjMgr::Get_Instance()->DeleteID(OBJID::TITLEUI);
}
