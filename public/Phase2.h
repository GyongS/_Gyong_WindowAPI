#pragma once
#include "Obj.h"
class CPhase2 :	public CObj
{
public:
	enum Phase2_STATE
	{
		IDLE,
		WALK,
		DEFAULT_ATTACK1,
		ATTACK_PUSH,
		ATTACK_FAKE,
		DEFAULT_ATTACK2,
		SKILL_WALL,
		SKILL_BALL,
		DEAD,
		END
	};

public:
	CPhase2();
	virtual ~CPhase2();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	void Take_Damage(int _Damage);
	void Set_WallCnt(int _Cnt) { m_WallCnt += _Cnt; }

private:
	void Set_State(Phase2_STATE _eState) { m_eCurState = _eState; }
	void Phase2_Pattern();
	void Change_State();
	void Check_LeftRight();

private:
	void IDLE_STATE();
	void WALK_STATE();
	void DEFAULT_ATTACK1_STATE();
	void DEFAULT_ATTACK2_STATE();
	void ATTACK_PUSH_STATE();
	void ATTACK_FAKE_STATE();
	void SKILL_BALL_STATE();
	void SKILL_WALL_STATE();	

private:
	Phase2_STATE m_ePreState;
	Phase2_STATE m_eCurState;


	int   m_iPatternNum;
	float m_fDelay;
	bool  m_bAnimisPlaying;
	bool  m_bCheck_LeftRight;
	bool  m_bCreateCol;
	int m_WallCnt;
};

