#pragma once
#ifndef __POTIONUI_H__
#define __POTIONUI_H__

#include "Obj.h"
class CPotionUI : public CObj
{
public:
	CPotionUI();
	virtual ~CPotionUI();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__POTIONUI_H__

