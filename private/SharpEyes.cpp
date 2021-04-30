#include "framework.h"
#include "SharpEyes.h"
#include "ResourcesMgr.h"
#include "SharpBuffIcon.h"
#include "ObjMgr.h"
CSharpEyes::CSharpEyes()
{
}

CSharpEyes::~CSharpEyes()
{
}

void CSharpEyes::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Player/SKILL/BUFF/BUFF2.bmp", L"SharpEyes");

	m_eRenderGroup = RENDER_SORT::EFFECT;
	m_pFrameKey = L"SharpEyes";
	m_tInfo.iCX = 225;
	m_tInfo.iCY = 182;

	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 12;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwNextTime = 100;
}

void CSharpEyes::Late_Init()
{
	CObj* pObj = CAbstractFactory<CSharpBuffIcon>::Create(1313, 17);
	CObjMgr::Get_Instance()->Add_Object(OBJID::BUFF, pObj);
}

int CSharpEyes::Update()
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

void CSharpEyes::Late_Update()
{
	if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
}

void CSharpEyes::Render(HDC _DC)
{
	Update_Rect();
	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CSharpEyes::Release()
{
}
