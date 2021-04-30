#pragma once
#ifndef __EFFECTMGR_H__
#define __EFFECTMGR_H__

class CEffect;
class CEffectMgr
{
public:
	CEffectMgr();
	~CEffectMgr();

public:
	static CEffectMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEffectMgr;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}


private:
	static CEffectMgr* m_pInstance;
};

#endif // !__EFFECTMGR_H__

