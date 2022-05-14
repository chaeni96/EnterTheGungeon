#pragma once
#include "Obj.h"
class CBossMonster :
	public CObj
{
public:
	enum STATE {RU, RIGHT, RD, DOWN, LD, LEFT, LU, HIT, DEAD, FLY, LAND, POSE, END };
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void OnCollision(void)	override;
private:
	void		Motion_Change(void);
	void		Monster_Dir(void);


private:
	void RandomPattern();
	bool TargetMove();
	void BehaviorUpdate();

	void BehaviorEnter();
	void BehaviorExecute();
	void BehaviorExit();

	void PatternNormalShot();
	void PatternWideShot();
	void PatternContinueShot();
	void PatternMoveToPlayer();
	void Hit();

private:
	STATE m_ePreState;
	STATE m_eCurState;
	float			m_fDiagonal;
	POINT			m_tPosin;

private:
	enum Behavior {
		Enter, // 준비
		Execute, // 실행
		Exit // 종료
	};

	enum PATTERN {
		LAUNCH1,		// 총알 발사
		LAUNCH2,		// 전방향 총알 발사
		LAUNCH3,	// 연속총알 발사
		None,			// 기본상태
	};

	Behavior behaviorState; // 이전 보스 상태
	PATTERN currentState; // 현재 보스 상태
	int iStatus;
	bool m_bDeadEffect;
	DWORD m_dwTime;
};

