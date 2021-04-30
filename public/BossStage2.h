#pragma once
#ifndef __BOSSSTAGE2_H__
#define __BOSSSTAGE2_H__

#include "Scene.h"
class CBossStage2 : public CScene
{

public:
	CBossStage2();
	virtual ~CBossStage2();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__BOSSSTAGE1_H__
