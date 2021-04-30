#pragma once

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Init();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC			m_DC;
	int			m_iFPS;
	DWORD       m_dwTime;

	CObj*           m_pPlayer;
	list<CObj*>		m_listObj[OBJID::END];

};

