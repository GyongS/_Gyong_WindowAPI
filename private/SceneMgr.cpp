#include "framework.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Logo.h"
#include "Title.h"
#include "MonsterStage.h"
#include "Entrance.h"
#include "BossStage1.h"
#include "BossStage2.h"
#include "BossStage3.h"
#include "Phase1Video.h"
#include "Phase2Video.h"
#include "Phase3Video.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(END), m_eCurScene(END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Change_Scene(SCENEID _eSceneID)
{
	m_eCurScene = _eSceneID;
	if (m_ePreScene != m_eCurScene)
	{
		Release();

		switch (m_eCurScene)
		{
		case CSceneMgr::LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneMgr::TITLE:
			m_pScene = new CTitle;
			break;
		case CSceneMgr::MONSTERSTAGE:
			m_pScene = new CMonsterStage;
			break;
		case CSceneMgr::ENTRANCE:
			m_pScene = new CEntrance;
			break;
		case CSceneMgr::PHASE1_VIDEO:
			m_pScene = new CPhase1Video;
			break;
		case CSceneMgr::PHASE1:
			m_pScene = new CBossStage1;
			break;
		case CSceneMgr::PHASE2_VIDEO:
			m_pScene = new CPhase2Video;
			break;
		case CSceneMgr::PHASE2:
			m_pScene = new CBossStage2;
			break;
		case CSceneMgr::PHASE3_VIDEO:
			m_pScene = new CPhase3Video;
			break;
		case CSceneMgr::PHASE3:
			m_pScene = new CBossStage3;
			break;
		}
		m_pScene->Init();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
}
