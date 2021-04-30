#pragma once
#ifndef __PHASE2UI_H__
#define __PHASE2UI_H__
#include "Obj.h"
class CPhase2UI : public CObj
{
public:
	CPhase2UI();
	virtual ~CPhase2UI();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PHASE2UI_H__

