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
	void PatternMoveToUp(); // �ϴ� ���� �ö󰡱�
	bool PatternBomb(); // �̻��� ��� bool Ÿ�� 5�� ��� true ��ȯ
	void PatternMoveToOri(); // ����
	void Hit();
	void PatternMoveToPlayer();

private:
	STATE m_ePreState;
	STATE m_eCurState;
	float			m_fDiagonal;
	POINT			m_tPosin;

private:
	enum Behavior {
		Enter, // �غ�
		Execute, // ����
		Exit // ����
	};

	enum PATTERN {
		LAUNCH1,		// �Ѿ� �߻�
		LAUNCH2,		// ������ �Ѿ� �߻�
		LAUNCH3,	// �����Ѿ� �߻�
		MOVE, // exit ���� ����� �÷��̾ �ϴ��� 100�� ���������� exit�� �̵�
		BOMB, // ��ź�� �𰹼��� 5���� �Ǹ� exit�� �̵�
		RETURN, // ���� ���ڸ��� ���ƿ��� exit�� �̵�
		None,			// �⺻����
	};

	Behavior behaviorState; // ���� ���� ����
	PATTERN currentState; // ���� ���� ����
	int iStatus;
	bool m_bDeadEffect;
	DWORD m_dwTime;

	POINT originPosition; //���� ��ġ
	POINT targetPosition; // Ÿ�� ��ġ

};

