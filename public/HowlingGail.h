#pragma once
#include "Obj.h"
class CHowlingGail : public CObj
{
public:
	enum HowlingGail_STATE
	{
	    LOOP,
		DEAD,
		END
	};
public:
	CHowlingGail();
	virtual ~CHowlingGail();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_State(HowlingGail_STATE _eState) { m_eCurState = _eState; }

private:
	void Change_State();
private:
	HowlingGail_STATE m_ePreState;
	HowlingGail_STATE m_eCurState;

private:
	float m_fDelay;

};

