#include "framework.h"    
#include "CAXCPJ.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LOADSTRING 100                          //全局变量

HINSTANCE hInst;                                    // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                      // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];                // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);               // 注册窗口函数的声明
BOOL                InitInstance(HINSTANCE, int);                       // 初始化实例的函数声明
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);                // 主窗口的回调函数
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);                  // "关于"对话框的回调函数

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                         // win32程序入口函数
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);     // 导入字符串资源
    LoadStringW(hInstance, IDC_XIRCC, szWindowClass, MAX_LOADSTRING);   // 导入字符串资源
    MyRegisterClass(hInstance);                                         // 调用注册窗口函数

    // 执行应用程序初始化:                                 
    if (!InitInstance(hInstance, nCmdShow = 3))                         // 调用初始化实例函数
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_XIRCC));  // 导入

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))                             // 从消息队列中取消息
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);                                     // 传递消息
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


//  函数: MyRegisterClass()
//  目标: 注册窗口类。
ATOM MyRegisterClass(HINSTANCE hInstance)                                // 注册窗口函数,实际调用的api 是 RegisterClassEx
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);                                    // 结构体WNDCLASSEX的大小

    wcex.style = CS_HREDRAW | CS_VREDRAW;                                // 定义窗体样式                                  
    wcex.lpfnWndProc = WndProc;                                          // 回调函数
    wcex.cbClsExtra = 0;                                                 // 窗口类额外字节数，通常为0
    wcex.cbWndExtra = 0;                                                 // 窗口实例额外字节数，通常为0
    wcex.hInstance = hInstance;                                          // 进程句柄
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));        // 图标
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);                       // 鼠标样式
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);                     // 背景
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_XIRCC);                     // 菜单指针
    wcex.lpszClassName = szWindowClass;                                  // 窗体类名
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1)); // 窗口小图标

    return RegisterClassExW(&wcex);
}



//   函数: InitInstance(HINSTANCE, int)
//   目标: 保存实例句柄并创建主窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)                      // 初始化实例函数,此函数功能是创建并显示窗口,实际使用的api 是CreateWindow,,ShowWindow
{
    hInst = hInstance;                                                    // 将实例句柄存储在全局变量中

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//  目标: 处理主窗口的消息。
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDC_NEW_FILES_Import:                                                                                            // 文件菜单
            DialogBox(hInst, MAKEINTRESOURCE(IDC_NEW_FILES_Import), hWnd, About);
            break;
        case IDC_NEW_FILES_Export:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_NEW_FILES_Export), hWnd, About);
            break;
        case IDC_NEW_FILES_information:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_NEW_FILES_information), hWnd, About);
            break;
        case IDC_NEW_FILES_Safety:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_NEW_FILES_Safety), hWnd, About);
            break;
        case IDC_edit_delete:                                                                                                 // 编辑菜单
            DialogBox(hInst, MAKEINTRESOURCE(IDC_edit_delete), hWnd, About);
            break;
        case IDC_edit_setting:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_edit_setting), hWnd, About);
            break;
        case IDC_edit_Openwithexternalprogram:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_edit_Openwithexternalprogram), hWnd, About);
            break;
        case IDC_edit_Fileinformation:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_edit_Fileinformation), hWnd, About);
            break;
        case IDC_view_theme:                                                                                                  // 视图菜单
            DialogBox(hInst, MAKEINTRESOURCE(IDC_view_theme), hWnd, About);
            break;
        case IDC_Components_Onlineaudio:                                                                                      // 组件菜单
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Onlineaudio), hWnd, About);
            break;
        case IDC_Components_Onlinevideo:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Onlinevideo), hWnd, About);
            break;
        case IDC_Components_Cloudstorage:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Cloudstorage), hWnd, About);
            break;
        case IDC_Components_Compresseddocument:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Compresseddocument), hWnd, About);
            break;
        case IDC_Components_Audioextension:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Audioextension), hWnd, About);
            break;
        case IDC_Components_Videoextension:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Videoextension), hWnd, About);
            break;
        case IDC_Components_Multiuser:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Components_Multiuser), hWnd, About);
            break;
        case IDC_Safety_Permissionsettings:                                                                                   // 安全菜单
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Safety_Permissionsettings), hWnd, About);
            break;
        case IDC_Safety_Passwordmanagement:
            DialogBox(hInst, MAKEINTRESOURCE(IDC_Safety_Passwordmanagement), hWnd, About);
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
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
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

// “关于”框的消息处理程序。
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