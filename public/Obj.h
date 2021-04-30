#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Init() = 0;
	virtual void Late_Init();
	virtual int  Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void Set_Scale(float _cx, float _cy) { m_tInfo.iCX = _cx; m_tInfo.iCY = _cy; }
	void Set_CollisionScale(float _cx, float _cy) { m_tInfo.iColX = _cx; m_tInfo.iColY = _cy; }
	void Set_Dead() { m_bDead = true; }
	void Set_Rotation(float _fAngle) { m_fRotation = _fAngle; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_PosX(float _x) { m_tInfo.fX += _x; }
	void Set_PosY(float _y) { m_tInfo.fY += _y; }
	void Set_FrameKey(const TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	
public:
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }
	const RECT& Get_CollisionRect() const { return m_tCollisionRect; }
	const STAT& Get_Stat() const { return m_tStat; }
	const int& Get_DrawID() const { return m_iDrawID; }
	const bool& Get_bRight() const { return m_bRight; }

	const RENDER_SORT::ID Get_Group() const { return m_eRenderGroup; }


protected:
	void Update_Rect();
	void Update_CollisionRect();
	void Update_Frame();
	void Update_FrameLoopEnd();
	void Update_FrameLoop();
	void Update_PressingEnd();

	void Reverse_Bmp(HDC _RenderDC, const TCHAR* _InFrameKey, const TCHAR* _InStretch, bool _bReverseCheck , int _Rect_L, int _Rect_T);
	void Anim_TransparentBlt(HDC _RenderDC, const TCHAR* _InFrameKey, int _Rect_L, int _Rect_T);

	RECT m_tRect;
	RECT m_tCollisionRect;

	INFO m_tInfo;
	STAT m_tStat;

	FRAME m_tFrame;

	float m_fSpeed;
	float m_fRotation;
	bool  m_bDead;
	bool  m_bRight;
	bool  m_bLate_Init;

	RENDER_SORT::ID		m_eRenderGroup;
	const TCHAR*    m_pFrameKey;
	const TCHAR*    m_pFrameKey_Right;

	const TCHAR*    m_pStretch;
	int				m_iDrawID;

	const CObj* m_pTarget;
};
#endif // !__OBJ_H__

