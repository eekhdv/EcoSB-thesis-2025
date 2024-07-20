/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   EcoUART1DialogWin
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "windows.h"
#include <CommCtrl.h>
#include "resource.h"
#pragma comment(lib, "user32")
#pragma comment(lib, "comctl32.lib")

/* Eco OS */
#include "IEcoSystem1.h"
#include "IEcoMemoryManager1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoUART1.h"
#include "IEcoUART1WIN32Config.h"

IEcoUART1Device* g_pIUARTDevice;
IEcoUART1WIN32Config* g_pIUARTConfig = 0;
ECO_UART_1_CONFIG xDevConfig = {0};
bool_t g_bConnected = 0;

BOOL CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) { 
    HWND h;
    CHAR bufComm[10] = {0};
    CHAR bufTransmit[64] = {0};
    CHAR bufReceive[64] = {0};
    int32_t nCount = 0;
    int16_t result = 0;
    byte_t dataTX = 0;
    byte_t dataRX = 0;
    int32_t index = 0;

    switch (message) { 

        case WM_CREATE:
            CreateWindow(TEXT("STATIC"), TEXT("Serial Port (UART) :"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 14, 140, 26, hDlg, (HMENU)IDC_STATIC_COMMPORT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | WS_BORDER | ES_LEFT , 150, 12, 340, 24, hDlg, (HMENU)IDC_EDIT_COMMPORT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_COMMPORT), g_pIUARTConfig->pVTbl->get_ConfigDescriptor(g_pIUARTConfig)->lpszName);
            CreateWindow(TEXT("BUTTON"), TEXT("Connect"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 520, 10, 100, 28, hDlg, (HMENU)IDC_BUTTON_CONNECT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            CreateWindow(TEXT("STATIC"), TEXT("Ttransmit Message :"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 48, 140, 26, hDlg, (HMENU)IDC_STATIC_TRANSMIT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | WS_BORDER | ES_LEFT , 150, 50, 340, 24, hDlg, (HMENU)IDC_EDIT_MESSAGE, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            CreateWindow(TEXT("BUTTON"), TEXT("Send"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 520, 50, 100, 28, hDlg, (HMENU)IDC_BUTTON_SEND, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 15, 100, 600, 320, hDlg, (HMENU)IDC_EDIT_RECEIVE, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("BUTTON"), TEXT("FORWARD"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 250, 120, 100, 28, hDlg, (HMENU)IDC_BUTTON_FORWARD, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("BUTTON"), TEXT("BACK"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 250, 200, 100, 28, hDlg, (HMENU)IDC_BUTTON_BACK, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("BUTTON"), TEXT("LEFT"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 130, 160, 100, 28, hDlg, (HMENU)IDC_BUTTON_LEFT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("BUTTON"), TEXT("STOP"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 250, 160, 100, 28, hDlg, (HMENU)IDC_BUTTON_STOP, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("BUTTON"), TEXT("RIGHT"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 370, 160, 100, 28, hDlg, (HMENU)IDC_BUTTON_RIGHT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("STATIC"), TEXT("Power"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 50, 140, 26, hDlg, (HMENU)IDC_STATIC_POWER, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("STATIC"), TEXT("100"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 50, 70, 50, 26, hDlg, (HMENU)IDC_STATIC_POWER_100, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("STATIC"), TEXT("0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 50, 250, 50, 26, hDlg, (HMENU)IDC_STATIC_POWER_0, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);

            //h = CreateWindowEx(0, TRACKBAR_CLASS, TEXT("Power"), WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_VERT | TBS_LEFT, 10, 70, 30, 200, hDlg, (HMENU)ID_TRACKBAR_POWER, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //SendMessageW(h, TBM_SETPAGESIZE, 0,  10); 
            //SendMessageW(h, TBM_SETTICFREQ, 10, 0);
            //SendMessage(h, TBM_SETRANGE, (WPARAM) TRUE, (LPARAM) MAKELONG(0, 100));
            //SendMessage(h, TBM_SETPOS, (WPARAM) TRUE, (LPARAM) 50); 
            //SetFocus(h); 
            //CreateWindow(TEXT("STATIC"), TEXT("Motor"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 130, 50, 140, 26, hDlg, (HMENU)IDC_STATIC_MOTOR_A, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(TEXT("STATIC"), TEXT("Motor"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 370, 50, 140, 26, hDlg, (HMENU)IDC_STATIC_MOTOR_B, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            //CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 180, 50, 50, 100, hDlg, (HMENU)ID_COMBOBOX_MOTOR_A, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), NULL);
            //CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 420, 50, 50, 100, hDlg, (HMENU)ID_COMBOBOX_MOTOR_B, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), NULL);
            //buf[0] = 'A';
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_A),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_B),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //buf[0] = 'B';
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_A),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_B),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //buf[0] = 'C';
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_A),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_B),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //buf[0] = 'D';
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_A),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_B),(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) buf);

            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_A),(UINT) CB_SETCURSEL,(WPARAM) 1,(LPARAM) 0);
            //SendMessage(GetDlgItem(hDlg, ID_COMBOBOX_MOTOR_B),(UINT) CB_SETCURSEL,(WPARAM) 2,(LPARAM) 0);

        return TRUE;

        case WM_COMMAND: 
            switch (LOWORD(wParam)) { 
                case IDOK:
                case IDCANCEL:
                    EndDialog(hDlg, wParam); 
                return TRUE; 
                case IDC_BUTTON_CONNECT:
                    if (g_bConnected) {
                        EnableWindow(GetDlgItem(hDlg, IDC_EDIT_COMMPORT), TRUE);
                        SetWindowTextA(GetDlgItem(hDlg, IDC_BUTTON_CONNECT), "Connect");
                        g_bConnected = 0;
                        /* Отключение */
                        result = g_pIUARTDevice->pVTbl->Disconnect(g_pIUARTDevice);
                    }
                    else {
                        EnableWindow(GetDlgItem(hDlg, IDC_EDIT_COMMPORT), FALSE);
                        nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_COMMPORT), bufComm, 10);
                        /* Создание нового устройства */
                        g_pIUARTConfig->pVTbl->get_ConfigDescriptor(g_pIUARTConfig)->lpszName = bufComm;
                        /* Подключение */
                        xDevConfig.BaudRate = ECO_UART_BR_9600;
                        result = g_pIUARTDevice->pVTbl->Connect(g_pIUARTDevice, &xDevConfig);
                        if (result == 0) {
                            /* Успешное подключение */
                            SetWindowTextA(GetDlgItem(hDlg, IDC_BUTTON_CONNECT), "Disonnect");
                            g_bConnected = 1;
                        }
                        /* Проверяем подключение */
                        if (g_bConnected != 1) {
                            /* Не удалось подключиться */
                            EnableWindow(GetDlgItem(hDlg, IDC_EDIT_COMMPORT), TRUE);
                        }
                    }
                    return TRUE;
                //case IDC_BUTTON_FORWARD:
                //    if (g_bConnected == 1) {
                //        power = 100 - SendMessage(GetDlgItem(hDlg, ID_TRACKBAR_POWER), TBM_GETPOS, 0, 0);
                //        g_bStarted = 1;
                //        startMotorF[11] = power;
                //        while ( nCount < 15) {
                //            data = startMotorF[nCount];
                //            nCount++;
                //            g_pIUARTDevice->pVTbl->Transmit(g_pIUARTDevice, data);
                //        }
                //    }
                //    return TRUE;
                case IDC_BUTTON_SEND:
                    if (g_bConnected == 1) {
                        nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_MESSAGE), bufTransmit, 64);
                        while ( index < nCount) {
                            dataTX = bufTransmit[index];
                            g_pIUARTDevice->pVTbl->Transmit(g_pIUARTDevice, dataTX);
                            g_pIUARTDevice->pVTbl->Receive(g_pIUARTDevice, &dataRX);
                            bufReceive[index] = dataRX;
                            SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RECEIVE), bufReceive);
                            index++;
                        }
                    }
                    return TRUE;
                //case IDC_BUTTON_BACK:
                //    if (g_bConnected == 1) {
                //        power = 100 - SendMessage(GetDlgItem(hDlg, ID_TRACKBAR_POWER), TBM_GETPOS, 0, 0);
                //        g_bStarted = 1;
                //        startMotorB[11] = 0xFF - power;
                //        while ( nCount < 15) {
                //            data = startMotorB[nCount];
                //            nCount++;
                //            g_pIUARTDevice->pVTbl->Transmit(g_pIUARTDevice, data);
                //        }
                //    }
                //    return TRUE;
                //case IDC_BUTTON_LEFT:
                //    if (g_bConnected == 1) {
                //        power = 100 - SendMessage(GetDlgItem(hDlg, ID_TRACKBAR_POWER), TBM_GETPOS, 0, 0);
                //        g_bStarted = 1;
                //        startMotorL[11] = power;
                //        while ( nCount < 15) {
                //            data = startMotorL[nCount];
                //            nCount++;
                //            g_pIUARTDevice->pVTbl->Transmit(g_pIUARTDevice, data);
                //        }
                //    }
                //    return TRUE;
                //case IDC_BUTTON_RIGHT:
                //    if (g_bConnected == 1) {
                //        power = 100 - SendMessage(GetDlgItem(hDlg, ID_TRACKBAR_POWER), TBM_GETPOS, 0, 0);
                //        g_bStarted = 1;
                //        startMotorR[11] = power;
                //        while ( nCount < 15) {
                //             data = startMotorR[nCount];
                //            nCount++;
                //            g_pIUARTDevice->pVTbl->Transmit(g_pIUARTDevice, data);
                //        }
                //    }
                //    return TRUE;
                //case IDC_BUTTON_STOP:
                //    if (g_bStarted == 1) {
                //        g_bStarted = 0;
                //        while ( nCount < 11) {
                //             data = stopMotor[nCount];
                //            nCount++;
                //            g_pIUARTDevice->pVTbl->Transmit(g_pIUARTDevice, data);
                //        }
                //    }
                //    return TRUE;
            }
        break;
        case WM_CLOSE:
            if (MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"), MB_ICONQUESTION | MB_YESNO) == IDYES) {
                DestroyWindow(hDlg);
            }
            return TRUE;

        case WM_DESTROY:
            PostQuitMessage(0);
            return TRUE;
        default:
            return DefWindowProc(hDlg, message, wParam, lParam);
    }
    return FALSE;
}

