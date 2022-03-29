/* -------------------------------------------------------------------
                    MyWindows.c -- 基本窗口模型
                                《Windows 程序设计（SDK）》视频教程
--------------------------------------------------------------------*/

#include <windows.h>
#include <vector>
#include <iostream>

#define LINEHIGH 15

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
        static TCHAR szAppName[] = TEXT("MyWindows");
        HWND hwnd;
        MSG msg;
        WNDCLASS wndclass;

        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = WndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndclass.lpszMenuName = NULL;
        wndclass.lpszClassName = szAppName;

        if (!RegisterClass(&wndclass))
        {
                MessageBox(NULL, TEXT("need Windows NT！"), szAppName, MB_ICONERROR);
                return 0;
        }

        hwnd = CreateWindow(szAppName,
                TEXT("win32"),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                hInstance,
                NULL);

        ShowWindow(hwnd, iCmdShow);
        UpdateWindow(hwnd);

        while (GetMessage(&msg, NULL, 0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        HDC hdc;
        PAINTSTRUCT ps;
        RECT rect, rectc;
        TCHAR szBuffer[128];
        HBRUSH hBrush, hBrush1;
        HPEN hPen, hPen1;
        static int cxClient, cyClient;
        POINT point;
        int _x[11] = {20, 40, 10, 20, 30, 40, 50, 20, 30, 40, 30},
            _y[11] = {10, 10, 20, 20, 20, 20, 20, 30, 30, 30, 40},
            _size = 11;

        switch (message)
        {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(WHITE_PEN));
            hBrush = CreateSolidBrush(RGB(255, 0, 0));
            SelectObject(hdc, hBrush);
            for(int i = 0; i < _size; i++)
                Rectangle(hdc, _x[i], _y[i], _x[i]+10, _y[i]+10);
            EndPaint(hwnd, &ps);
            return 0;

        case WM_LBUTTONUP:
            SetRect(&rectc, 10, 10, 60, 50);
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            SendMessage(hwnd, WM_PAINT, wParam, lParam);
            if(PtInRect(&rectc, point))
                MessageBox(hwnd, TEXT("你戳中了我的心！"), TEXT("HEART"), MB_OK);
            return 0;

        case WM_RBUTTONUP:
            DestroyWindow(hwnd);
            return 0;

        case WM_CLOSE:
            if(MessageBox(hwnd, TEXT("确认关闭？"), TEXT("???"), MB_OKCANCEL) == IDOK)
                DestroyWindow(hwnd);
            else
                return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hwnd, message, wParam, lParam);
}
