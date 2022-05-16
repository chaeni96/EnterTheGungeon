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
	void PatternNormalShot(); // 1�� �߻�
	void PatternWideShot(); // ���̵弦
	void PatternContinueShot(); // ���ӹ߻�
	bool PatternMoveToUp(); // �ϴ� ���� �ö󰡱�
	void PatternBomb(); // �̻��� ��� bool Ÿ�� 5�� ��� true ��ȯ
	bool PatternMoveToOri(); // ����
	void Hit();

private:
	STATE			m_ePreState;
	STATE			m_eCurState;
	float			m_fDiagonal;
	POINT			m_tPosin;

private:


	enum PATTERN { // ���ϸ� ����
		LAUNCH1 = 1,		// �Ѿ� �߻�
		LAUNCH2,		// ������ �Ѿ� �߻�
		LAUNCH3,	// �����Ѿ� �߻�
		MOVE,
		NONE,// exit ���� ����� �÷��̾ �ϴ��� 100�� ���������� exit�� �̵�			// �⺻����
		// ��ź�� �𰹼��� 5���� �Ǹ� exit�� �̵�
		BOMB,
		RETURN
		
	};

	PATTERN currentState; // ���� ���� ����
	bool m_bDeadEffect;
	DWORD m_dwTime;
	int iCount; 
	int iTempX;
	int iTempY;
	POINT originPosition; //���� ��ġ
	POINT targetPosition; // Ÿ�� ��ġ
	bool m_bCheck;
};

