#pragma once
#ifndef __BOSSSTAGE3_H__
#define __BOSSSTAGE3_H__
#include "Scene.h"
class CBossStage3 :	public CScene
{
public:
	CBossStage3();
	virtual ~CBossStage3();
public:	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__BOSSSTAGE3_H__


