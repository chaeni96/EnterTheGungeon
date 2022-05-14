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
	void TargetMove();
	void BehaviorUpdate();

	void BehaviorEnter();
	void BehaviorExecute();
	void BehaviorExit();

	bool Ori();
	void PatternNormalShot();
	void PatternWideShot();
	void PatternContinueShot();
	void PatternMoveToUp(); // 하늘 위로 올라가기
	bool PatternBomb(); // 미사일 쏘기 bool 타입 5번 쏘면 true 반환
	void PatternMoveToOri(); // 복귀
	void Hit();
	void PatternMoveToPlayer();

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
		MOVE, // exit 가는 방법은 플레이어가 하늘의 100에 도달했을때 exit로 이동
		BOMB, // 폭탄을 쏜갯수가 5발이 되면 exit로 이동
		RETURN, // 원래 제자리로 돌아오면 exit로 이동
		None,			// 기본상태
	};

	Behavior behaviorState; // 이전 보스 상태
	PATTERN currentState; // 현재 보스 상태
	int iStatus;
	bool m_bDeadEffect;
	DWORD m_dwTime;

	POINT originPosition; //현재 위치
	POINT targetPosition; // 타겟 위치

};

