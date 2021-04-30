#pragma once
#ifndef __WHITEEYEPATTERN_H__
#define __WHITEEYEPATTERN_H__
#include "Obj.h"
class CWhiteEyePattern : public CObj
{
public:
	CWhiteEyePattern();
	virtual ~CWhiteEyePattern();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__WHITEEYEPATTERN_H__


