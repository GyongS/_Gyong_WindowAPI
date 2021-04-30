#pragma once
#include "Obj.h"
class CPlayer :	public CObj
{
public:
	enum Player_STATE
	{
		IDLE,
		WALK,
		JUMP,
		ATTACK,
		HOWLINGGAIL,
		DEAD,
		END
	};

public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Take_Damage(int _InDamage) { m_tStat.fHp -= _InDamage; }
	void Init_HP() { m_tStat.fHp = m_tStat.fMaxHp; }
	void Init_MP() { m_tStat.fMp = m_tStat.fMaxMp; }
	void Init_SKillCnt() { m_iSkillCnt = 0; }
	void Set_DamageChange() { m_bChangeDmgSkin = false; }
	void Set_PotionCnt() { m_iPotionCnt += 1; }
	void Set_PickUpPotion() { m_bPickupPotion = true; }
	void Set_JumpCheck(bool _bCheck) { m_bJump = _bCheck; }
	void Set_JumpTime() { m_fJumpTime = 0.f; }
	void Set_GroundCheck(bool _bCheck) { m_bGround = _bCheck; }
	void Set_LegHitCheck(bool _bCheck) { m_bLegHitCheck = _bCheck; }
	void Set_MapLegHitCheck(bool _bCheck) { m_bMapLegHitCheck = _bCheck; }	
	void Set_DeadCheck(bool _bCheck) { m_bCurDead = _bCheck; }
	void Set_SKillHitCheck(bool _bCheck) { m_bSkillHitCheck = _bCheck; }
public:
	const int& Get_PotionCnt() const { return m_iPotionCnt; }
	const bool& Get_GroundCheck() const { return m_bGround; }
	const bool& Get_LegHitCheck() const { return m_bLegHitCheck; }
	const bool& Get_MapLegHitCheck() const { return m_bMapLegHitCheck; }
	const bool& Get_DamageChange() const { return m_bChangeDmgSkin; }
	const bool& Get_SkillHitCheck() const { return m_bSkillHitCheck; }
private:

	template <typename T>
	CObj* Create_Allow()
	{
		return CAbstractFactory<T>::Create(m_tInfo.fX, m_tInfo.fY);
	}
	template <typename T>
	CObj* Create_Effect()
	{
		return CAbstractFactory<T>::Create(m_tInfo.fX, m_tInfo.fY);
	}

	template <typename T>
	CObj* Create_BUFF()
	{
		return CAbstractFactory<T>::Create(m_tInfo.fX, m_tInfo.fY - 200);
	}	
private:
	void Jumping();
	void DoubleJump();
	void OffSet();
	void Stop_Move();
	void Key_Check();
	void Change_State();
	void Allow_Shot();
private:
	Player_STATE	m_ePreState;
	Player_STATE	m_eCurState;
	int     m_iJumpCnt;
	int     m_iPotionCnt;
	int     m_iSkillCnt;
	bool	m_bJump;
	bool    m_bPickupPotion;
	bool    m_bGround;
	float	m_fJumpPower;
	float	m_fJumpTime;
	float	m_fJumpY;
	float   m_fDelay;
	float   m_fSkillDelay;

private:
	bool m_bLegHitCheck;
	bool m_bSkillHitCheck;
	bool m_bMapLegHitCheck;
	bool m_bCurDead;
	bool m_bChangeDmgSkin;
	bool m_UsedMapleWarrior;
	bool m_UsedSharpEyes;
};
