#pragma once
#ifndef __MONSTERSTAGE_H__
#define __MONSTERSTAGE_H__
#include "Scene.h"
class CMonsterStage : public CScene
{
public:
	CMonsterStage();
	virtual ~CMonsterStage();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	
private:
	void InitFloorRect();
private:
	RECT m_tPortalRect;
};
#endif // !__MONSTERSTAGE_H__