#include "framework.h"
#include "MonsterStage.h"
#include "ResourcesMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "MainUI.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "HPbar.h"
#include "MPbar.h"
#include "UIBackGround.h"
#include "Monster.h"
#include "MonsterMapFloor.h"
#include "MonsterHPbar.h"
#include "MonsterHPBG.h"
#include "PotionUI.h"
#include "SoundMgr.h"

CMonsterStage::CMonsterStage()
{
	ZeroMemory(&m_tPortalRect, sizeof(m_tPortalRect));
}


CMonsterStage::~CMonsterStage()
{
	Release();
}

void CMonsterStage::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Map/Monster_Map.bmp", L"Monster_Map");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/MainUI.bmp", L"MainUI");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/SelectMode.bmp", L"SelectMode");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/HPBAR.bmp", L"HPBAR");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/MPBAR.bmp", L"MPBAR");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/UIBackGround.bmp", L"UIBackGround");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Item/Potion_NoEnabled.bmp", L"Potion_NoEnabled");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Item/Potion_Enable.bmp", L"Potion_Enable");
	CObj* pObj = CAbstractFactory<CPlayer>::Create(100, 970);
	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, pObj);		

	InitFloorRect();

	pObj = CAbstractFactory<CMainUI>::Create(685, 383);
	pObj->Set_FrameKey(L"MainUI");
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);

	pObj = CAbstractFactory<CPotionUI>::Create(1102, 739);
	CObjMgr::Get_Instance()->Add_Object(OBJID::POTION_UI, pObj);

	pObj = CAbstractFactory<CHPbar>::Create(693, 723);
	pObj->Set_FrameKey(L"HPBAR");
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);

	pObj = CAbstractFactory<CUIBackGround>::Create(685, 730);
	pObj->Set_FrameKey(L"UIBackGround");
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);

	pObj = CAbstractFactory<CMPbar>::Create(693, 739);
	pObj->Set_FrameKey(L"MPBAR");
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);

	CSoundMgr::Get_Instance()->PlayBGM(L"TempleInTheMirror.mp3");

	m_tPortalRect = { 2963,1089,3037,1213};

}

void CMonsterStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	RECT rc = {};
	if (IntersectRect(&rc, &m_tPortalRect, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect()))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.mp3", CSoundMgr::UI);
			m_bNextScene = true;
		}
		if (m_bNextScene)
		{
			CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::ENTRANCE);			
		}
	}
}

void CMonsterStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMonsterStage::Render(HDC _DC)
{	
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Monster_Map");
	
	BitBlt(_DC,iScrollX
		, iScrollY, MONSTERMAP_CX, MONSTERMAP_CY, hMemDC, 0, 0, SRCCOPY);

	//Rectangle(_DC, m_tPortalRect.left + iScrollX, m_tPortalRect.top + iScrollY, m_tPortalRect.right + iScrollX, m_tPortalRect.bottom + iScrollY);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CMonsterStage::Release()
{
	m_bNextScene = false;
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER_HP);
	CObjMgr::Get_Instance()->DeleteID(OBJID::FLOOR);
}



void CMonsterStage::InitFloorRect()
{
	
	CObj* pObj = CAbstractFactory<CMonsterMapFloor>::Create(1600, 1250, MONSTERMAP_CX, 100);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);
	

	pObj = CAbstractFactory<CMonsterMapFloor>::Create(993, 969, 700, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(993, 869);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	

	pObj = CAbstractFactory<CMonsterMapFloor>::Create(377, 710, 700, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(377, 610);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);



	pObj = CAbstractFactory<CMonsterMapFloor>::Create(339, 305, 450, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(350, 205);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	

	pObj = CAbstractFactory<CMonsterMapFloor>::Create(991, 433, 680, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(995, 333);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);



	pObj = CAbstractFactory<CMonsterMapFloor>::Create(1603, 709, 680, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1610, 609);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);
	

	pObj = CAbstractFactory<CMonsterMapFloor>::Create(2223, 429, 680, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2230, 329);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);


	pObj = CAbstractFactory<CMonsterMapFloor>::Create(2223, 963, 680, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2230, 863);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);


	pObj = CAbstractFactory<CMonsterMapFloor>::Create(2853, 711, 680, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2870, 611);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);


	pObj = CAbstractFactory<CMonsterMapFloor>::Create(2899, 311, 450, 50);
	CObjMgr::Get_Instance()->Add_Object(OBJID::FLOOR, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2910, 211);
	pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);
}
