#pragma once
#ifndef __MOONLIGHT_H__
#define __MOONLIGHT_H__

#include "Obj.h"
class CMoonLight :	public CObj
{

public:
	CMoonLight();
	virtual ~CMoonLight();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bAddEffect;
};

#endif // !__MOONLIGHT_H__
