#pragma once
#include "Scene.h"
class CMyEdit :	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);

private:
	float		m_fSpeed = 5.f;

};

