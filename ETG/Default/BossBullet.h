#pragma once
#include "Obj.h"
class BossBullet :
	public CObj
{
public:
	BossBullet();
	~BossBullet();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private :
	float m_fDiagonal;
};

