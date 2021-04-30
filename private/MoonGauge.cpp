#include "framework.h"
#include "MoonGauge.h"
#include "ResourcesMgr.h"
#include "SceneMgr.h"
CMoonGauge::CMoonGauge() : m_fMaxGauge(0.f), m_fGauge(0.f)
{
}

CMoonGauge::~CMoonGauge()
{
}

void CMoonGauge::Init()
{
	m_eRenderGroup = RENDER_SORT::BOSSMAIN_UI;

	m_fMaxGauge = 100.f;
	m_fGauge = 0.f;

	m_tInfo.iCX = 80;
	m_tInfo.iCY = 80;
}

int CMoonGauge::Update()
{
	if (m_bDead || CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::Get_Instance()->PHASE1)
	{
		return OBJ_DEAD;
	}
	Update_Rect();
	
	if (m_fGauge > m_fMaxGauge)
	{
		m_fGauge = m_fMaxGauge;
	}


	return OBJ_NOEVENT;
}

void CMoonGauge::Late_Update()
{
}

void CMoonGauge::Render(HDC _DC)
{
	Update_Rect();

	float fFillAmount = m_fGauge / m_fMaxGauge;

	if (0.f > fFillAmount)
		fFillAmount = 0.f;

	m_tRect.right = LONG(m_tInfo.iCX * fFillAmount);

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top
		, m_tRect.right, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CMoonGauge::Release()
{
}
