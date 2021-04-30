#pragma once

#ifndef __MOONEFFECT_H__
#define __MOONEFFECT_H__

#include "Obj.h"
class CMoonEffect : public CObj
{
public:
	CMoonEffect();
	virtual ~CMoonEffect();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // __MOONEFFECT_H__

