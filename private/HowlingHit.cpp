#include "framework.h"
#include "HowlingHit.h"
#include "ResourcesMgr.h"

CHowlingHit::CHowlingHit()
{
}

CHowlingHit::~CHowlingHit()
{
}

void CHowlingHit::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/HowlingGail/HowlingGail_HIT.bmp", L"HOWLING_HIT");
	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 358;
	m_tInfo.iCY = 299;
	m_pFrameKey = L"HOWLING_HIT";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 5;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CHowlingHit::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHowlingHit::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
}

void CHowlingHit::Render(HDC _DC)
{
	Update_Rect();
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CHowlingHit::Release()
{
}
