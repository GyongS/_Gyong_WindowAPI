#include "framework.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{
}

CLine::CLine(LINEPOS _tLeftPos, LINEPOS _tRightPos)
	: m_tInfo(_tLeftPos, _tRightPos)
{
}

CLine::~CLine()
{
	Release();
}

void CLine::Init()
{
}

void CLine::Render(HDC _DC)
{
	//int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//HPEN myPen, OldPen;
	//myPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	//OldPen = (HPEN)SelectObject(_DC, myPen);

	//MoveToEx(_DC, (int)m_tInfo.tLeftPos.fX + iScrollX, (int)m_tInfo.tLeftPos.fY + iScrollY, nullptr);
	//LineTo(_DC, (int)m_tInfo.tRightPos.fX + iScrollX, (int)m_tInfo.tRightPos.fY + iScrollY);

	//SelectObject(_DC, OldPen);
	//DeleteObject(myPen);
}

void CLine::Release()
{
}
