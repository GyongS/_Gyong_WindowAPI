#include "framework.h"
#include "Collision.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

void CCollision::Init()
{
	m_eRenderGroup = RENDER_SORT::OBJECT;
}

int CCollision::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_CollisionRect();

	return OBJ_NOEVENT;
}

void CCollision::Late_Update()
{

}

void CCollision::Render(HDC _DC)
{
	Update_CollisionRect();
	//Rectangle(_DC, m_tCollisionRect.left, m_tCollisionRect.top, m_tCollisionRect.right, m_tCollisionRect.bottom);
}

void CCollision::Release()
{
}
