#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	enum Monster_STATE
	{
		IDLE,
		WALK,
		ATTACK,
		DEAD,
		END
	};
public:
	CMonster();
	virtual ~CMonster();
public:
	virtual void Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Take_Damage(int _Damage) { m_tStat.fHp -= _Damage; }
	void Set_HitCheck(bool _bCheck) { m_bHitCheck = _bCheck; }
public:
	bool& Get_HitCheck() { return m_bHitCheck; }

private:
	void Change_State();
	void Check_LeftRight();
	void Monster_Pattern();
	void Set_State(Monster_STATE _eState) { m_eCurState = _eState;}
private:
	void IDLE_STATE();
	void WALK_STATE();
	void ATTACK_STATE();

private:
	Monster_STATE m_eCurState;
	Monster_STATE m_ePreState;

private:
	float m_fDelay;
	int   m_iDir;

	bool  m_bAnimisPlaying;
	bool m_bCheck_LeftRight;
	bool m_bHitCheck;
	bool m_bCreateCol;
};
