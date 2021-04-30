#pragma once
#ifndef __REDEYEPATTERN_H__
#define __REDEYEPATTERN_H__
#include "Obj.h"
class CRedEyePattern :	public CObj
{
public:
	CRedEyePattern();
	virtual ~CRedEyePattern();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};
#endif // !__REDEYEPATTERN_H__


