#pragma once
#ifndef __PLAYERDEADUI_H__
#define __PLAYERDEADUI_H__
#include "Obj.h"
class CPlayerDeadUI : public CObj
{
public:
	CPlayerDeadUI();
	virtual ~CPlayerDeadUI();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // __PLAYERDEADUI_H__


