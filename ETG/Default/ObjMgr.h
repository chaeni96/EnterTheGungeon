#pragma once

#include "Obj.h"
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	CObj*		Get_Player_Info() { return m_pPlayer; }
	void		Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

	void		Weapon_Change(TYPE _eType);

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	void		Delete_ID(OBJID eID);
	void		Set_Vector(vector<CObj*> _vectorId) { m_vecTile = _vectorId; }

private:
	list<CObj*>	m_ObjList[OBJ_END];
	vector<CObj*> m_vecTile; // 타일의 주소값 받아오기

public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr*			m_pInstance;
	list<CObj*>				m_RenderSort[RENDER_END];
	TYPE		m_eCurWeapon;  // 현재 무기 타입
	TYPE		m_ePreWeapon;  //이전 무기타입
	CObj* m_pPlayer;

};


