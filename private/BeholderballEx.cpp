#include "framework.h"
#include "BeholderballEx.h"
#include "ResourcesMgr.h"
#include "SoundMgr.h"

CBeholderballEx::CBeholderballEx() : m_fDist(0.f)
{
}

CBeholderballEx::~CBeholderballEx()
{
}

void CBeholderballEx::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/BeholderballEX/BeholderballEX_Loop.bmp", L"BeholderballEX_Loop");
	//CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/BeholderballEX/BeholderballEX_HIT.bmp", L"BeholderballEX_HIT");
	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	m_tInfo.iColX = 45;
	m_tInfo.iColY = 45;
	m_fDist = 100.f;
	m_fSpeed = 5.f;
	m_fRotation = 45.f;

	m_pFrameKey = L"BeholderballEX_Loop";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 8;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;


}

int CBeholderballEx::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += cosf(m_fRotation * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fRotation * PI / 180.f) * m_fSpeed;

	Update_Frame();
	Update_Rect();
	Update_CollisionRect();

	return OBJ_NOEVENT;
}

void CBeholderballEx::Late_Update()
{
	if (0 >= m_tRect.left || 0 >= m_tRect.top ||
		WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
		m_bDead = true;
}

void CBeholderballEx::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CBeholderballEx::Release()
{
}
