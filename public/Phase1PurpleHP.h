#pragma once
#ifndef __PHASE1PURPLEHP_H__
#define __PHASE1PURPLEHP_H__
#include "Obj.h"
class CPhase1PurpleHP :	public CObj
{
public:
	CPhase1PurpleHP();
	virtual ~CPhase1PurpleHP();

public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PHASE1PURPLEHP_H__