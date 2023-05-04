// LR5_Sys_prog.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "LR5_Sys_prog.h"
#include <iostream>
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
const int IDBut1 = 1000;
const int IDBut2 = 1001;
const int IDBut3 = 1002;
const int IDBut4 = 1003;
const int IDBut5 = 1004;
const int IDBut6 = 1005;
bool But1 = false;
RECT rec;
RECT rect = { 0 ,0, 1000, 1000 };
bool But2 = false;
bool But3 = false;
bool But5 = true;
bool But6 = false;
int i = 0;
int j = 0;

double a = 0.0;
UINT_PTR timer;
const UINT_PTR IdTimer = 2005;
RECT circle = { 200, 200, 300, 300 };

HWND hwin;
HWND hshrp;

HDC hdc;
HDC hdcwin;
HDC hdcshrp;

bool But4 = false;
RECT fordraw = { 150, 90, 1100, 500 };
POINT start_point, end_point;
bool draw = false;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LR5SYSPROG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR5SYSPROG));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR5SYSPROG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR5SYSPROG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   HWND But1 = CreateWindowW(L"BUTTON", L"Задание 1", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 20, 110, 40, hWnd, (HMENU)IDBut1, hInstance, 0);
   HWND But2 = CreateWindowW(L"BUTTON", L"Задание 2", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 70, 110, 40, hWnd, (HMENU)IDBut2, hInstance, 0);
   HWND But3 = CreateWindowW(L"BUTTON", L"Задание 3", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 120, 110, 40, hWnd, (HMENU)IDBut3, hInstance, 0);
   HWND But4 = CreateWindowW(L"BUTTON", L"Задание 4", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 170, 110, 40, hWnd, (HMENU)IDBut4, hInstance, 0);
   HWND But5 = CreateWindowW(L"BUTTON", L"Красный", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 250, 110, 40, hWnd, (HMENU)IDBut5, hInstance, 0);
   HWND But6 = CreateWindowW(L"BUTTON", L"Синий", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 300, 110, 40, hWnd, (HMENU)IDBut6, hInstance, 0);
   GetWindowRect(hWnd, &rec);
   rec.left = 0;
   rec.top = 0;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
