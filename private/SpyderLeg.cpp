#include "framework.h"
#include "SpyderLeg.h"
#include "ResourcesMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CSpyderLeg::CSpyderLeg() : m_bHitLeg(false)
{
}

CSpyderLeg::~CSpyderLeg()
{
	Release();
}

void CSpyderLeg::Init()
{
	// 거미 다리
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/SPYDER_LEG/SPYDERLEG_START.bmp", L"SPYDERLEG_START");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/SPYDER_LEG/SPYDERLEG_HIT.bmp", L"SPYDERLEG_HIT");

	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 680;
	m_tInfo.iCY = 720;
	m_tInfo.iColX = 100;
	m_tInfo.iColY = 600;
	m_pFrameKey = L"SPYDERLEG_START";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 30;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 80;

}

void CSpyderLeg::Late_Init()
{
	
}

int CSpyderLeg::Update()
{
	Late_Init();
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Frame();
	Update_Rect();
	Update_CollisionRect();
	return OBJ_NOEVENT;
}

void CSpyderLeg::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 8 && !m_bHitLeg)
	{		
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MapLegHitCheck(true);
		m_bHitLeg = true;
	}
}

void CSpyderLeg::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);

}

void CSpyderLeg::Release()
{
}