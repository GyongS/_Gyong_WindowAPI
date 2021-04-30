#pragma once
#ifndef __PURPLEMETEOR_H__
#define __PURPLEMETEOR_H__
#include "Obj.h"
class CPurpleMeteor : public CObj
{
public:
	CPurpleMeteor();
	virtual ~CPurpleMeteor();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__PURPLEMETEOR_H__