void Draw_Circle(HDC hdc, RECT& c, int i, int j)
{
    SelectObject(hdc, (HPEN)CreatePen(PS_SOLID, 2, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
    SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
    c.left += i;
    c.top += j;
    c.right += i;
    c.bottom += j;
    Ellipse(hdc, c.left, c.top, c.right, c.bottom);
}
bool inrect(int x, int y)
{
    return x >= fordraw.left && x <= fordraw.right && y >= fordraw.top && y <= fordraw.bottom;

}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDBut1:
            {
                But1 = true;
                InvalidateRect(hWnd, &rec, true);
                
            }
            break;
            case IDBut2:
            {
                But2 = true;
                InvalidateRect(hWnd, &rec, true);
            }
            break;
            case IDBut3:
            {
                But3 = !But3;
                if (But3)
                {
                    hwin = GetDesktopWindow();
                    hshrp = FindWindow(NULL, L"Form_PI");

                    hdc = GetWindowDC(hWnd);
                    hdcwin = GetWindowDC(hwin);
                    hdcshrp = GetWindowDC(hshrp);

                    SetTimer(hWnd, IdTimer, 25, NULL);
                }
                else
                {
                    a = 0.0;
                    circle = { 200, 200, 300, 300 };
                    But3 = false;
                    InvalidateRect(hwin, &rect, true);
                    UpdateWindow(hwin);
                    InvalidateRect(hWnd, &rect, true);
                    UpdateWindow(hWnd);
                    InvalidateRect(hshrp, &rect, true);
                    UpdateWindow(hshrp);
                    ReleaseDC(hwin, hdcwin);
                    ReleaseDC(hWnd, hdc);
                    ReleaseDC(hshrp, hdcshrp);
                    KillTimer(hWnd, IdTimer);
                }
            }
            break;
            case IDBut4:
            {
                But4 = !But4;
                InvalidateRect(hWnd, &rec, true);
            }
            break;
            case IDBut5:
            {
                But5 = true;
                But6 = false;
            }
            break;
            case IDBut6:
            {
                But6 = true;
                But5 = false;
            }
            break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
    {
        if (But3)
        {
            InvalidateRect(hwin, &rect, true);
            UpdateWindow(hwin);
            InvalidateRect(hWnd, &rect, true);
            UpdateWindow(hWnd);
            InvalidateRect(hshrp, &rect, true);
            UpdateWindow(hshrp);

            i = int(4 * cos(a));
            j = int(4 * sin(a));

            Draw_Circle(hdc, circle, i, j);
            //InvalidateRect(hwin, &rect, false);
            Draw_Circle(hdcwin, circle, i, j);
            Draw_Circle(hdcshrp, circle, i, j);

            a += 0.1;

        }
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            
            if (But1)
            {
               
                HWND hwin = GetDesktopWindow();
                HDC hdcwin = GetDC(hwin);
                // переменные для расчета красного, зелёного и синего цвета соответственно
                int rc = 0;
                int gc = 0;
                int bc = 0;

                RECT winrec;
                GetWindowRect(hwin, &winrec);

                for (int i = 0; i < 5; i++)
                {
                    int right = rand() % winrec.right + 1;
                    int bottom = rand() % winrec.bottom + 1;

                    COLORREF c = GetPixel(hdcwin, right, bottom);
                    rc += GetRValue(c);
                    gc += GetGValue(c);
                    bc += GetBValue(c);
                }

                ReleaseDC(hwin, hdcwin);

                COLORREF color = RGB(rc / 5, gc / 5, bc / 5);
                /*
                                long long rc = 0;
                long long gc = 0;
                long long bc = 0;
                long long count = 0;

                RECT winrec;
                GetWindowRect(hwin, &winrec);

                for (int i = 0; i < winrec.right; i++)
                    for (int j = 0; j < winrec.bottom; j++)
                    {
                        count++;
                        COLORREF c = GetPixel(hdcwin, i, j);
                        rc += GetRValue(c);
                        gc += GetGValue(c);
                        bc += GetBValue(c);
                    }

                ReleaseDC(hwin, hdcwin);

                COLORREF color = RGB(rc / count, gc / count, bc / count);
                */

                // закрасим окно приложения преобладающим цветом рабочего стола
                RECT hwndrec;
                GetWindowRect(hWnd, &hwndrec);
                hwndrec.left = 0;
                hwndrec.top = 0;
                FillRect(hdc, &hwndrec, CreateSolidBrush(color));

                //геометрические фигуры и надписи

                SelectObject(hdc, (HPEN)CreatePen(PS_SOLID, 2, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
                
                Ellipse(hdc, 350, 150, 550, 350);

                SelectObject(hdc, (HPEN)CreatePen(PS_SOLID, 2, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
                MoveToEx(hdc, 750, 50, NULL);
                LineTo(hdc, 950, 150);
                LineTo(hdc, 950, 50);
                LineTo(hdc, 750, 50);

                SelectObject(hdc, (HPEN)CreatePen(PS_SOLID, 2, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));

                Rectangle(hdc, 600, 150, 800, 350);
                
                SelectObject(hdc, (HFONT)CreateFont(28, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                    CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact")));
                RECT rect;
                SetRect(&rect, 240, 50, 390, 100);
                SetTextColor(hdc, RGB(rand() % 255 + 1, rand() % 255+1, rand() % 255+1));
                DrawText(hdc, TEXT("Лабораторная работа №5"), -1, &rect, DT_NOCLIP);
                SelectObject(hdc, (HFONT)CreateFont(28, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                    CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact")));


                But1 = false;
            }
            if (But2)
            {
                // рабочий стол
                HWND hwnd = GetDesktopWindow();
                HDC hdc = GetDC(hwnd);
                SelectObject(hdc, (HPEN)CreatePen(PS_NULL, 0, RGB(255, 255, 255)));
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
                Rectangle(hdc, 50, 50, 350, 150);
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
                Rectangle(hdc, 50, 150, 350, 250);
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
                Rectangle(hdc, 50, 250, 350, 350);
                ReleaseDC(hwnd, hdc);

                //рабочая область окна
                hdc = GetDC(hWnd);
                SelectObject(hdc, (HPEN)CreatePen(PS_SOLID, 2, RGB(0,0,0)));
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
                Rectangle(hdc, 200, 150, 800, 250);
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
                Rectangle(hdc, 200, 250, 800, 350);
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
                Rectangle(hdc, 200, 350, 800, 450);
                ReleaseDC(hWnd, hdc);

                //поверхность окна приложения
                hdc = GetWindowDC(hWnd);
                SelectObject(hdc, (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
                Rectangle(hdc, 200, 15, 400, 50);
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
                Rectangle(hdc, 200, 50, 400, 85);
                SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
                Rectangle(hdc, 200, 85, 400, 120);
                ReleaseDC(hWnd, hdc);
                But2 = false;
            }
            if (But4)
            {
                FrameRect(hdc, &fordraw, (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)));
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
    {

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (But4)
        {
            //Проверим, что нажали в области для рисования
            if (inrect(x, y))
            {
                hdc = GetDC(hWnd);
                draw = true;
                start_point.x = x;
                start_point.y = y;
                end_point.x = x;
                end_point.y = y;
            }
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        //закончим рисовать линию

        if (draw)
        {
            draw = FALSE;
            ReleaseDC(hWnd, hdc);
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (draw && inrect(x, y))
        {
            if (But5)
                SelectObject(hdc, CreatePen(BS_SOLID, 1, RGB(0,255,255)));
            if (But6)
                SelectObject(hdc, CreatePen(BS_SOLID, 1, RGB(255, 255, 0)));
            SetROP2(hdc, R2_XORPEN);

            MoveToEx(hdc, start_point.x, start_point.y, NULL);
            LineTo(hdc, end_point.x, end_point.y);
            MoveToEx(hdc, start_point.x, start_point.y, NULL);
            LineTo(hdc, x, y);

            end_point.x = x;
            end_point.y = y;
        }
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

// Обработчик сообщений для окна "О программе".
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
