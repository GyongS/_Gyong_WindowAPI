#include "framework.h"
#include "Beholder.h"
#include "Beholderball.h"
#include "ResourcesMgr.h"
#include "BeholderballEx.h"

#include "ObjMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CBeholder::CBeholder() : m_fDelay(0.f), m_eCurState(END), m_ePreState(END), m_iBallCnt(0)
{
}

CBeholder::~CBeholder()
{
	Release();
}

void CBeholder::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/Beholder/Beholder_Start.bmp", L"Beholder_Start");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/Beholder/Beholder_Loop.bmp", L"Beholder_Loop");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/MapPattern/Beholder/Beholder_DEAD.bmp", L"Beholder_DEAD");

	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX = 600;
	m_tInfo.iCY = 300;
	m_fRotation = 0.f;
	m_eCurState = START;
	m_pFrameKey = L"Beholder_Start";	
}

int CBeholder::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	Change_State();	
	Next_State();
	Update_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBeholder::Late_Update()
{
	if (m_eCurState == DEAD && m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_bDead = true;
	}
}

void CBeholder::Render(HDC _DC)
{
	Update_Rect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);
}

void CBeholder::Release()
{
}

void CBeholder::Change_State()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CBeholder::START:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CBeholder::LOOP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CBeholder::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBeholder::Next_State()
{
	if (m_eCurState == START)
	{
		if (m_tFrame.iStartX >= m_tFrame.iEndX - 1)
		{
			m_eCurState = LOOP;
			m_pFrameKey = L"Beholder_Loop";
		}
		
	}
	else if (m_eCurState == LOOP)
	{
		m_fDelay += 1.f;

		if (m_iBallCnt >= 3)
		{
			m_eCurState = DEAD;
			m_pFrameKey = L"Beholder_DEAD";
		}

		if (m_fDelay >= 80.f)
		{
			if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1 ||
				CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
			{
				// 여기서 구슬 쏘기
				for (int i = 0; i < 6; ++i)
				{
					CObj* pObj = CAbstractFactory<CBeholderball>::Create(m_tInfo.fX, m_tInfo.fY, m_fRotation);
					CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_BALL, pObj);
					m_fRotation += (rand() % 20) + 45;
				}
				m_iBallCnt++;
				m_fDelay = 0.f;
			}

			if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
			{
				// 페이즈 3 구슬
				for (int i = 0; i < 6; ++i)
				{
					CObj* pObj = CAbstractFactory<CBeholderballEx>::Create(m_tInfo.fX, m_tInfo.fY, m_fRotation);
					CObjMgr::Get_Instance()->Add_Object(OBJID::MAP_BALL, pObj);
					m_fRotation += (rand() % 20) + 45;
				}
				m_iBallCnt++;
				m_fDelay = 0.f;
			}
		}		
	}

}
