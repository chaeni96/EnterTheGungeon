#pragma once

#include "Logo.h"
#include "MyMenu.h"
#include "MyEdit.h"
#include "Stage.h"
#include "Hidden.h"
#include "Ending.h"
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eID);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	SCENEID		Get_SceneID(void) { return m_eCurScene; }

protected:
	virtual void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; };

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;
	CObj*					m_pPlayer;
	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;

};

