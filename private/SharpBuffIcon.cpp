#include "framework.h"
#include "SharpBuffIcon.h"
#include "ResourcesMgr.h"

CSharpBuffIcon::CSharpBuffIcon()
{
}

CSharpBuffIcon::~CSharpBuffIcon()
{
}

void CSharpBuffIcon::Init()
{
	m_eRenderGroup = RENDER_SORT::UI;
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/BUFF/SharpEyes_Icon.bmp", L"SharpEyes_Icon");
	m_tInfo.iCX = 32;
	m_tInfo.iCY = 32;
	m_pFrameKey = L"SharpEyes_Icon";
}

int CSharpBuffIcon::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSharpBuffIcon::Late_Update()
{
}

void CSharpBuffIcon::Render(HDC _DC)
{
	Update_Rect();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CSharpBuffIcon::Release()
{
}
