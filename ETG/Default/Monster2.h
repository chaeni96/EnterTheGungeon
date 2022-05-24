#pragma once
#include "Obj.h"
class CMonster2 :
	public CObj
{
public :
	enum STATE {IDLE_UP, IDLE_RIGHT, IDLE_DOWN, IDLE_LEFT, ATTACK_UP, ATTACK_RIGHT, ATTACK_DOWN, ATTACK_LEFT, DEAD_ALL, SMOG_RIGHT, SMOG_LEFT, HIT_ALL, STATE_END };
public:
	CMonster2();
	virtual ~CMonster2();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual		void	OnCollision(void)	override;
	virtual		void	OnCollision(DIRECTION _eDir, const float & _fX, const float& _fY) override;
	virtual		bool	Get_DeadEffect(void);
	void   Set_CollisionCheck(void) { m_bCollisionCheck = false; }


private:
	void		Motion_Change(void);
	void		Monster_Dir(void);
	void		Hit();
	void		Split();
	void		Smog();
	void		RandomPattern();
	void		MoveToPlayer(void);
	void		AttackBullet(void);
private:
	enum PATTERN { // 랜덤 사용할 필요없음
		SPLIT = 1 ,		// 검으로 공격 ->NONE으로 가기
		SMOG,		// 스모그 내뿜기 -> 순간이동
		MOVE,	// ->검으로 공격 
		NONE

	};

private:
	PATTERN		m_ecurPattern;
	STATE		m_eCurState;
	STATE		m_ePreState;
	bool		m_bDeadEffect;

	float			m_fDiagonal;
	POINT			m_tPosin;
	DWORD          m_DelayTime;
	DWORD			m_pTime;
	DWORD			m_SoundTime;
	int				m_iRandom;
	bool			m_bCollisionCheck;

};

