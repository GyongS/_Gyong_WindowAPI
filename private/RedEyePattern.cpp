#include "framework.h"
#include "RedEyePattern.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CRedEyePattern::CRedEyePattern()
{
}

CRedEyePattern::~CRedEyePattern()
{
}

void CRedEyePattern::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase3_2/RedEye_Leg/RedEye_Leg.bmp", L"RedEye_Leg");
	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 644;
	m_tInfo.iCY = 621;
	m_tInfo.iColX = 200;
	m_tInfo.iColY = 400;
	m_pFrameKey = L"RedEye_Leg";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 15;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CRedEyePattern::Update()
{
	if (m_bDead)
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_LegHitCheck(false);
		return OBJ_DEAD;
	}
	Update_Frame();
	Update_CollisionRect();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CRedEyePattern::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
	if (-500 >= m_tRect.left || 0 >= m_tRect.top
		|| WINCX + 500 <= m_tRect.right || WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}	
}

void CRedEyePattern::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CRedEyePattern::Release()
{
}
