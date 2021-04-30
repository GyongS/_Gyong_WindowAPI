#pragma once
#ifndef __BEHOLDER_H__
#define __BEHOLDER_H__

#include "Obj.h"
class CBeholder : public CObj
{
public:
	enum Beholder_STATE
	{
		START,
		LOOP,
		DEAD,
		END
	};

public:
	CBeholder();
	virtual ~CBeholder();

public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	void Change_State();
	void Next_State();

private:
	float m_fDelay;
	int   m_iBallCnt;
	Beholder_STATE m_eCurState;
	Beholder_STATE m_ePreState;
};
#endif // !__BEHOLDER_H__