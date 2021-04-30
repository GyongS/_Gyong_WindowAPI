#include "framework.h"
#include "BossStage2.h"
#include "ResourcesMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Phase2.h"
#include "Phase2UI.h"
#include "Phase2MainHP.h"
#include "MapPattern.h"
#include "SoundMgr.h"
CBossStage2::CBossStage2()
{
}

CBossStage2::~CBossStage2()
{
	Release();
}

void CBossStage2::Init()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Phase2BGM.mp3");

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Map/Phase2.bmp", L"Phase2_Map");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/Phase2_will_hp.bmp", L"PHASE2_UI");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/WILL_MAINHP.bmp", L"Phase2_MAINHP");

	CLineMgr::Get_Instance()->Init();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(100, 380);

	CObj* pObj = CAbstractFactory<CPhase2>::Create(980, 430);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE2, pObj);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	pObj = CAbstractFactory<CPhase2UI>::Create(700, 30);
	pObj->Set_FrameKey(L"PHASE2_UI");
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE2_HP, pObj);

	pObj = CAbstractFactory<CPhase2MainHP>::Create(718, 20);
	pObj->Set_FrameKey(L"Phase2_MAINHP");
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE2_HP, pObj);

	pObj = CAbstractFactory<CMapPattern>::Create(100, 100);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_PATTERN, pObj);

}

void CBossStage2::Update()
{
	CObjMgr::Get_Instance()->Update();

}

void CBossStage2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CBossStage2::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Phase2_Map");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CLineMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CBossStage2::Release()
{
	CSoundMgr::Get_Instance()->StopBGM();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PHASE2_HP);
	CObjMgr::Get_Instance()->DeleteID(OBJID::WILL_WALL);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MAP_PATTERN);
	CObjMgr::Get_Instance()->DeleteID(OBJID::PHASE2);
	CObjMgr::Get_Instance()->DeleteID(OBJID::HOWLING);

	CLineMgr::Destroy_Instance();
}
