#pragma once
#ifndef __PHASE3MAINHP_H__
#define __PHASE3MAINHP_H__
#include "Obj.h"
class CPhase3MainHP :	public CObj
{
public:
	CPhase3MainHP();
	virtual ~CPhase3MainHP();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PHASE3MAINHP_H__

