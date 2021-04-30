#pragma once
#ifndef __PHASE2BALL_H__
#define __PHASE2BALL_H__
#include "Obj.h"
class CPhase2Ball :	public CObj
{
public:
	CPhase2Ball();
	virtual ~CPhase2Ball();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bCheck;
};
#endif // !__PHASE2BALL_H__

