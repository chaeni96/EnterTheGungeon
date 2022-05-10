#pragma once

#include "Scene.h"

class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

