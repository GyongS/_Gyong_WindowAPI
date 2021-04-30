#pragma once
#include "Obj.h"
class CHowlingGailUsed : public CObj
{
public:
	CHowlingGailUsed();
	virtual ~CHowlingGailUsed();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bCheck;
};

