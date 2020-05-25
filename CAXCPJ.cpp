#include "framework.h"    
#include "CAXCPJ.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LOADSTRING 100                          //ȫ�ֱ���

HINSTANCE hInst;                                    // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                      // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];                // ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM                MyRegisterClass(HINSTANCE hInstance);               // ע�ᴰ�ں���������
BOOL                InitInstance(HINSTANCE, int);                       // ��ʼ��ʵ���ĺ�������
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);                // �����ڵĻص�����
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);                  // "����"�Ի���Ļص�����

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                         // win32������ں���
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);     // �����ַ�����Դ
    LoadStringW(hInstance, IDC_XIRCC, szWindowClass, MAX_LOADSTRING);   // �����ַ�����Դ
    MyRegisterClass(hInstance);                                         // ����ע�ᴰ�ں���

    // ִ��Ӧ�ó����ʼ��:                                 
    if (!InitInstance(hInstance, nCmdShow = 3))                         // ���ó�ʼ��ʵ������
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_XIRCC));  // ����

    MSG msg;

    // ����Ϣѭ��:
    while (GetMessage(&msg, nullptr, 0, 0))                             // ����Ϣ������ȡ��Ϣ
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);                                     // ������Ϣ
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


//  ����: MyRegisterClass()
//  Ŀ��: ע�ᴰ���ࡣ
ATOM MyRegisterClass(HINSTANCE hInstance)                                // ע�ᴰ�ں���,ʵ�ʵ��õ�api �� RegisterClassEx
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);                                    // �ṹ��WNDCLASSEX�Ĵ�С

    wcex.style = CS_HREDRAW | CS_VREDRAW;                                // ���崰����ʽ                                  
    wcex.lpfnWndProc = WndProc;                                          // �ص�����
    wcex.cbClsExtra = 0;                                                 // ����������ֽ�����ͨ��Ϊ0
    wcex.cbWndExtra = 0;                                                 // ����ʵ�������ֽ�����ͨ��Ϊ0
    wcex.hInstance = hInstance;                                          // ���̾��
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));        // ͼ��
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);                       // �����ʽ
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);                     // ����
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_XIRCC);                     // �˵�ָ��
    wcex.lpszClassName = szWindowClass;                                  // ��������
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1)); // ����Сͼ��

    return RegisterClassExW(&wcex);
}



//   ����: InitInstance(HINSTANCE, int)
//   Ŀ��: ����ʵ�����������������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)                      // ��ʼ��ʵ������,�˺��������Ǵ�������ʾ����,ʵ��ʹ�õ�api ��CreateWindow,,ShowWindow
{
    hInst = hInstance;                                                    // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//  Ŀ��: ���������ڵ���Ϣ��
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �����˵�ѡ��:
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
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: �ڴ˴�����ʹ�� hdc ���κλ�ͼ����...
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

// �����ڡ������Ϣ��������
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