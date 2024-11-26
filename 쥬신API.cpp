// 쥬신API.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "쥬신API.h"
#include "Define.h"
#include "..\\HongDong_Engine_Source\HongApplication.h"
#define MAX_LOADSTRING 100
HongAppliction app;
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance); // 핸들
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    app.test();
    //깃허브 테스트

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_API, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // 핸들이 들어간다.

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_API));

    MSG msg;


    //GetMessage(&msg, nullptr, 0, 0))  


    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // 나중에 메세지를 처리할 프록함수
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_API));
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_API);
    wcex.lpszClassName = szWindowClass; //  API라는 이름의 정보
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // 레지스터 함수를 이용해 렘에다가 정보를 저장한다.
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) // 초기화 하는곳
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // szWindowClass에는 API 이름이 들어가있음. 전체적인 정보의 대한 핸들값 반환
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // 크기의 정도

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow); // 그 핸들값을 이용해서 화면 출력  
    UpdateWindow(hWnd); // 실시간으로 업데이트 하는것들

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

RECT  rc{ 50,50,100,100 }; // 사각형
RECT  el{ 50,50,100,100 }; // 원

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // 메세지를 처리하는 프록함수
{
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 0, 0);
        break;

    case WM_TIMER:
        InvalidateRect(hWnd, 0, TRUE);

        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {

        //DC란 화면 출력에 필요한 모든 정보를 가지는 데이터 구조체이며
       //GDI모듈에 의해서 관리된다. ( 그래픽 디바이스 인터페이스)
       //어떤 폰트에 사용할건가? 어떤 선의 굵기를 정해줄건가 어떤 색상으로 그려줄껀가
       //화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행 할 수 있다.

        PAINTSTRUCT ps; // 윈도우 좌표계를 씀  x , y 뒤짚어져 있음
        // x를 레프트 y를 탑이라고 함.

        HDC hdc = BeginPaint(hWnd, &ps); // 핸들값으로 DC를 생성해주고, 그림 시작 알려주기

        // MoveToEx : 커서를 이동 시키는 함수
        // nullptr : 커서를 이동하기 전 위치를 output으로 반환
/*
           MoveToEx(hdc, 100, 100, nullptr);

           LineTo(hdc, 100, 200);
           LineTo(hdc, 200, 200);
           LineTo(hdc, 200, 100);
           LineTo(hdc, 100, 100);
           LineTo(hdc, 200, 200);

           MoveToEx(hdc, 200, 100, nullptr);

           LineTo(hdc, 100, 200);*/

        HBRUSH GrayBrush = CreateSolidBrush(RGB(176, 224, 230));

        HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GrayBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환

        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

        HBRUSH BlueBrush = CreateSolidBrush(RGB(0, 255, 255));  //RGB를 이용해 파랑 브러쉬를 생성해준다

        OldBrush = (HBRUSH)SelectObject(hdc, BlueBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환

        Ellipse(hdc, el.left, el.top, el.right, el.bottom);



        //SelectObject(hdc, OldBrush); //다시 흰색 원본브러쉬로 바꿔주고

        //DeleteObject(BlueBrush);       //파랑 브러쉬 삭제

        //HPEN Yellowpen = CreatePen(PS_SOLID, 2, RGB(255,215, 0)); // 옐로우펜 만들고 선형태 , 두께, 색깔 넣기
        //HPEN OldPen = (HPEN)SelectObject(hdc, Yellowpen);  // 셀렉트 잡을 통해 기존 흰색깔 선 저장해놓고 옐로우펜 선택

        //Ellipse(hdc, 200, 200, 300, 300); //  노란팬으로 원 야무지게 그리기

        //SelectObject(hdc, OldPen); // 다시 돌려놓고
        //DeleteObject(Yellowpen); // 썼던거 삭제
        //



        EndPaint(hWnd, &ps); // 그림 그리는거 종료
    }
    break;
    case WM_KEYDOWN:
        el.top = rc.top; // 원 크기 맞춰주기
        el.bottom = rc.bottom;
        el.left = rc.left;
        el.right = rc.right;
        switch (wParam)
        {
        case VK_ESCAPE:PostQuitMessage(0);
            break;

        case VK_RIGHT:
            rc.left += 30;
            rc.right += 30;
            break;
        case VK_LEFT:
            rc.left -= 30;
            rc.right -= 30;
            break;
        case VK_UP:
            rc.top -= 30;
            rc.bottom -= 30;
            break;
        case VK_DOWN:

            rc.top += 30;
            rc.bottom += 30;
            break;

        case VK_SPACE:

            while (el.top != 0)
            {
                el.top += -10;
                el.bottom += -10;
            }

            break;
        }
        break;
    case WM_DESTROY:
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
