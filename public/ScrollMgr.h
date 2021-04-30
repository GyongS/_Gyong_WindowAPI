#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__

class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	void Set_ScrollX(float _x) 
	{
		if (m_fScrollX + _x <= 0.f && m_fScrollX + _x >= WINCX - MONSTERMAP_CX)
		{
			m_fScrollX += _x;
		}
	}
	void Set_ScrollY(float _y) 
	{
		if (m_fScrollY + _y <= 0.f && m_fScrollY + _y >= WINCY - MONSTERMAP_CY)
		{
			m_fScrollY += _y;
		}
	}

public:
	float Get_ScrollX() { return m_fScrollX; }
	float Get_ScrollY() { return m_fScrollY; }

public:
	void Scroll_Lock();

public:
	static CScrollMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CScrollMgr* m_pInstance;

	float	m_fScrollX;
	float	m_fScrollY;

};

#endif // !__SCROLLMGR_H__
