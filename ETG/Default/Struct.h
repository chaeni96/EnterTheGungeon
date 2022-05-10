#pragma once

typedef	struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;


typedef	struct	tagLinePoint 
{
	float		fX;
	float		fY;

	tagLinePoint(){	ZeroMemory(this, sizeof(tagLinePoint));	}
	tagLinePoint(float _fX, float _fY) : fX(_fX) , fY(_fY){	}

}LINEPOINT;

typedef	struct	tagLineInfo 
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLineInfo()	{	ZeroMemory(this, sizeof(tagLineInfo));	}
	tagLineInfo(LINEPOINT& tLeft, LINEPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight)	{	}

}LINE;

typedef struct tagFrame
{
	int		iFrameStart;		// 원하는 지점부터 스프라이트 이미지 구동 시작
	int		iFrameEnd;			// 스프라이트가 끝나는 지점을 지정
	int		iMotion;			// 모션 인덱스

	DWORD	dwSpeed;			// 스프라이트가 돌아가는 속도
	DWORD	dwTime;				// 스프라이트 위치가 변경되는 시간 

}FRAME;