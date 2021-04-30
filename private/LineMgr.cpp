#include "framework.h"
#include "LineMgr.h"
#include "Line.h"
#include "SceneMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	Release();

}

CLineMgr::~CLineMgr()
{
}

void CLineMgr::Init()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->MONSTERSTAGE)
		Load_Line(L"../Data/MonsterMAP.dat");

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->ENTRANCE)
		Load_Line(L"../Data/Line.dat");

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE2)
		Load_Line(L"../Data/Phase2Line.dat");

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::Get_Instance()->PHASE3)
		Load_Line(L"../Data/Phase3Line.dat");	
}

void CLineMgr::Render(HDC _DC)
{
	for (auto& pLine : m_listLine)
	{
		pLine->Render(_DC);
	}
}

void CLineMgr::Release()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}

bool CLineMgr::Collision_Line(float _x, float* _y)
{
	CLine* pTarget = nullptr;

	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_Info().tLeftPos.fX < _x
			&& pLine->Get_Info().tRightPos.fX > _x)
		{
			pTarget = pLine;
			break;
		}
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Info().tLeftPos.fX;
	float y1 = pTarget->Get_Info().tLeftPos.fY;
	float x2 = pTarget->Get_Info().tRightPos.fX;
	float y2 = pTarget->Get_Info().tRightPos.fY;

	*_y = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

	return true;
}

void CLineMgr::Load_Line(const TCHAR* _pFileName)
{	
	HANDLE hFile = CreateFile(_pFileName, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패", L"실패!", MB_OK);
		return;
	}

	LINEINFO	Temp = {};
	DWORD		dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &Temp, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_listLine.emplace_back(new CLine(Temp.tLeftPos, Temp.tRightPos));
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공", L"성공!", MB_OK);
}
