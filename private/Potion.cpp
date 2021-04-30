#include "framework.h"
#include "Potion.h"
#include "ResourcesMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "PotionUI.h"
CPotion::CPotion() : m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f), m_bPickUP(false)
{
}

CPotion::~CPotion()
{
}

void CPotion::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Item/Potion_Drop.bmp", L"Potion_Drop");
	m_tInfo.iCX = 32;
	m_tInfo.iCY = 31;
	m_fSpeed = 7.f;
	m_pFrameKey = L"Potion_Drop";
	m_fJumpPower = 15.f;
	m_eRenderGroup = RENDER_SORT::OBJECT;
}

void CPotion::Late_Init()
{
	m_bJump = true;
	m_fJumpY = m_tInfo.fY;
	float fY = static_cast<CObj*>(CObjMgr::Get_Instance()->Get_Floor())->Get_Info().fY;
}

int CPotion::Update()
{
	CObj::Late_Init();

	if (m_bDead)
	{
		if (!m_bPotionUIEnabled)
		{
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_PotionCnt();
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_PickUpPotion();
			static_cast<CPotionUI*>(CObjMgr::Get_Instance()->Get_PotionUI())->Set_FrameKey(L"Potion_Enable");
			m_bPotionUIEnabled = true;
		}
		return OBJ_DEAD;
	}


	RECT rcTemp = {};

	if (m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f);
		m_fJumpTime += 0.25f;		
	}

	if (IntersectRect(&rcTemp, &m_tRect, &m_pTarget->Get_Rect())
		&& CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		m_bPickUP = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPotion::Late_Update()
{
	if (m_bPickUP)
	{
		float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);

		m_fRotation = acosf(fWidth / fDist);

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fRotation *= -1.f;

		m_tInfo.fX += cosf(m_fRotation) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fRotation) * m_fSpeed;
		if (fDist <= 10.f)
		{
			m_bDead = true;
		}
	}
}

void CPotion::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CResourcesMgr::Get_Instance()->Find_DC(m_pFrameKey);

	GdiTransparentBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CPotion::Release()
{
}

