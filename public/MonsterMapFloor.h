#pragma once
#ifndef __MONSTERMAPFLOOR_H__
#define __MONSTERMAPFLOOR_H__

#include "Obj.h"
class CMonsterMapFloor : public CObj
{
public:
	CMonsterMapFloor();
	virtual ~CMonsterMapFloor();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__MONSTERMAPFLOOR_H__
