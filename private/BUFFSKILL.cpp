#include "framework.h"
#include "BUFFSKILL.h"
#include "ResourcesMgr.h"
#include "MapleBuffIcon.h"
#include "ObjMgr.h"
CBUFFSKILL::CBUFFSKILL()
{
}

CBUFFSKILL::~CBUFFSKILL()
{
}

void CBUFFSKILL::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/BUFF/BUFF1.bmp", L"Maplebrave");

	m_eRenderGroup = RENDER_SORT::EFFECT;
	m_pFrameKey = L"Maplebrave";
	m_tInfo.iCX = 272;
	m_tInfo.iCY = 457;

	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 21;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 50;
}

void CBUFFSKILL::Late_Init()
{
	CObj* pObj = CAbstractFactory<CMapleBuffIcon>::Create(1345, 17);
	CObjMgr::Get_Instance()->Add_Object(OBJID::BUFF,pObj);
}

int CBUFFSKILL::Update()
{
	CObj::Late_Init();
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBUFFSKILL::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
}

void CBUFFSKILL::Render(HDC _DC)
{
	Update_Rect();
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CBUFFSKILL::Release()
{
}
