#pragma once
#include "Obj.h"
class CHowlingHit :	public CObj
{
public:
	CHowlingHit();
	virtual ~CHowlingHit();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

