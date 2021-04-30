#include "framework.h"
#include "Phase2_WALL.h"
#include "ResourcesMgr.h"
#include "Phase2.h"
#include "ObjMgr.h"

CPhase2_WALL::CPhase2_WALL() : m_eCurState(END), m_ePreState(END)
{
}

CPhase2_WALL::~CPhase2_WALL()
{
}

void CPhase2_WALL::Init()
{
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/WALL/START.bmp", L"WALL_START");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/WALL/Loop.bmp", L"WALL_Loop");
	CResourcesMgr::Get_Instance()->Insert_Resources(L"../Resources/Will/Phase2/WALL/DEAD.bmp", L"WALL_DEAD");
	m_eRenderGroup = RENDER_SORT::OBJECT;
	m_tInfo.iCX   = 200;
	m_tInfo.iCY = 450;
	m_tInfo.iColX = 100;
	m_tInfo.iColY = 700;
	m_eCurState = START;
	m_pFrameKey = L"WALL_START";
}

int CPhase2_WALL::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	Change_State();
	Next_State();
	Update_Frame();
	Update_CollisionRect();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPhase2_WALL::Late_Update()
{
	if (m_eCurState == DEAD && m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		// 거미줄이 사라졌다는 것을 알려줄 bool 값 하나 필요
		static_cast<CPhase2*>(CObjMgr::Get_Instance()->Get_Phase2())->Set_WallCnt(-1);
		m_bDead = true;
	}
}

void CPhase2_WALL::Render(HDC _DC)
{
	Update_Rect();
	Update_CollisionRect();

	Anim_TransparentBlt(_DC, m_pFrameKey, m_tRect.left, m_tRect.top);

}

void CPhase2_WALL::Release()
{
}

void CPhase2_WALL::Change_State()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CPhase2_WALL::START:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2_WALL::LOOP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 9;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwNextTime = 100;
			break;
		case CPhase2_WALL::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
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

void CPhase2_WALL::Next_State()
{
	if (m_eCurState == START && m_tFrame.iStartX >= m_tFrame.iEndX - 1)
	{
		m_eCurState = LOOP;
		m_pFrameKey = L"WALL_Loop";
	}
	if (m_eCurState == LOOP)
	{
		// 플레이어가 닿으면 사라지고 데미지 줌
	}
}
