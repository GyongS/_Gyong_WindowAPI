#include "framework.h"
#include "ResourcesMgr.h"
#include "Resources.h"

CResourcesMgr* CResourcesMgr::m_pInstance = nullptr;

CResourcesMgr::CResourcesMgr()
{
}

CResourcesMgr::~CResourcesMgr()
{
	Release();
}

void CResourcesMgr::Insert_Resources(const TCHAR* _pFilePath, const TCHAR* _FrameKey)
{
	auto&& iter = find_if(m_mapResources.begin(), m_mapResources.end(), CStrCmp(_FrameKey));

	if (m_mapResources.end() == iter)
	{
		CResources* pTemp = new CResources;
		pTemp->Load_Resources(_pFilePath);
		m_mapResources.emplace(_FrameKey, pTemp);
	}

}

HDC CResourcesMgr::Find_DC(const TCHAR* _FrameKey)
{
	auto&& iter = find_if(m_mapResources.begin(), m_mapResources.end(), CStrCmp(_FrameKey));

	if (m_mapResources.end() == iter)
	{
		return nullptr;
	}

	return iter->second->Get_DC();
}

void CResourcesMgr::Release()
{
	for (auto& pair : m_mapResources)
	{
		SAFE_DELETE(pair.second);
	}

	m_mapResources.clear();
}
