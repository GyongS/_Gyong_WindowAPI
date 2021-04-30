#pragma once

#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
	static bool Check_RectPush(CObj* _Dst, CObj* _Src, float* _x, float* _y);
	static bool Check_RectEx(CObj* _Dst, CObj* _Src, float* _x, float* _y);
	static bool Check_ColRect(CObj* _Dst, CObj* _Src);
	static bool Check_ColRectEx(CObj* _Dst, CObj* _Src);
	
public:
	static void Collision_Howling(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_YellowMeteor(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_WhiteRedLeg(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_Ball(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_MapLeg(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_MapBall(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_Wall(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_ATTACK(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_MONSTER_ATTACK(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Will_Push(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Shiled(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_PurpleMeteor(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_BeholderEye(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);

};

#endif // !__COLLISIONMGR_H__


