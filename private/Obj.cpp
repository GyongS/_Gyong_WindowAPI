#include "framework.h"
#include "Obj.h"
#include "KeyMgr.h"
#include "ResourcesMgr.h"

CObj::CObj() : m_fRotation(0.f), m_fSpeed(0.f), m_bDead(false), m_pTarget(nullptr), m_iDrawID(0)
,m_pFrameKey(nullptr), m_eRenderGroup(RENDER_SORT::END), m_bRight(false), m_bLate_Init(false), m_pStretch(nullptr)
,m_pFrameKey_Right(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tCollisionRect, sizeof(m_tCollisionRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));	
}

CObj::~CObj()
{

}

void CObj::Late_Init()
{
	if (!m_bLate_Init)
	{
		this->Late_Init();
	}
	m_bLate_Init = true;
}

void CObj::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top    = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right  = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CObj::Update_CollisionRect()
{
	m_tCollisionRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iColX >> 1));
	m_tCollisionRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iColY >> 1));
	m_tCollisionRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iColX >> 1));
	m_tCollisionRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iColY >> 1));
}

void CObj::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwNextTime < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Update_FrameLoopEnd()
{
	if (m_tFrame.dwTime + m_tFrame.dwNextTime < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = m_tFrame.iEndX;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Update_FrameLoop()
{
	if (m_tFrame.dwTime + m_tFrame.dwNextTime < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = m_tFrame.iEndX - 3;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Update_PressingEnd()
{
	if (m_tFrame.dwTime + m_tFrame.dwNextTime < GetTickCount())
	{
		++m_tFrame.iStartX;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LCONTROL))
		{
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
				m_tFrame.iStartX = 0;
		}
		if (CKeyMgr::Get_Instance()->key_Up(VK_LCONTROL))
		{
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
				m_tFrame.iStartX = m_tFrame.iEndX;
		}
	}
}

void CObj::Reverse_Bmp(HDC _RenderDC, const TCHAR* _InFrameKey, const TCHAR* _InStretch, bool _bReverseCheck, int _Rect_L, int _Rect_T)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(_InFrameKey);
	HDC hStretchDC = CResourcesMgr::Get_Instance()->Find_DC(_InStretch);	

	StretchBlt(hStretchDC, 0, 0, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC, _bReverseCheck ? (m_tFrame.iStartX + 1) * m_tInfo.iCX : m_tFrame.iStartX * m_tInfo.iCX, 0
		, _bReverseCheck ? (-m_tInfo.iCX) : m_tInfo.iCX, m_tInfo.iCY, SRCCOPY);
	
	GdiTransparentBlt(_RenderDC
		, _Rect_L, _Rect_T
		, m_tInfo.iCX, m_tInfo.iCY
		, hStretchDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CObj::Anim_TransparentBlt(HDC _RenderDC, const TCHAR* _InFrameKey, int _Rect_L, int _Rect_T)
{
	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(_InFrameKey);

	GdiTransparentBlt(_RenderDC
		, _Rect_L, _Rect_T
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iStartX * m_tInfo.iCX, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}
