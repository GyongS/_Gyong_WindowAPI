#pragma once
#include "Obj.h"
class CBeholderballEx :	public CObj
{
public:
	CBeholderballEx();
	virtual ~CBeholderballEx();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float m_fDist;
};

