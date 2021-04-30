#pragma once
#include "Obj.h"
class CPhase3 :	public CObj
{
public:
	enum Phase3_STATE
	{
		IDLE,
		DEFAULT_ATTACK1,
		DEFAULT_ATTACK2,
		ATTACK_PUSH,
		WHITE_EYE,
		RED_EYE,
		DEAD,
		END
	};
public:
	CPhase3();
	virtual ~CPhase3();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;	

public:
	void Take_Damage(int _Damage);

private:
	void Set_State(Phase3_STATE _eState) { m_eCurState = _eState; }
	void Phase3_Pattern();
	void Change_State();
	void Check_LeftRight();

private:
	void IDLE_STATE();
	void DEFAULT_ATTACK1_STATE();
	void DEFAULT_ATTACK2_STATE();
	void ATTACK_PUSH_STATE();
	void WHITE_EYE_STATE();
	void RED_EYE_STATE();

private:
	Phase3_STATE m_ePreState;
	Phase3_STATE m_eCurState;

	int m_iPatternNum;
	float m_fDelay;
	float m_fSaveTargetPosX;
	float m_fSpawnPosX;
	bool m_bAnimisPlaying;
	bool m_bCheck_LeftRight;

	bool m_bCheck_PatternLeg;
	bool m_bCreateCol;

};

