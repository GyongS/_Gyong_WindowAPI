#include "framework.h"
#include "BossStage3.h"
#include "ObjMgr.h"
#include "ResourcesMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Phase3.h"
#include "Phase3UI.h"
#include "Phase3MainHP.h"
#include "MapPattern.h"
#include "SoundMgr.h"

CBossStage3::CBossStage3()
{
}

CBossStage3::~CBossStage3()
{
	Release();
}

void CBossStage3::Init()
{

	CSoundMgr::Get_Instance()->PlayBGM(L"Phase3BGM.mp3");

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Map/Phase3.bmp", L"Phase3_Map");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/Phase3_will_hp.bmp", L"PHASE3_UI");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/WILL_MAINHP.bmp", L"Phase3_MAINHP");

	CLineMgr::Get_Instance()->Init();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(100, 500);

	CObj* pObj = CAbstractFactory<CPhase3>::Create(700, 500);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE3, pObj);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	pObj = CAbstractFactory<CPhase3UI>::Create(700, 30);
	pObj->Set_FrameKey(L"PHASE3_UI");
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE3_HP, pObj);

	pObj = CAbstractFactory<CPhase3MainHP>::Create(718, 20);
	pObj->Set_FrameKey(L"Phase3_MAINHP");
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE3_HP, pObj);

	pObj = CAbstractFactory<CMapPattern>::Create(100, 100);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_PATTERN, pObj);
}

void CBossStage3::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CBossStage3::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CBossStage3::Render(HDC _DC)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Phase3_Map");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CLineMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CBossStage3::Release()
{
	CSoundMgr::Get_Instance()->StopBGM();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PHASE3);
	CObjMgr::Get_Instance()->DeleteID(OBJID::PHASE3_HP);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MAP_PATTERN);
	CObjMgr::Get_Instance()->DeleteID(OBJID::HOWLING);

}

