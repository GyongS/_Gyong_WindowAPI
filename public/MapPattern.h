#pragma once

#ifndef __MAPPATTERN_H__
#define __MAPPATTERN_H__
#include "Obj.h"
class CMapPattern : public CObj
{
public:
	CMapPattern();
	virtual ~CMapPattern();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_SpawnBeholderEye(bool _bCheck) { m_bSpawnBeholderEye = _bCheck; }
	void Set_SpawnMonitorBreak(bool _bCheck) { m_bSpawnMonitorBreak = _bCheck; }

private:
	void PATTERN_SPYDERLEG();
	void PATTERN_BEHOLDER();
	void PATTERN_BEHOLDER_EYE();
private:
	float m_fSpyderLegDelay;
	float m_fBeholderDelay;
	float m_fMonitorBreakDelay;

	bool  m_bSpawnBeholderEye;
	bool  m_bSpawnMonitorBreak;
};
#endif // !__MAPPATTERN_H__