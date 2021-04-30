#pragma once
#ifndef  __MONSTERHPBG_H__
#define __MONSTERHPBG_H__
#include "Obj.h"
class CMonsterHPBG : public CObj
{
public:
	CMonsterHPBG();
	virtual ~CMonsterHPBG();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // ! __MONSTERHPBG_H__


