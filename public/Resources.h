#pragma once

#ifndef __RESOURCES_H__
#define __RESOURCES_H__


class CResources
{
public:
	CResources();
	~CResources();

public:
	HDC Get_DC() { return m_hMemDC; }
	void Load_Resources(const TCHAR* _pFilePath);
	void Release();


public:
	HDC m_hMemDC;

	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
};

#endif // !__RESOURCES_H__
