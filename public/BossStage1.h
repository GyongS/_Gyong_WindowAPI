#pragma once

#ifndef __BOSSSTAGE1_H__
#define __BOSSSTAGE1_H__

#include "Scene.h"
class CBossStage1 : public CScene
{

public:
	CBossStage1();
	virtual ~CBossStage1();

public:
	const bool Get_bChangeMap() { return m_bChangeMap; }

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bChangeMap;
};
#endif // !__BOSSSTAGE1_H__

