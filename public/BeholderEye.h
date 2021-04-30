#pragma once
#ifndef __BEHOLDEREYE_H__
#define __BEHOLDEREYE_H__
#include "Obj.h"
class CBeholderEye : public CObj
{
public:
	enum BeholderEye_STATE
	{
		START,
		LOOP,
		DEAD,
		END
	};

public:
	CBeholderEye();
	virtual ~CBeholderEye();

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
	BeholderEye_STATE m_eCurState;
	BeholderEye_STATE m_ePreState;

private:
	float m_fDelay;
};
#endif // !__BEHOLDEREYE_H__


