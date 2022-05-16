#pragma once
#include "Obj.h"
class CMyButton : public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual		void	OnCollision(void)	override;
	virtual		bool	Get_DeadEffect(void);
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
private:
	int			m_iDrawID;

};

