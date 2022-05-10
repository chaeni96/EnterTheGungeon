// Default.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Default.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// 창 생성과 관련된 디자인 요소를 제어
BOOL                InitInstance(HINSTANCE, int);				// 실제적으로 창을 생성하고 그 창의 핸들을 만드는 기능
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULT));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame*	pMainGame = new CMainGame;
	
	if (nullptr == pMainGame)
		return FALSE;

	pMainGame->Initialize();

    // 기본 메시지 루프입니다.
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
        {
            TranslateMessage(&msg);	// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 번역하는 함수
            DispatchMessage(&msg);	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램에서 처리(WndProc 호출) 하도록 전달
        }
    }*/

	// 운영체제가 시작된 후로 흐른 시간을 정수 형태로 반환
	// 1 / 1000초의 DWORD 정수값으로 반환(밀리 세컨드 단위)
	DWORD		dwOldTime = GetTickCount();



	while (true)
	{
		// PM_REMOVE   : 메시지를 읽어옴과 동시에 메시지 큐에서 제거
		// PM_NOREMOVE : 메시지 큐에 메시지가 존재하는지만 파악, 만약 메시지를 얻어오려면 GetMessage를 다시 호출해야 함

		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
			{
				TranslateMessage(&msg);	// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 번역하는 함수
				DispatchMessage(&msg);	// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램에서 처리(WndProc 호출) 하도록 전달
			}
		}

		else
		{
			if (dwOldTime + 10 < GetTickCount())
			{
				pMainGame->Update();
				pMainGame->Late_Update();
				pMainGame->Render();

				dwOldTime = GetTickCount();
			}		

			/*pMainGame->Update();
			pMainGame->Late_Update();
			pMainGame->Render();*/
		}

	}


	Safe_Delete<CMainGame*>(pMainGame);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rc{ 0, 0, WINCX, WINCY };

   // 출력창의 최종 크기 = 원래 창 사이즈 + 기본 윈도우 창 설정 값 + 메뉴바 크기 고려 여부
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      400, 300,  // 출력하고자 하는 창의 left와 top 좌표
	   rc.right - rc.left, 
	   rc.bottom - rc.top, // 생성하고자 하는 창의 가로, 세로 사이즈
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

#pragma region 복습용 코드
		/*case WM_CREATE:

		SetTimer(hWnd, 0, 0, 0);

		/ *SetTimer : 타이머를 설치하는 함수
		1인자 :윈도우 핸들
		2인자 : 타이머의 id 번호, 여러개의 타이머가 존재할 수 있기 때문에, 현재는 0번 타이머
		3인자 : 타이머 주기, 기본값으로 지정, 1000당 1초
		4인자 : null인 경우 wm_timer라는 메세지를 발생시킴* /
		break;

		case WM_TIMER:

		InvalidateRect(hWnd, 0, true);
		// InvalidateRect : 윈도우 화면 갱신 함수, 함수 호출 시 wm_paint 메세지를 발생
		/ *1인자 : 갱신할 윈도우 핸들
		2인자 : 윈도우 안에서 갱신할 범위 지정, null인 경우 윈도우 전체 영역
		3인자 : false냐 true냐에 따라 화면 갱신 상태 변경* /
		// false인 경우 새로 그리는 부분만 갱신, true인 경우 그려져 있지 않는 모든 영역도 갱신
		break;*/
#pragma endregion 복습용 코드	

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

			// 그리기 함수
			/*MoveToEx(hdc, 100, 100, nullptr);
			LineTo(hdc, 200, 100);
			LineTo(hdc, 200, 200);
			LineTo(hdc, 100, 200);
			LineTo(hdc, 100, 100);*/

			// 사각형 그리기 함수
			//Rectangle(hdc, 100, 100, 200, 200);

			// 원 그리기 함수
			//Ellipse(hdc, 300, 300, 400, 400);

			/*LineTo(hdc, 200, 200);
			LineTo(hdc, 200, 300);*/

			/*Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			for (auto& iter : m_BulletList)
			{
				Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);
				
				iter.top    -= 10;
				iter.bottom -= 10;
			}*/
			
            EndPaint(hWnd, &ps);
        }
        break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		break;

    case WM_DESTROY:
		// KillTimer(hWnd, 0);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// 함수 호출 규약의 발생 이유 : 함수 실행이 종료되면 할당되었던 스택 메모리를 해제해야 하는데 함수를 호출한 호출원(caller)에서 호출 받은 피호출자(callee)에서 할 것인가에 대한 약속, 규약
// __cdecl, __stdcall, __fastcall, thiscall, naked 등

// __cdecl(호출자에서 스택을 정리)
/*
- c, c++의 기본 호출 규약, 호출자(caller)가 스택을 정리한다.
- 공통점은 자기 자신에게 어떤 매개변수가 들어온지 모른다. (가변인자가 가능한 함수)
- 이로 인해 보인이 스택을 정리할 수 없다.*/

// __stdcall

/*
- WIN32 api의 기본 호출 규약, 피호출자(callee)가 스택을 정리한다.
- api에서 제공하는 대부분의 함수들처럼 __stdcall은 '고정 인자 함수'이다.
- 매개변수가 고정되어 있다보니 어떤 데이터 타입이 들어올지 알고 있기 때문에 피호출자 본인이 스택을 정리할 수 있다.*/

// __fastcall

/*
- 함수 호출을 빠르게 처리하기 위한 호출 규약이가.
- ecx와 edx라는 레지스터를 통해 저장된다. 레지스터 사용하고 있다는 점 때문에 함수 호출이 빨라진다.*/

// thiscall
 
// - this 포인터를 인자로 넘겨받았을 때 사용하는 호출 규약이다.

