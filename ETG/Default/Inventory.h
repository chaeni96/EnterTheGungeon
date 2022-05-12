#pragma once
#include "Ui.h"
class CInventory :
	public CUi
{
public:
	CInventory();
	virtual ~CInventory();


public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
};

