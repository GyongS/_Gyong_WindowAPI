#pragma once

#ifndef __ALLOWSHOTEFFECT_H__
#define __ALLOWSHOTEFFECT_H__

#include "Obj.h"
class CAllowShotEffect : public CObj
{
public:
	CAllowShotEffect();
	~CAllowShotEffect();

public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	
public:
	bool& Get_bEndSkill() { return m_bEndSkill; }

private:
	bool m_bEndSkill;
	bool m_bCheck;
	
};
#endif // !__ALLOWSHOTEFFECT_H__

