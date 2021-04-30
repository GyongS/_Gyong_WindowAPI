#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(OBJID::ID _eID, CObj* _pObj);	
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void DeleteID(OBJID::ID _eID);

public:
	CObj* Get_Potion(OBJID::ID _eID);
	CObj* Get_AllowEffect(OBJID::ID _eID);
	CObj* Get_PotionUI() const { return m_listObj[OBJID::POTION_UI].front();}
	CObj* Get_Player() const { return m_listObj[OBJID::PLAYER].front();}
	CObj* Get_Monster() const { return m_listObj[OBJID::MONSTER].back();}
	CObj* Get_Phase1() const { return m_listObj[OBJID::PHASE1].front();}
	CObj* Get_Phase2() const { return m_listObj[OBJID::PHASE2].front();}
	CObj* Get_Phase3() const { return m_listObj[OBJID::PHASE3].front();}
	CObj* Get_Allow()  const { return m_listObj[OBJID::ALLOW].front();}
	CObj* Get_MoonGauge()  const { return m_listObj[OBJID::MOONGAUGE].front();}	
	CObj* Get_MapPattern()  const { return m_listObj[OBJID::MAP_PATTERN].front();}	
	CObj* Get_MoonEffect()  const { return m_listObj[OBJID::MOONGAUGE].back();}
	CObj* Get_BlockHPbar()  const { return m_listObj[OBJID::PHASE1_HP].back();}
	CObj* Get_BlockServeHPbar()  const { return m_listObj[OBJID::PHASE1_HP].back();}
	CObj* Get_Beholder_Eye()  const { return m_listObj[OBJID::BEHOLDER_EYE].front();}
	CObj* Get_Beholder_Shiled()  const { return m_listObj[OBJID::SHILED].front();}
	CObj* Get_MonitorBreak()  const { return m_listObj[OBJID::BOSSSKILL].front();}

	
	CObj* Get_Floor()  const { return m_listObj[OBJID::FLOOR].back();}

	CObj* Get_Target(OBJID::ID _eID, CObj* _pObj);

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	list<CObj*> m_listObj[OBJID::END];
	list<CObj*> m_listRender[RENDER_SORT::END];
	
	static CObjMgr* m_pInstance;

};
#endif // !__OBJMGR_H__

