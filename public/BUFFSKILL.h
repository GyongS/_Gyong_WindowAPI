#pragma once
#include "Obj.h"
class CBUFFSKILL :	public CObj
{
public:
	CBUFFSKILL();
	virtual ~CBUFFSKILL();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

