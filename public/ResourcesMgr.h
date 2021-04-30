#pragma once

#ifndef __RESOURCESMGR_H__
#define __RESOURCESMGR_H__

class CResources;
class CResourcesMgr
{
public:
	CResourcesMgr();
	~CResourcesMgr();

public:
	void Insert_Resources(const TCHAR* _pFilePath, const TCHAR* _FrameKey);
	HDC Find_DC(const TCHAR* _FrameKey);
	void Release();

public:
	static CResourcesMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CResourcesMgr;
		}
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CResourcesMgr* m_pInstance;
	map<const TCHAR*, CResources*> m_mapResources;
};
#endif // !__RESOURCESMGR_H__

