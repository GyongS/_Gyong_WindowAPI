#include "framework.h"
#include "MonsterMapFloor.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
CMonsterMapFloor::CMonsterMapFloor()
{
}

CMonsterMapFloor::~CMonsterMapFloor()
{
}

void CMonsterMapFloor::Init()
{
	m_eRenderGroup = RENDER_SORT::BACKGROUND;

}

int CMonsterMapFloor::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonsterMapFloor::Late_Update()
{
}

void CMonsterMapFloor::Render(HDC _DC)
{
	Update_Rect();

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
}

void CMonsterMapFloor::Release()
{
}
