#pragma once
#ifndef __SPYDERLEG_H__
#define __SPYDERLEG_H__

#include "Obj.h"
class CSpyderLeg :	public CObj
{
public:
	CSpyderLeg();
	virtual ~CSpyderLeg();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bHitLeg;
};

#endif // !__SPYDERLEG_H__
