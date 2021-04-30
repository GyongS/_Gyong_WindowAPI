#pragma once
#include "Obj.h"
class CUIBackGround : public CObj
{
public:
	CUIBackGround();
	virtual ~CUIBackGround();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
