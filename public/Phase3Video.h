#pragma once
#include "Scene.h"
class CPhase3Video : public CScene
{
public:
	CPhase3Video();
	virtual ~CPhase3Video();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	HWND m_hVideo;
};

