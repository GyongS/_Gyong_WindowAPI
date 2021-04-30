#pragma once
#ifndef __MOONGAUGE_H__
#define __MOONGAUGE_H__
#include "Obj.h"
class CMoonGauge : public CObj
{
public:
	CMoonGauge();
	virtual ~CMoonGauge();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_Gauge(float _InGauge) { m_fGauge += _InGauge; }	
	void Init_Gauge() { m_fGauge = 0; }

public:
	const float& Get_MoonCurGauge() const { return m_fGauge; }
	const float& Get_MoonMaxGauge() const { return m_fMaxGauge; }
private:
	float m_fMaxGauge;
	float m_fGauge;

};
#endif // !__MOONGAUGE_H__

