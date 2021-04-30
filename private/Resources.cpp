#include "framework.h"
#include "Resources.h"

CResources::CResources()
{
}

CResources::~CResources()
{
	Release();

}

void CResources::Load_Resources(const TCHAR* _pFilePath)
{
	HDC hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBmp = (HBITMAP)LoadImage(NULL, _pFilePath
		, IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);
}

void CResources::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBmp);
	DeleteDC(m_hMemDC);
}
