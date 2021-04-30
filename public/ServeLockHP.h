#pragma once
#ifndef __SERVELOCKHP_H__
#define __SERVELOCKHP_H__
#include "Obj.h"
class CServeLockHP : public CObj
{
public:
	CServeLockHP();
	virtual ~CServeLockHP();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__SERVELOCKHP_H__