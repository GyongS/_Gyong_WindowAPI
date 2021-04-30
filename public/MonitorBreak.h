#pragma once
#ifndef __MONITORBREAK_H__
#define __MONITORBREAK_H__
#include "Obj.h"
class CMonitorBreak : public CObj
{
public:
	CMonitorBreak();
	virtual ~CMonitorBreak();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bCheck;
};
#endif // !__MONITORBREAK_H__