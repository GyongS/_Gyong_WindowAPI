#include "framework.h"
#include "ServeLockHP.h"
#include "MonitorBreak.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"

CServeLockHP::CServeLockHP()
{
}

CServeLockHP::~CServeLockHP()
{
}

void CServeLockHP::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_hp/Phase1_will_hp_Block.bmp", L"SERVE_HPBLOCK");
	m_eRenderGroup = RENDER_SORT::PAHSE1_UI;

	m_tInfo.iCX = 2;
	m_tInfo.iCY = 14;
}

void CServeLockHP::Late_Init()
{	
}

int CServeLockHP::Update()
{
	Late_Init();

	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CServeLockHP::Late_Update()
{

}

void CServeLockHP::Render(HDC _DC)
{
	Update_Rect();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"SERVE_HPBLOCK");

	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CServeLockHP::Release()
{
}
