#pragma once
#ifndef __ALLOWHIT_H__
#define __ALLOWHIT_H__
#include "Obj.h"
class CAllowHit : public CObj
{
public:
	CAllowHit();
	virtual ~CAllowHit();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__ALLOWHIT_H__


