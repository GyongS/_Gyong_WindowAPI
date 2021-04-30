#pragma once
#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class CScene;
class CSceneMgr
{
public:
	enum SCENEID {
		LOGO,
		TITLE,
		MONSTERSTAGE,
		ENTRANCE,
		PHASE1_VIDEO,
		PHASE1,
		PHASE2_VIDEO,
		PHASE2,
		PHASE3_VIDEO,
		PHASE3,
		END
	};

public:
	CSceneMgr();
	~CSceneMgr();

public:
	void Change_Scene(SCENEID _eSceneID);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	CScene* Get_CurrentScene() const { return m_pScene; }
	const SCENEID& Get_SceneID() const { return m_eCurScene; }

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	CScene* m_pScene;
	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;
	static CSceneMgr* m_pInstance;
};

#endif // !__SCENEMGR_H__
