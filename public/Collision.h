#pragma once
#ifndef __COLLISION_H__
#define __COLLISION_H__
#include "Obj.h"
class CCollision : public CObj
{
public:
	CCollision();
	virtual ~CCollision();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__COLLISION_H__