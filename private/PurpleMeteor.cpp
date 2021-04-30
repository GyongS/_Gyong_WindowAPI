#include "framework.h"
#include "PurpleMeteor.h"
#include "ResourcesMgr.h"

CPurpleMeteor::CPurpleMeteor()
{
}

CPurpleMeteor::~CPurpleMeteor()
{
}

void CPurpleMeteor::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(
		L"../Resources/Will/MapPattern/BeholderEye/PURPLE_METEOR/PURPLE_METEOR.bmp", L"PURPLE_METEOR");

	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 198;
	m_tInfo.iCY = 254;
	m_fSpeed = 3.f;
	m_pFrameKey = L"PURPLE_METEOR";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 10;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CPurpleMeteor::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;


	Update_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPurpleMeteor::Late_Update()
{

	if ( WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CPurpleMeteor::Render(HDC _DC)
{
	Update_Rect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CPurpleMeteor::Release()
{
}
