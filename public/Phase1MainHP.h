#pragma once
#ifndef __PHASEMAINHP_H__
#define __PHASEMAINHP_H__

#include "Obj.h"
class CPhase1MainHP : public CObj
{

public:
	CPhase1MainHP();
	virtual ~CPhase1MainHP();

public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PHASEMAINHP_H__