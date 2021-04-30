#pragma once


#include "Obj.h"
class CPhase1 : public CObj
{
public:
	enum Phase1_STATE
	{
		IDLE,
		WALK,
		ATTACK1,
		PUSHATTACK,
		BALL_SKILL,
		TELEPORT_START,
		TELEPORT_END,
		GROGGY,
		DEAD,
		END
	};

public:
	CPhase1();
	virtual ~CPhase1();

public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;	
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Take_Damage(int _Damage);

public:
	void Init_HP();
	void MonitorBreakDmg();
	void Set_Block_BlueHP() { m_bBlock_BlueHP = false; }
	void Set_Block_PurpleHP() {m_bBlock_PurpleHP = false; }
	void Set_DeleteBlockHP(bool _bCheck) { m_bDeleteBlockHP = _bCheck; }
	void Set_ShiledSpawnCheck(bool _bCheck) { m_bShiledSpawnCheck = _bCheck; }
	void Set_ShiledTriggerEnter(bool _bCheck) { m_bShiled_TriggerEnter = _bCheck; }
	void Set_ShiledTriggerExit(bool _bCheck) { m_bShiled_TriggerExit = _bCheck; }
	void Set_GroggyState(bool _bCheck) { m_bGroggyState = _bCheck; }
public:
	const float& Get_MaxBlueHP() const { return m_fMaxBlueHP; }
	const float& Get_BlueHP() const { return m_fBlueHP; }
	const float& Get_MaxPurpleHP() const{ return m_fMaxPurpleHP; }
	const float& Get_PurpleHP() const { return m_fPurpleHP; }
	const bool& Get_Block_BlueHP() const { return m_bBlock_BlueHP; }
	const bool& Get_Block_PurpleHP() const { return m_bBlock_PurpleHP; }
	const bool& Get_ShiledSpawnCheck() const { return m_bShiledSpawnCheck; }
	const bool& Get_Shiled_TriggerEnter()const { return m_bShiled_TriggerEnter; }
	const bool& Get_Shiled_TriggerExit() const { return m_bShiled_TriggerExit; }
	const bool& Get_Phase1_DeadCheck() const { return m_bDead; }
private:
	void Change_State();	 
	void WALK_STATE();
	void Check_LeftRight();
	void Update_Block_HP();
	void ATTACK_STATE();
	void ATTACK_PUSH_STATE();
	void SKILL_BALL_STATE();
	void SKILL_TELEPORT_START();
	void SKILL_TELEPORT_END();
	void IDLE_STATE();
	void GROGGY_STATE();
private:
	void Set_State(Phase1_STATE _eState) { m_eCurState = _eState; }
	void Phase1_Pattern();
private:
	Phase1_STATE m_ePreState;
	Phase1_STATE m_eCurState;

	int   m_iPatternNum;
	
	float m_fSaveTargetX;

	float m_fMaxBlueHP;
	float m_fBlueHP;

	float m_fMaxPurpleHP;
	float m_fPurpleHP;
	
	float m_fDelay;
	
	bool  m_bAnimisPlaying;
	bool  m_bCheck_LeftRight;
	bool  m_bBlock_BlueHP;
	bool  m_bBlock_PurpleHP;
	bool  m_bDeleteBlockHP;
	bool  m_bGroggyState;

	bool  m_bChangeState;

	bool  m_bShiledSpawnCheck;
	bool m_bShiled_TriggerEnter;
	bool m_bShiled_TriggerExit;
	bool m_bCreateCol;

};
