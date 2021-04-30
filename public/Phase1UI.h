#pragma once
#ifndef __PHASE1UI_H__
#define __PHASE1UI_H__
#include "Obj.h"
class CPhase1UI : public CObj
{

public:
	CPhase1UI();
	virtual ~CPhase1UI();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PHASE1UI_H__