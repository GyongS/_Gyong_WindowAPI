#include "framework.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID::ID _eID, CObj* _pObj)
{
	m_listObj[_eID].emplace_back(_pObj);
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto&& iter = m_listObj[i].begin(); iter != m_listObj[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}	

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
	{
		CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::ALLOW]);
		CCollisionMgr::Collision_RectEx(m_listObj[OBJID::FLOOR], m_listObj[OBJID::PLAYER]);
		CCollisionMgr::Collision_RectEx(m_listObj[OBJID::FLOOR], m_listObj[OBJID::ITEM]);
		CCollisionMgr::Collision_Will_ATTACK(m_listObj[OBJID::MONSTER_ATTACK], m_listObj[OBJID::PLAYER]);
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1)
	{
		CCollisionMgr::Collision_Rect(m_listObj[OBJID::PHASE1], m_listObj[OBJID::ALLOW]);
		CCollisionMgr::Collision_Howling(m_listObj[OBJID::PHASE1], m_listObj[OBJID::HOWLING]);
		CCollisionMgr::Collision_BeholderEye(m_listObj[OBJID::BEHOLDER_EYE], m_listObj[OBJID::ALLOW]);
		CCollisionMgr::Collision_PurpleMeteor(m_listObj[OBJID::PLAYER], m_listObj[OBJID::PURPLE_METEOR]);
		CCollisionMgr::Collision_YellowMeteor(m_listObj[OBJID::PLAYER], m_listObj[OBJID::YELLOW_METEOR]);
		CCollisionMgr::Collision_Shiled(m_listObj[OBJID::SHILED], m_listObj[OBJID::PLAYER]);
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
	{
		CCollisionMgr::Collision_Rect(m_listObj[OBJID::PHASE2], m_listObj[OBJID::ALLOW]);
		CCollisionMgr::Collision_Howling(m_listObj[OBJID::PHASE2], m_listObj[OBJID::HOWLING]);

		CCollisionMgr::Collision_Will_Wall(m_listObj[OBJID::PLAYER], m_listObj[OBJID::WILL_WALL]);
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
	{
		CCollisionMgr::Collision_Rect(m_listObj[OBJID::PHASE3], m_listObj[OBJID::ALLOW]);
		CCollisionMgr::Collision_Howling(m_listObj[OBJID::PHASE3], m_listObj[OBJID::HOWLING]);
	}
	CCollisionMgr::Collision_Will_Push(m_listObj[OBJID::WILL_PUSH], m_listObj[OBJID::PLAYER]);
	CCollisionMgr::Collision_Will_ATTACK(m_listObj[OBJID::WILL_ATTACK], m_listObj[OBJID::PLAYER]);
	CCollisionMgr::Collision_Will_Ball(m_listObj[OBJID::PLAYER], m_listObj[OBJID::WILL_BALL]);
	CCollisionMgr::Collision_Will_WhiteRedLeg(m_listObj[OBJID::PLAYER], m_listObj[OBJID::RED_LEG]);
	CCollisionMgr::Collision_Will_WhiteRedLeg(m_listObj[OBJID::PLAYER], m_listObj[OBJID::WHITE_LEG]);
	CCollisionMgr::Collision_Will_MapLeg(m_listObj[OBJID::PLAYER], m_listObj[OBJID::SPYDERLEG]);
	CCollisionMgr::Collision_Will_MapBall(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MAP_BALL]);
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update();

			if (m_listObj[i].empty())
				break;

			RENDER_SORT::ID eID = pObj->Get_Group();
			m_listRender[eID].emplace_back(pObj);
		}
	}
}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < RENDER_SORT::END; ++i)
	{
		// 높이가 더 작은 오브젝트부터 출력
		if (RENDER_SORT::OBJECT == i)
		{
			m_listRender[i].sort(CompareY<CObj*>);
		}

		// 크기가 더 작은 UI부터 출력
		if (RENDER_SORT::UI == i)
		{
			m_listRender[i].sort(LessCompareCX<CObj*>);
		}

		// 크기가 더 큰 UI부터 출력
		if (RENDER_SORT::BOSSMAIN_UI == i)
		{
			m_listRender[i].sort(GreaterCompareCY<CObj*>);
		}	

		for (auto& pObj : m_listRender[i])
		{
			pObj->Render(_DC);
		}
		m_listRender[i].clear();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

void CObjMgr::DeleteID(OBJID::ID _eID)
{
	if (m_listObj[_eID].empty())
		return;
	for_each(m_listObj[_eID].begin(), m_listObj[_eID].end(), Safe_Delete<CObj*>);
	m_listObj[_eID].clear();
}

CObj* CObjMgr::Get_Potion(OBJID::ID _eID)
{
	CObj* pTargat = nullptr;
	if (m_listObj[_eID].empty())
		return nullptr;

	for (auto& pObj : m_listObj[_eID])
	{
		pTargat = pObj;
	}
	return pTargat;
}

CObj* CObjMgr::Get_AllowEffect(OBJID::ID _eID)
{
	CObj* pTargat = nullptr;
	if (m_listObj[_eID].empty())
		return nullptr;

	for (auto& pObj : m_listObj[_eID])
	{
		pTargat = pObj;
	}
	return pTargat;
}

CObj* CObjMgr::Get_Target(OBJID::ID _eID, CObj* _pObj)
{
	CObj* pTarget = nullptr;
	float	fDis = 0.f;

	for (auto& pObj : m_listObj[_eID])
	{
		float fX = pObj->Get_Info().fX - _pObj->Get_Info().fX;
		float fY = pObj->Get_Info().fY - _pObj->Get_Info().fY;
		float fDia = sqrtf(fX * fX + fY * fY);

		if (fDis > fDia || !pTarget)
		{
			fDis = fDia;
			pTarget = pObj;
		}
	}

	return pTarget;
}
