#pragma once
#ifndef __BEHOLDERBALL_H__
#define __BEHOLDERBALL_H__
#include "Obj.h"
class CBeholderball : public CObj
{
public:
	CBeholderball();
	virtual ~CBeholderball();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float m_fDist;

};
#endif // !__BEHOLDERBALL_H__

