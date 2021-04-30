#pragma once
#ifndef __MONSTERHPBAR_H__
#define __MONSTERHPBAR_H__
#include "Obj.h"
class CMonsterHPbar : public CObj
{
public:
	CMonsterHPbar();
	virtual ~CMonsterHPbar();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__MONSTERHPBAR_H__