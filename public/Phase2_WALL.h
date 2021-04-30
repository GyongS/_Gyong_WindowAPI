#pragma once
#ifndef __PHASE2WALL_H__
#define __PHASE2WALL_H__
#include "Obj.h"
class CPhase2_WALL : public CObj
{
public:
	enum Phase2_WALL_STATE
	{
		START,
		LOOP,
		DEAD,
		END
	};
public:
	CPhase2_WALL();
	virtual ~CPhase2_WALL();
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
	Phase2_WALL_STATE m_eCurState;
	Phase2_WALL_STATE m_ePreState;

};
#endif // !__PHASE2WALL_H__


