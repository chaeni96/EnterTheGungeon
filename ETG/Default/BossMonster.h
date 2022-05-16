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
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	virtual		bool	Get_DeadEffect(void);
private:
	void		Motion_Change(void);
	void		Monster_Dir(void);


private:
	void RandomPattern();
	void PatternNormalShot(); // 1발 발사
	void PatternWideShot(); // 와이드샷
	void PatternContinueShot(); // 연속발사
	bool PatternMoveToUp(); // 하늘 위로 올라가기
	void PatternBomb(); // 미사일 쏘기 bool 타입 5번 쏘면 true 반환
	bool PatternMoveToOri(); // 복귀
	void Hit();

private:
	STATE			m_ePreState;
	STATE			m_eCurState;
	float			m_fDiagonal;
	POINT			m_tPosin;

private:


	enum PATTERN { // 패턴만 쓰자
		LAUNCH1 = 1,		// 총알 발사
		LAUNCH2,		// 전방향 총알 발사
		LAUNCH3,	// 연속총알 발사
		MOVE,
		NONE,// exit 가는 방법은 플레이어가 하늘의 100에 도달했을때 exit로 이동			// 기본상태
		// 폭탄을 쏜갯수가 5발이 되면 exit로 이동
		BOMB,
		RETURN
		
	};

	PATTERN currentState; // 현재 보스 상태
	bool m_bDeadEffect;
	DWORD m_dwTime;
	int iCount; 
	int iTempX;
	int iTempY;
	POINT originPosition; //현재 위치
	POINT targetPosition; // 타겟 위치
	bool m_bCheck;
};

