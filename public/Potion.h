#pragma once
#ifndef __POTION_H__
#define __POTION_H__
#include "Obj.h"
class CPotion : public CObj
{
public:
	CPotion();
	virtual ~CPotion();
public:
	virtual void Init() override;
	virtual void Late_Init() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_JumpCheck(bool _bCheck) { m_bJump = _bCheck; }
	void Set_JumpTime() { m_fJumpTime = 0.f; }

private:
	bool  m_bPickUP;
	bool  m_bPotionUIEnabled;
	bool  m_bJump;
	float m_fJumpY;
	float m_fJumpPower;
	float m_fJumpTime;
};
#endif // !__POTION_H__

