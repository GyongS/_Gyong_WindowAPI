#include "framework.h"
#include "MyButton.h"
#include "ResourcesMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Init()
{
	m_tInfo.iCX = 140;
	m_tInfo.iCY = 52;

	m_eRenderGroup = RENDER_SORT::UI;
}

void CMyButton::Late_Init()
{
}

int CMyButton::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(m_pFrameKey, L"Start"))
			{
				CSceneMgr::Get_Instance()->Change_Scene(CSceneMgr::MONSTERSTAGE);
				return;
			}
			if (!lstrcmp(m_pFrameKey, L"Quit"))
			{
				DestroyWindow(g_hWnd);
				return;
			}
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC _DC)                                  
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_iDrawID * 140, 0
		, 140, 52
		, RGB(255, 0, 255));
}

void CMyButton::Release()
{

}
