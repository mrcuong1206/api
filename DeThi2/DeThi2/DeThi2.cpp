// DeThi2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DeThi2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
int hinh;
int nen;
int vien;
HBRUSH hBrush;
HPEN hPen;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DETHI2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DETHI2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DETHI2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Tam giác
   // static POINT point[3] = { {200, 600}, {500, 400}, {700, 500} };
   // Thoi
   //static POINT point[4] = { {100, 0}, {0, 150}, {100, 300}, {200, 150} };

    static int x, y, x1, y1;
    static POINT pointThoi[4] = {};
    static POINT pointCan[3] = {};
    static POINT pointSao[8] = {};
    static HDC hdc;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        x1 = LOWORD(lParam);
        y1 = HIWORD(lParam);

        hdc = GetDC(hWnd);

        //hBrush = CreateSolidBrush(RGB(50, 200, 250));
        //SelectObject(hdc, hPen); // Áp dụng bút         
        SelectObject(hdc, hBrush); // Áp dụng màu nền

        if (hinh == 1) {
            Rectangle(hdc, x, y, x1, y1);
        }
        else if (hinh == 2) {
            Polygon(hdc, pointThoi, 4);
        }
        else if(hinh == 3) {
            Polygon(hdc, pointCan, 3);
        }

         if (nen == 1) {
            hBrush = CreateSolidBrush(RGB(0, 255, 0));
         }
         else if (nen == 2) {
             hBrush = CreateSolidBrush(RGB(50, 200, 250));
         }

         if (vien == 1) {
             hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 255));
         }
         else if (vien == 2) {
             hPen = CreatePen(PS_DASH, 1, RGB(0, 255, 255));
         }

        // CHữ nhật
        //Rectangle(hdc, x, y, x1, y1);

        // Thoi
        pointThoi[0].x = (x + x1) / 2;
        pointThoi[0].y = y;
        pointThoi[1].x = x1;
        pointThoi[1].y = (y + y1) / 2;
        pointThoi[2].x = (x + x1) / 2;
        pointThoi[2].y = y1;
        pointThoi[3].x = x;
        pointThoi[3].y = (y + y1) / 2;
        //Polygon(hdc, pointThoi, 4);

        // Tam giác cân
        pointCan[0].x = (x + x1) / 2;
        pointCan[0].y = y;
        pointCan[1].x = x1;
        pointCan[1].y = y1;
        pointCan[2].x = x;
        pointCan[2].y = y1;
        //Polygon(hdc, pointCan, 3);

        // Sao
        /*pointSao[0].x = (x + x1) / 2;
        pointSao[0].y = y;
        pointSao[1].x = 2*x * 3*x * x1;*/

        ReleaseDC(hWnd, hdc);

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_Thoat:
                if (MessageBox(hWnd, TEXT("Bạn có thật sự muốn thoát!"), TEXT("Question"), MB_ICONQUESTION | MB_YESNO) == IDYES)
                {
                    DestroyWindow(hWnd);
                    break;
                }
            case ID_HCN:
                hinh = 1;
                break;
            case ID_Elip:
                hinh = 2;
                break;
            case ID_Sao:
                hinh = 3;
                break;
            case ID_Green:
                nen = 1;
                break;
            case ID_Blue:
                nen = 2;
                break;

            case ID_Red:
                vien = 1;
                break;
            case ID_XanhNgoc:
                vien = 2;
                break;


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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
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

// Message handler for about box.
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
