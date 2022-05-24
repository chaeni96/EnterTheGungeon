#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	enum STATE { START, END };
public:
	CEnding();
	~CEnding();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Motion_Change(void);

private:
	STATE		m_eCurState;
	STATE		m_ePreState;
};

