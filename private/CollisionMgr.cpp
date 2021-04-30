#include "framework.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Allow.h"
#include "AllowHit.h"
#include "Phase1.h"
#include "Player.h"
#include "YellowMeteor.h"
#include "PurpleMeteor.h"
#include "MoonGauge.h"
#include "BeholderShiled.h"
#include "BeholderEye.h"
#include "BeholderShiled.h"
#include "SceneMgr.h"
#include "Phase2.h"
#include "Phase3.h"
#include "Monster.h"
#include "Potion.h"
#include "SoundMgr.h"
#include "DamageSkin.h"
#include "HowlingHit.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fY = _Dst->Get_Info().fY - _Src->Get_Info().fY;

	// 피타고라스 정리
	float fDia = sqrtf(fX * fX + fY * fY);


	// 두 반지름의 합
	float fDist = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);

	return fDia <= fDist;
}

bool CCollisionMgr::Check_ColRect(CObj* _Dst, CObj* _Src)
{
	float fDistX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fDistY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fCX = (float)((_Dst->Get_Info().iColX + _Src->Get_Info().iCX) >> 1);
	float fCY = (float)((_Dst->Get_Info().iColY + _Src->Get_Info().iCY) >> 1);

	if (fDistX < fCX && fDistY < fCY)
	{		
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_ColRectEx(CObj* _Dst, CObj* _Src)
{
	float fDistX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fDistY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fCX = (float)((_Dst->Get_Info().iColX + _Src->Get_Info().iColX) >> 1);
	float fCY = (float)((_Dst->Get_Info().iColY + _Src->Get_Info().iColY) >> 1);

	if (fDistX < fCX && fDistY < fCY)
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_RectPush(CObj* _Dst, CObj* _Src, float* _x, float* _y)
{
	float fDistX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fDistY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fCX = (float)((_Dst->Get_Info().iColX + _Src->Get_Info().iColX) >> 1);
	float fCY = (float)((_Dst->Get_Info().iColY + _Src->Get_Info().iColY) >> 1);

	if (fDistX < fCX && fDistY < fCY)
	{
		*_x = fCX - fDistX;
		*_y = fCY - fDistY;
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_RectEx(CObj* _Dst, CObj* _Src, float* _x, float* _y)
{
	float fDistX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fDistY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fCX = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iColX) >> 1);
	float fCY = (float)((_Dst->Get_Info().iCY + _Src->Get_Info().iColY) >> 1);

	if (fDistX < fCX && fDistY < fCY)
	{
		*_x = fCX - fDistX;
		*_y = fCY - fDistY;
		return true;
	}
	return false;
}

void CCollisionMgr::Collision_Howling(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	int iDamage = static_cast<CObj*>(CObjMgr::Get_Instance()->Get_Player())->Get_Stat().iDamage;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Hit.mp3", CSoundMgr::HOWLINGGAIL_HIT);
					CSoundMgr::Get_Instance()->PlaySound(L"ALLOWHit.mp3", CSoundMgr::MONSTER_HIT);
					if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_SkillHitCheck())
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();
						static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Take_Damage(iDamage + rand() % 50 * 5);
						CObj* pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE1, Src)->Get_Info().fX
							, CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE1, Src)->Get_Info().fY - 100);
						CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

						pObj = CAbstractFactory<CHowlingHit>::Create(
							CObjMgr::Get_Instance()->Get_Phase1()->Get_Info().fX
							, CObjMgr::Get_Instance()->Get_Phase1()->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
						static_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Set_Gauge(3.f);

						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SKillHitCheck(false);
					}
				}
				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Hit.mp3", CSoundMgr::HOWLINGGAIL_HIT);
					CSoundMgr::Get_Instance()->PlaySound(L"ALLOWHit.mp3", CSoundMgr::MONSTER_HIT);
					if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_SkillHitCheck())
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();
						static_cast<CPhase2*>(CObjMgr::Get_Instance()->Get_Phase2())->Take_Damage(iDamage + rand() % 50 * 5);

						CObj* pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE2, Src)->Get_Info().fX
							, CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE2, Src)->Get_Info().fY - 100);
						CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

						pObj = CAbstractFactory<CHowlingHit>::Create(
							CObjMgr::Get_Instance()->Get_Phase2()->Get_Info().fX
							, CObjMgr::Get_Instance()->Get_Phase2()->Get_Info().fY);
						CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SKillHitCheck(false);
					}
				}

				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Hit.mp3", CSoundMgr::HOWLINGGAIL_HIT);
					CSoundMgr::Get_Instance()->PlaySound(L"ALLOWHit.mp3", CSoundMgr::MONSTER_HIT);
					if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_SkillHitCheck())
					{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();
					static_cast<CPhase3*>(CObjMgr::Get_Instance()->Get_Phase3())->Take_Damage(iDamage + rand() % 50 * 5);

					CObj* pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE3, Src)->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE3, Src)->Get_Info().fY - 100);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

					pObj = CAbstractFactory<CHowlingHit>::Create(
						CObjMgr::Get_Instance()->Get_Phase3()->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Phase3()->Get_Info().fY);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SKillHitCheck(false);
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	int iDamage = static_cast<CObj*>(CObjMgr::Get_Instance()->Get_Player())->Get_Stat().iDamage;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRect(Dst, Src))
			{				
				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
				{					
					static_cast<CMonster*>(CObjMgr::Get_Instance()->Get_Target(OBJID::MONSTER, Src))->Take_Damage(iDamage);
					static_cast<CMonster*>(CObjMgr::Get_Instance()->Get_Target(OBJID::MONSTER, Src))->Set_HitCheck(true);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();

					Src->Set_Dead();
					CObj* pObj = CAbstractFactory<CAllowHit>::Create(
						CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fY);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

					pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::MONSTER, Src)->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Target(OBJID::MONSTER, Src)->Get_Info().fY);

					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

				}

				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE1)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Hit.mp3", CSoundMgr::HOWLINGGAIL_HIT);
					CSoundMgr::Get_Instance()->PlaySound(L"ALLOWHit.mp3", CSoundMgr::MONSTER_HIT);

					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();
					static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Take_Damage(iDamage);
					Src->Set_Dead();
					CObj* pObj = CAbstractFactory<CAllowHit>::Create(
						CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fY);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

					pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE1, Src)->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE1, Src)->Get_Info().fY - 100);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

					static_cast<CMoonGauge*>(CObjMgr::Get_Instance()->Get_MoonGauge())->Set_Gauge(1.f);
				}
				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Hit.mp3", CSoundMgr::HOWLINGGAIL_HIT);
					CSoundMgr::Get_Instance()->PlaySound(L"ALLOWHit.mp3", CSoundMgr::MONSTER_HIT);

					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();
					static_cast<CPhase2*>(CObjMgr::Get_Instance()->Get_Phase2())->Take_Damage(iDamage);
					Src->Set_Dead();
					CObj* pObj = CAbstractFactory<CAllowHit>::Create(
						CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fY);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

					pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE2, Src)->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE2, Src)->Get_Info().fY - 100);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

				}

				if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"HowlingGail_Hit.mp3", CSoundMgr::HOWLINGGAIL_HIT);
					CSoundMgr::Get_Instance()->PlaySound(L"ALLOWHit.mp3", CSoundMgr::MONSTER_HIT);

					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_DamageChange();
					static_cast<CPhase3*>(CObjMgr::Get_Instance()->Get_Phase3())->Take_Damage(iDamage);
					Src->Set_Dead();
					CObj* pObj = CAbstractFactory<CAllowHit>::Create(
						CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fY);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);

					pObj = CAbstractFactory<CDamageSkin>::Create(CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE3, Src)->Get_Info().fX
						, CObjMgr::Get_Instance()->Get_Target(OBJID::PHASE3, Src)->Get_Info().fY - 100);
					CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
				}
				/////////////////////////////////////////////////////////
			}
		}
	}
}

