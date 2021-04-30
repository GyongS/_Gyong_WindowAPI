#pragma once

#include "Obj.h"
class CHPbar : public CObj
{
public:
	CHPbar();
	virtual ~CHPbar();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


};
