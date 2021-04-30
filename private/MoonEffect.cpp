#include "framework.h"
#include "MoonEffect.h"
#include "ResourcesMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MoonGauge.h"
#include "SceneMgr.h"

CMoonEffect::CMoonEffect()
{
}

CMoonEffect::~CMoonEffect()
{
}

void CMoonEffect::Init()
{
	m_eRenderGroup = RENDER_SORT::BOSSMAIN_UI;

	m_tInfo.iCX = 156;
	m_tInfo.iCY = 156;
	
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 6;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

int CMoonEffect::Update()
{
	if (m_bDead || CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE1)
	{
		return OBJ_DEAD;
	}

	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMoonEffect::Late_Update()
{
}

void CMoonEffect::Render(HDC _DC)
{
	Update_Rect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top); 
}

void CMoonEffect::Release()
{
}
