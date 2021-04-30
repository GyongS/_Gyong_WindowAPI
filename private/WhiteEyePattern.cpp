#include "framework.h"
#include "WhiteEyePattern.h"
#include "ResourcesMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CWhiteEyePattern::CWhiteEyePattern()
{
}

CWhiteEyePattern::~CWhiteEyePattern()
{
}

void CWhiteEyePattern::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(
		L"../Resources/Will/Phase3/WhiteEye_Leg/WhiteEye_Leg.bmp", L"WhiteEye_Leg");
	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 422;
	m_tInfo.iCY = 629;
	m_tInfo.iColX = 100;
	m_tInfo.iColY = 200;
	m_pFrameKey = L"WhiteEye_Leg";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 15;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CWhiteEyePattern::Update()
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

void CWhiteEyePattern::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
}

void CWhiteEyePattern::Render(HDC _DC)
{
	Update_CollisionRect();
	Update_Rect();	
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);

}

void CWhiteEyePattern::Release()
{
}
