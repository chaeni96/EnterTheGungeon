#include "stdafx.h"
#include "UiMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;

CUiMgr::CUiMgr()
{
}


CUiMgr::~CUiMgr()
{
	Release();
}

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}


void CUiMgr::Add_Object(UIID eID, CUi * pObj)
{
	if ((eID >= UI_END) || (nullptr == pObj))
		return;

	m_UiList[eID].push_back(pObj);


}

int CUiMgr::Update(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UiList[i].begin();
			iter != m_UiList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CUi*>(*iter);
				iter = m_UiList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CUiMgr::Late_Update(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UiList[i])
		{
			iter->Late_Update();

			if (m_UiList[i].empty())
				break;

			RENDERID eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);
		}
	}

}



void CUiMgr::Render(HDC hDC)
{
	

	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CUi*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

		m_RenderSort[i].clear();
	}

}

void CUiMgr::Release(void)
{
	for (int i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UiList[i])
			Safe_Delete<CUi*>(iter);

		m_UiList[i].clear();
	}
}

void CUiMgr::Delete_ID(UIID eID)
{
	for (auto& iter : m_UiList[eID])
		Safe_Delete(iter);

	m_UiList[eID].clear();
}
