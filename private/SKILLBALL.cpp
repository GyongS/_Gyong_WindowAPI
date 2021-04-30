#include "framework.h"
#include "SKILLBALL.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
CSKILLBALL::CSKILLBALL() : m_bCheck(false), m_bHitCheck(false)
{
}

CSKILLBALL::~CSKILLBALL()
{
}

void CSKILLBALL::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase1/BALL_Loop/BALL_Loop.bmp", L"BALL_Loop");
	m_eRenderGroup      = RENDER_SORT::OBJECT;
	m_tInfo.iCX         = 344;
	m_tInfo.iCY         = 525;
	m_tInfo.iColX       = 200;
	m_tInfo.iColY       = 500;
	m_fSpeed            = 5.f;
	m_pFrameKey         = L"BALL_Loop";
	m_tFrame.iStartX    = 0;
	m_tFrame.iEndX      = 10;
	m_tFrame.iScene     = 0;
	m_tFrame.dwTime     = GetTickCount();
	m_tFrame.dwNextTime = 100;

	if (CObjMgr::Get_Instance()->Get_Phase1()->Get_bRight())
	{
		m_bCheck = true;
	}
}

int CSKILLBALL::Update()
{
	if (m_bDead )
	{
		return OBJ_DEAD;
	}
	if (m_bCheck)
		m_tInfo.fX += m_fSpeed;
	else
		m_tInfo.fX -= m_fSpeed;

	Update_Rect();
	Update_CollisionRect();
	Update_Frame();

	return OBJ_NOEVENT;
}

void CSKILLBALL::Late_Update()
{
	if (0 >= m_tRect.left || WINCX <= m_tRect.right )
	{
		m_bDead = true;
	}
}

void CSKILLBALL::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CSKILLBALL::Release()
{
}
