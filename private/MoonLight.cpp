#include "framework.h"
#include "MoonLight.h"
#include "MoonGauge.h"
#include "MoonCover.h"
#include "MoonEffect.h"
#include "ObjMgr.h"
#include "ResourcesMgr.h"

CMoonLight::CMoonLight() : m_bAddEffect(false)
{
}

CMoonLight::~CMoonLight()
{
}

void CMoonLight::Init()
{
	m_eRenderGroup = RENDER_SORT::BOSSMAIN_UI;

	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_Monnlight/MoonLight_Effect.bmp", L"MoonLight_Effect");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_Monnlight/Moonlight_base.bmp", L"Moonlight_base");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_Monnlight/Moonlight_cover.bmp", L"Moonlight_cover");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/UI/Will_Monnlight/Moonlight_gauge.bmp", L"Moonlight_gauge");

	m_tInfo.fX = 80;
	m_tInfo.fY = 200;
	m_tInfo.iCX = 104;
	m_tInfo.iCY = 104;

	CObj* pObj = CAbstractFactory<CMoonGauge>::Create(80, 200);
	pObj->Set_FrameKey(L"Moonlight_gauge");
	CObjMgr::Get_Instance()->Add_Object(OBJID::MOONGAUGE, pObj);

	pObj = CAbstractFactory<CMoonCover>::Create(80, 200);
	pObj->Set_FrameKey(L"Moonlight_cover");
	CObjMgr::Get_Instance()->Add_Object(OBJID::MAINUI, pObj);
}

int CMoonLight::Update()
{
	if (dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Get_MoonCurGauge() >= 100.f && !m_bAddEffect)
	{
		CObj* pObj = CAbstractFactory<CMoonEffect>::Create(80, 200);
		pObj->Set_FrameKey(L"MoonLight_Effect");
		CObjMgr::Get_Instance()->Add_Object(OBJID::MOONGAUGE, pObj);
		m_bAddEffect = true;
	}
	else if (dynamic_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Get_MoonCurGauge() < 100.f)
	{
		m_bAddEffect = false;
	}
	

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMoonLight::Late_Update()
{
}

void CMoonLight::Render(HDC _DC)
{
	Update_Rect();

	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(L"Moonlight_base");

	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CMoonLight::Release()
{
}
