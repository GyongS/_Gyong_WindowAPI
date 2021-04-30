#pragma once
#ifndef __PHASE3UI_H__
#define __PHASE3UI_H__
#include "Obj.h"
class CPhase3UI : public CObj
{
public:
	CPhase3UI();
	virtual ~CPhase3UI();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PHASE3UI_H__

