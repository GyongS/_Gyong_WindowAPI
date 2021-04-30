#pragma once
#ifndef __SKILLBALL_H__
#define __SKILLBALL_H__
#include "Obj.h"
class CSKILLBALL : public CObj
{
public:
	CSKILLBALL();
	virtual ~CSKILLBALL();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bCheck;

private:
	bool m_bHitCheck;
};
#endif // !__SKILLBALL_H__


