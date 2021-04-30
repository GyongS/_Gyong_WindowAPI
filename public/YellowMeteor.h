#pragma once
#ifndef __YELLOWMETEOR_H__
#define __YELLOWMETEOR_H__

#include "Obj.h"
class CYellowMeteor : public CObj
{
public:
	CYellowMeteor();
	virtual ~CYellowMeteor();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__YELLOWMETEOR_H__

