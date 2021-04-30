#pragma once

#include "Obj.h"
class CMPbar : public CObj
{
public:
	CMPbar();
	virtual ~CMPbar();

public:
	virtual void Init() override;	
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

