#pragma once
#ifndef __PHASE1BLUEHP_H__
#define __PHASE1BLUEHP_H__

#include "Obj.h"
class CPhase1BlueHP : public CObj
{

public:
	CPhase1BlueHP();
	virtual ~CPhase1BlueHP();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};
#endif // !__PHASE1BLUEHP_H__