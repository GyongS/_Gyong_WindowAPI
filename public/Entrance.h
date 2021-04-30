#pragma once
#ifndef __ENTRANCE_H__
#define __ENTRANCE_H__

#include "Scene.h"
class CEntrance : public CScene
{
public:
	CEntrance();
	virtual ~CEntrance();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


private:
	RECT m_tPortalRect;
};
#endif // !__ENTRANCE_H__