void CCollisionMgr::Collision_YellowMeteor(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRect(Dst, Src))
			{
				if (!static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Get_ShiledSpawnCheck())
				{
					CObj* pObj = CAbstractFactory<CBeholderShiled>::Create(700, 580);
					CObjMgr::Get_Instance()->Add_Object(OBJID::SHILED, pObj);
					static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledSpawnCheck(true);
				}				
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Will_WhiteRedLeg(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				if (!static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_LegHitCheck())
				{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(30);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_LegHitCheck(true);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Will_Ball(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(20);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Will_MapLeg(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MapLegHitCheck())
				{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(10);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MapLegHitCheck(false);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Will_MapBall(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(5);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Will_Wall(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(50);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Will_ATTACK(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(20);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_MONSTER_ATTACK(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRectEx(Dst, Src))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(5);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Will_Push(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_RectPush(Dst, Src, &fX, &fY))
			{
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Src->Set_PosX(fX);
					else
						Src->Set_PosX(-fX);

					if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
					{
						if (Dst->Get_Info().fX < Src->Get_Info().fX)
							Src->Set_PosX(fX * 2);
						else
							Src->Set_PosX(-fX * 2);
					}
			}
		}
	}
}

void CCollisionMgr::Collision_Shiled(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRect(Dst, Src))
			{
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledTriggerEnter(true);
			}
			else if(!Check_ColRect(Dst, Src))
			{
				static_cast<CPhase1*>(CObjMgr::Get_Instance()->Get_Phase1())->Set_ShiledTriggerEnter(false);
			}
		}
	}
}

void CCollisionMgr::Collision_PurpleMeteor(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRect(Dst, Src))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Take_Damage(10);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_BeholderEye(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_ColRect(Dst, Src))
			{
				// 천공의 노래에 맞았을 때
				Src->Set_Dead();
				CObj* pObj = CAbstractFactory<CAllowHit>::Create(
					CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fX
					, CObjMgr::Get_Instance()->Get_Allow()->Get_Info().fY);
				CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);


				float fX = rand() % 500;

				for (int i = 0; i < rand() % 3; ++i)
				{
					CObj* pObj = CAbstractFactory<CYellowMeteor>::Create((100 + fX) + fX, 50);
					CObjMgr::Get_Instance()->Add_Object(OBJID::YELLOW_METEOR, pObj);
					for (int j = 0; j < rand() % 3; ++j)
					{
						CObj* pObj = CAbstractFactory<CPurpleMeteor>::Create((100 + fX) + fX, 50);
						CObjMgr::Get_Instance()->Add_Object(OBJID::PURPLE_METEOR, pObj);
					}					
				}		
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f, fY = 0.f;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_RectEx(Dst, Src, &fX, &fY))
			{
				if (fX < fY)
				{
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Src->Set_PosX(fX);
					else
						Src->Set_PosX(-fX);
				}
				else
				{
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
					{
						Src->Set_PosY(fY);
					}
					else
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_JumpCheck(false);
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_JumpTime();
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GroundCheck(true);

						if (CObjMgr::Get_Instance()->Get_Potion(OBJID::ITEM) != nullptr)
						{
							static_cast<CPotion*>(CObjMgr::Get_Instance()->Get_Potion(OBJID::ITEM))->Set_JumpCheck(false);
							static_cast<CPotion*>(CObjMgr::Get_Instance()->Get_Potion(OBJID::ITEM))->Set_JumpTime();
						}
 						Src->Set_PosY(-fY);
					}
				}			
			}
		/*	else if(!Check_RectEx(Dst, Src, &fX, &fY))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GroundCheck(false);
			}			*/
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}
