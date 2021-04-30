#include "framework.h"
#include "YellowMeteor.h"
#include "ResourcesMgr.h"

CYellowMeteor::CYellowMeteor()
{
}

CYellowMeteor::~CYellowMeteor()
{
}

void CYellowMeteor::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(
		L"../Resources/Will/MapPattern/BeholderEye/YELLOW_METEOR/YELLOW_METEOR.bmp", L"YELLOW_METEOR");

	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 171;
	m_tInfo.iCY = 222;
	m_fSpeed = 3.f;
	m_pFrameKey = L"YELLOW_METEOR";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 8;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CYellowMeteor::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;

	Update_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CYellowMeteor::Late_Update()
{
	if ( WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CYellowMeteor::Render(HDC _DC)
{
	Update_Rect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CYellowMeteor::Release()
{
}
