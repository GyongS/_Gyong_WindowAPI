#pragma once

#ifndef __TITLE_H__
#define __TITLE_H__
#include "Scene.h"
class CTitle : public CScene
{
public:
	CTitle();
	virtual ~CTitle();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};
#endif // !__TITLE_H__

