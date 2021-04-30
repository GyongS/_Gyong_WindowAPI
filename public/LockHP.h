#pragma once
#ifndef __LOCKHP_H__
#define __LOCKHP_H__
#include "Obj.h"
class CLockHP :	public CObj
{	
public:
	CLockHP();
	virtual ~CLockHP();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__LOCKHP_H__


