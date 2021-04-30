#include "framework.h"
#include "BeholderEye.h"
#include "ResourcesMgr.h"
#include "YellowMeteor.h"
#include "PurpleMeteor.h"
#include "Phase1.h"
#include "ObjMgr.h"
#include "SceneMgr.h"


CBeholderEye::CBeholderEye() : m_eCurState(END), m_ePreState(END)
{
}

CBeholderEye::~CBeholderEye()
{
}

void CBeholderEye::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/BeholderEye/BeholderEye_START.bmp", L"BeholderEye_START");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/BeholderEye/BeholderEye_Loop.bmp", L"BeholderEye_Loop");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/BeholderEye/BeholderEye_DEAD.bmp", L"BeholderEye_DEAD");

	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 600;
	m_tInfo.iCY = 400;
	m_tInfo.iColX = 200;
	m_tInfo.iColY = 100;
	m_eCurState = START;
	m_pFrameKey = L"BeholderEye_START";

}

int CBeholderEye::Update()
{
	if (m_bDead)
	{		
		dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledTriggerExit(false);
		return OBJ_DEAD;
	}

	Change_State();
	Next_State();
	Update_Frame();
	Update_CollisionRect();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBeholderEye::Late_Update()
{
	if (m_eCurState == DEAD && m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		if (dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_ShiledSpawnCheck())
		{
			dynamic_cast<CObj*>(CObjMgr::Get_Instance()->Get_Beholder_Shiled())->Set_Dead();
			dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledSpawnCheck(false);
		}
		m_bDead = true;
	}	
}

void CBeholderEye::Render(HDC _DC)
{
	Update_CollisionRect();
	Update_Rect();


	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CBeholderEye::Release()
{
}

void CBeholderEye::Change_State()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CBeholderEye::START:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CBeholderEye::LOOP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CBeholderEye::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBeholderEye::Next_State()
{

    if (m_eCurState == START && m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_eCurState = LOOP;
		m_pFrameKey = L"BeholderEye_Loop";
	}
	if (m_eCurState == LOOP)
	{
		if (!dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Block_BlueHP() &&
			!dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Block_PurpleHP()
			|| dynamic_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_Shiled_TriggerExit())
		{			
			
			m_eCurState = DEAD;
			m_pFrameKey = L"BeholderEye_DEAD";
		}	
	}
}