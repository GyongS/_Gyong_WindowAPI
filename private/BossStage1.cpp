#include "framework.h"
#include "BossStage1.h"
#include "ResourcesMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Phase1.h"
#include "Phase1UI.h"
#include "Phase1MainHP.h"
#include "Phase1BlueHP.h"
#include "Phase1PurpleHP.h"
#include "MoonLight.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "MoonGauge.h"
#include "MoonEffect.h"
#include "MapPattern.h"
#include "SpyderLeg.h"
#include "LockHP.h"
#include "ServeLockHP.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CBossStage1::CBossStage1() : m_bChangeMap(false)
{
}

CBossStage1::~CBossStage1()
{
	Release();
}

void CBossStage1::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Map/Phase1_Blue.bmp", L"BLUE");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Map/Phase1_Purple.bmp", L"Purple");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/Phase1_will_hp.bmp", L"PHASE1_UI");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/WILL_MAINHP.bmp", L"MAINHP");


	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(100, 630);

	CObj* pObj = CAbstractFactory<CPhase1>::Create(700, 550);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1, pObj);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	pObj = CAbstractFactory<CPhase1UI>::Create(700, 30);
	pObj->Set_FrameKey(L"PHASE1_UI");
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);

	pObj = CAbstractFactory<CPhase1MainHP>::Create(718, 20);
	pObj->Set_FrameKey(L"MAINHP");
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);

	pObj = CAbstractFactory<CPhase1PurpleHP>::Create(718, 36);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);

	pObj = CAbstractFactory<CPhase1BlueHP>::Create(718, 44);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);

	pObj = CAbstractFactory<CMoonLight>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);

	pObj = CAbstractFactory<CMapPattern>::Create(100, 100);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_PATTERN, pObj);

	pObj = CAbstractFactory<CLockHP>::Create(718, 20);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);

	pObj = CAbstractFactory<CServeLockHP>::Create(718, 40);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PHASE1_HP, pObj);
}

void CBossStage1::Update()
{
	CObjMgr::Get_Instance()->Update();
	
}

void CBossStage1::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('1') &&
		dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Get_MoonCurGauge() >=
		dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Get_MoonMaxGauge() && !m_bChangeMap)
	{
		m_bChangeMap = true;
		dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Init_Gauge();
		dynamic_cast<CMoonEffect*>(CObjMgr::Get_Instance()->Get_MoonEffect())->Set_Dead();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('2') &&
		dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Get_MoonCurGauge() >=
		dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Get_MoonMaxGauge() && m_bChangeMap)
	{
		m_bChangeMap = false;
		dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Init_Gauge();
		dynamic_cast<CMoonEffect*>(CObjMgr::Get_Instance()->Get_MoonEffect())->Set_Dead();
	}
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CBossStage1::Render(HDC _DC)
{

	if (m_bChangeMap)
	{
		HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Purple");
		BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
		CLineMgr::Get_Instance()->Render(_DC);
		CObjMgr::Get_Instance()->Render(_DC);
	}
	else
	{
		HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"BLUE");
		BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
		CLineMgr::Get_Instance()->Render(_DC);
		CObjMgr::Get_Instance()->Render(_DC);
	}

	
}

void CBossStage1::Release()
{
	CSoundMgr::Get_Instance()->StopBGM();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PHASE1);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MOONGAUGE);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MAP_PATTERN);
	CObjMgr::Get_Instance()->DeleteID(OBJID::PHASE1_HP);
	CObjMgr::Get_Instance()->DeleteID(OBJID::HOWLING);
	CLineMgr::Destroy_Instance();
}
