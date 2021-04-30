#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

protected:
	bool m_bNextScene;
};
#endif // !__SCENE_H__