/*
 *
 * <сводка>
 *   Функция DialogProcessing
 * </сводка>
 *
 * <описание>
 *   Функция DialogProcessing
 * </описание>
 *
 */
int16_t DialogProcessing(/* in */IEcoUART1Device* pIDevice) {
    int16_t result = -1;
    HWND hDlg;
    WNDCLASS wndClass = {0};
    MSG msg;
    BOOL ret;
    RECT rectScreen;
    int32_t x = 0;
    int32_t y = 0;
    int32_t nCmdShow = 0;

    g_pIUARTDevice = pIDevice;
    result = g_pIUARTDevice->pVTbl->QueryInterface(g_pIUARTDevice, &IID_IEcoUART1WIN32Config, (void**) &g_pIUARTConfig);
    if (result != 0 || g_pIUARTConfig == 0) {
        /* Возврат в случае ошибки */
        return -1;
    }
    /* вычисление координат центра экрана */
    GetWindowRect(GetDesktopWindow(), &rectScreen);
    x = rectScreen.right / 2 - 150;
    y = rectScreen.bottom / 2 - 75;

    /* Регистрация класса */
    wndClass.lpfnWndProc = (WNDPROC)DialogProc;
    wndClass.style = CS_HREDRAW|CS_VREDRAW;
    wndClass.hInstance =  GetModuleHandle(0);
    wndClass.lpszClassName = TEXT("Eco UART Terminal");
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

    RegisterClass(&wndClass);
    FreeConsole();
    /* Инициализация элементов управления и создание диалогового окна */
    InitCommonControls();
    hDlg = CreateWindow(TEXT("Eco UART Terminal"), TEXT("Eco UART Terminal"), WS_DLGFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU, x, y, 640, 480, NULL, NULL,  GetModuleHandle(0), NULL);
    ShowWindow(hDlg, SW_SHOWDEFAULT);

    /* Цикл обработки Windows сообщений */
    while   ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
        if(ret == -1)
            return -1;

        if  (!IsDialogMessage(hDlg, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return result;
}

