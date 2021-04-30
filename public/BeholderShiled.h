#pragma once
#ifndef __BEHOLDERSHILED_H__
#define __BEHOLDERSHILED_H__

#include "Obj.h"
class CBeholderShiled :	public CObj
{
public:
	CBeholderShiled();
	virtual ~CBeholderShiled();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__BEHOLDERSHILED_H__

