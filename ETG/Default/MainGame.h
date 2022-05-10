#pragma once

#include "Include.h"

#include "Player.h"

class CMainGame
{
public:				// 생성자, 소멸자
	CMainGame();
	~CMainGame();

// public, protected, private 함수
public:
	void	Initialize(void);		// 초기화 함수
	void	Update(void);			// 매 프레임마다 갱신되는 데이터를 만드는 함수
	void	Late_Update(void);
	void	Render(void);			// 매 프레임마다 출력하는 함수
	void	Release(void);			// 동적할당한 포인터를 해제하는 함수


// public, protected, private 변수
private:
	HDC		m_hDC;
	/*CObj*	m_pPlayer;
	list<CObj*>	m_BulletList;*/



	TCHAR		m_szFPS[64];	// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	int			m_iFPS;
	DWORD		m_dwTime;

};

// 디자인 패턴 : 코드의 구조들을 일정한 형태로 만들어 재사용하기 편리하게 만든 패턴

// 추상 팩토리 패턴 : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화하는 패턴을 의미한다.
// 객세 생성 시 공통적으로 수행할 작업을 추상화시키는 방식을 의미한다.

// 반복자(이터레이터)패턴 : 내부 표현 방식을 공개하지 않고 순차적인 접근 방법을 제공하는 패턴을 의미한다.

// 중재자(메디에이터)패턴 : 상호작용하는 객체들이 서로 복잡한 관계를 맺고 있을 경우 별도의 형식으로 정의하여 준애하는 객체를 두는 패턴
					  // 복잡한 관계를 단순화 시키기 위한 용도, (n 대 n) 관계를 (1 : n)의 만드는 패턴

// 싱글톤 패턴 : 단 하나의 인스턴스(객체)를 생성하여 사용하는 패턴, 인스턴스가 필요할 때마다 똑같은 인스턴스를 생성하는 것이 아니라 기존의 생성해둔 인스턴스를 불러와서 사용하는 패턴
			// 다른 인스턴스 생성을 막기 위해 생성자와 소멸자를 private으로 두어 외부 생성을 불가능하게 만든다.
