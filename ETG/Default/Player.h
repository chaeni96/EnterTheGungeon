#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
public:
	enum STATE  { IDLE, WALK, ROLL, DEAD, HIT, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int		Update(void) override;
	virtual	void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Mouse_Sight(void); // 마우스 위치에 따라서 플레이어의 시선방향 움직임
	void		Key_Input(void);
	void		OffSet(void);
	void		Motion_Change(void);
	void		Dodge_Roll(void);

private:
	float					m_fDiagonal;
	bool					m_bJump;		// 점프 상태 확인
	float					m_fJumpPower;	// 점프 힘
	float					m_fJumpTime;	// 점프 중 진행 시간

	STATE					m_ePreState;
	STATE					m_eCurState;

	bool					m_bStretch = true;
	bool					m_bRoll; // 구르는 상태 확인
	POINT	pt{};

};
