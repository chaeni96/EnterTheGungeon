#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create(void)
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}

	static CObj*	Create(float _fX, float _fY, float _fAngle)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

