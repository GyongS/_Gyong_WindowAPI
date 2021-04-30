#pragma once
#ifndef __ALLOW_H__
#define __ALLOW_H__
#include "Obj.h"
class CAllow :	public CObj
{

public:
	CAllow();
	virtual ~CAllow();

public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	bool m_bCheck;
};
#endif // !__ALLOW_H__