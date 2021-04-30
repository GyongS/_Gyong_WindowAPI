#pragma once
#include "Obj.h"
class CDamageSkin :	public CObj
{
public:
	CDamageSkin();
	virtual ~CDamageSkin();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float m_fDelay;
};

