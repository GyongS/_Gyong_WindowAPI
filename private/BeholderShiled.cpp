#include "framework.h"
#include "BeholderShiled.h"
#include "ResourcesMgr.h"

CBeholderShiled::CBeholderShiled()
{
}

CBeholderShiled::~CBeholderShiled()
{
}

void CBeholderShiled::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/BeholderEye/SHILED/SHILED.bmp", L"BeholderEye_SHILED");

	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 436;
	m_tInfo.iCY = 247;
	m_tInfo.iColX = 200;
	m_tInfo.iColY = 100;
	m_pFrameKey = L"BeholderEye_SHILED";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 6;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;

}

int CBeholderShiled::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBeholderShiled::Late_Update()
{

}

void CBeholderShiled::Render(HDC _DC)
{
	Update_Rect();


	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CBeholderShiled::Release()
{

}
