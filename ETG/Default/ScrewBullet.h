#pragma once
#include "Obj.h"
class CScrewBullet : public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	POINT		m_ptCenter;

	float		m_fRotAngle;
	float		m_fRotSpeed;
	float		m_fRotDistance;

	bool		m_bStart;	// 중심 축에 대한 적용은 1회만 적용 후 진행 방향대로 함께 이동하도록 설계 해야 함.

};

