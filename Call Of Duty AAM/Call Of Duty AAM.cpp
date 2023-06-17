// Call Of Duty AAM.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Call Of Duty AAM.h"
#include "time.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
    LoadStringW(hInstance, IDC_CALLOFDUTYAAM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALLOFDUTYAAM));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALLOFDUTYAAM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALLOFDUTYAAM);
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

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// Глобальные переменные

// Жизни солдата

int HPSol = 1;
int HPTPlay = 1;

// позиция террориста

int PTerrorX = 150;
int PTerrorY = 100;

//второй игрок

int TPlayX = 400;
int TPlayY = 50;

//Позиция солдата
int PSoldierX = 400;
int PSoldierY = 150;

//Позиция документов
// doc soldier
#define NUM_DOCUMENTSOL 6 //кол-во доков

int DocumentSolX[NUM_DOCUMENTSOL] = { 50, 90, 150, 185, 195, 220 }; // ось х
int DocumentSolY[NUM_DOCUMENTSOL] = { 10, 120, 150, 10, 220, 60 }; // ось у
int DocumentSolVisible[NUM_DOCUMENTSOL] = { 1, 1, 1, 1, 1, 1 }; // все видны

//doc two player
#define NUM_TDOCUMENTP 6

int TDocumentPX[NUM_TDOCUMENTP] = { 30, 60, 120, 190, 220, 260 };
int TDocumentPY[NUM_TDOCUMENTP] = { 50, 100, 10, 180, 20, 260 };
int TDocumentPVisible[NUM_TDOCUMENTP] = { 1, 1, 1, 1, 1, 1 };

// Точка эвакуации

int PEvaX = 850;
int PEvaY = 320;

// Код отрисовки объектов

// Второй игрок

void TPalyer(HDC hdc, int cx, int cy) {
    HBRUSH hbrushPlayer = CreateSolidBrush(RGB(52, 12, 36));
    SelectObject(hdc, hbrushPlayer);
    Rectangle(hdc, cx, cy, cx + 30, cy + 40);//туловище
    Rectangle(hdc, cx + 2, cy + 40, cx + 10, cy + 60);//нога
    Rectangle(hdc, cx + 18, cy + 40, cx + 28, cy + 60);//нога
    Ellipse(hdc, cx + 8, cy - 15, cx + 22, cy);//голова
    DeleteObject(hbrushPlayer);
}

//документ второго игрока

void TDocumentP(HDC hdc, int cx, int cy) {
    HBRUSH hbrushTDoc = CreateSolidBrush(RGB(13, 234, 247));
    SelectObject(hdc, hbrushTDoc);
    Rectangle(hdc, cx, cy, cx + 10, cy + 20);
    DeleteObject(hbrushTDoc);
}

// Солдат

void Soldier(HDC hdc, int cx, int cy) {
    // soldier body серое туловище
    HBRUSH hpenSolBody = CreateSolidBrush(RGB(187, 187, 187));
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx, cy, cx + 30, cy + 50);
    // Ошибка Отрисовка солдата происходит с границами как у туловища автоматически


    // soldier body черная граница туловища
    HPEN hpenSoldier = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, cx, cy + 50);
    LineTo(hdc, cx + 30, cy + 50);
    LineTo(hdc, cx + 30, cy);
    LineTo(hdc, cx, cy);

    // soldier hands левая рука
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx - 10, cy + 2, cx, cy + 30);

    //soldier hands palm левая ладонь
    HBRUSH hpenPalm = CreateSolidBrush(RGB(245, 247, 165));
    SelectObject(hdc, hpenPalm);
    Rectangle(hdc, cx - 9, cy + 27, cx - 1, cy + 30);


    // soldier hands правая рука
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx + 30, cy + 2, cx + 40, cy + 30);

    // soldier hands palm правая ладонь
    SelectObject(hdc, hpenPalm);
    Rectangle(hdc, cx + 31, cy + 27, cx + 39, cy + 30);

    // soldier legs левая нога
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx + 4, cy + 50, cx + 12, cy + 75);
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx + 4, cy + 69, NULL);
    LineTo(hdc, cx + 11, cy + 69);
    MoveToEx(hdc, cx + 4, cy + 71, NULL);
    LineTo(hdc, cx + 11, cy + 71);
    MoveToEx(hdc, cx + 11, cy + 73, NULL);
    LineTo(hdc, cx + 11, cy + 73);

    // soldier legs правая нога
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx + 18, cy + 50, cx + 26, cy + 75);
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx + 18, cy + 69, NULL);
    LineTo(hdc, cx + 25, cy + 69);
    MoveToEx(hdc, cx + 18, cy + 71, NULL);
    LineTo(hdc, cx + 25, cy + 71);
    MoveToEx(hdc, cx + 25, cy + 73, NULL);
    LineTo(hdc, cx + 25, cy + 73);

    // neck шея

    SelectObject(hdc, hpenPalm);
    Rectangle(hdc, cx + 11, cy, cx + 18, cy - 4);
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx + 11, cy, NULL);
    LineTo(hdc, cx + 11, cy - 4);
    LineTo(hdc, cx + 18, cy - 4);
    LineTo(hdc, cx + 18, cy);
    LineTo(hdc, cx + 11, cy);

    // head голова
    SelectObject(hdc, hpenPalm);
    Ellipse(hdc, cx + 4, cy - 23, cx + 26, cy - 2);

    // eye_left левый глаз
    HBRUSH hpenEye = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hpenEye);
    Rectangle(hdc, cx + 10, cy - 16, cx + 12, cy - 13);

    // eye_right правый глаз
    Rectangle(hdc, cx + 17, cy - 16, cx + 19, cy - 13);

    // mouth рот
    Rectangle(hdc, cx + 10, cy - 9, cx + 19, cy - 7);

    // gun автомат
    //Rectangle(hdc, cx - 6, cy + 25, cx + 100, cy + 25);
    //Почему то объекты перестали отрисовываться!!! Ошибка

    DeleteObject(hpenSolBody);
    DeleteObject(hpenSoldier);
    DeleteObject(hpenPalm);
    DeleteObject(hpenEye);
}

//Террорист
void Terror(HDC hdc, int cx, int cy) {
    // soldier body серое туловище
    HBRUSH hpenSolBody = CreateSolidBrush(RGB(112, 155, 116));
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx, cy, cx + 30, cy + 50);


    // soldier body черная граница туловища
    HPEN hpenSoldier = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, cx, cy + 50);
    LineTo(hdc, cx + 30, cy + 50);
    LineTo(hdc, cx + 30, cy);
    LineTo(hdc, cx, cy);

    // soldier hands левая рука
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx - 10, cy + 2, cx, cy + 30);

    //soldier hands palm левая ладонь
    HBRUSH hpenPalm = CreateSolidBrush(RGB(245, 247, 165));
    SelectObject(hdc, hpenPalm);
    Rectangle(hdc, cx - 9, cy + 27, cx - 1, cy + 30);


    // soldier hands правая рука
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx + 30, cy + 2, cx + 40, cy + 30);

    // soldier hands palm правая ладонь
    SelectObject(hdc, hpenPalm);
    Rectangle(hdc, cx + 31, cy + 27, cx + 39, cy + 30);

    // soldier legs левая нога
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx + 4, cy + 50, cx + 12, cy + 75);
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx + 4, cy + 69, NULL);
    LineTo(hdc, cx + 11, cy + 69);
    MoveToEx(hdc, cx + 4, cy + 71, NULL);
    LineTo(hdc, cx + 11, cy + 71);
    MoveToEx(hdc, cx + 11, cy + 73, NULL);
    LineTo(hdc, cx + 11, cy + 73);

    // soldier legs правая нога
    SelectObject(hdc, hpenSolBody);
    Rectangle(hdc, cx + 18, cy + 50, cx + 26, cy + 75);
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx + 18, cy + 69, NULL);
    LineTo(hdc, cx + 25, cy + 69);
    MoveToEx(hdc, cx + 18, cy + 71, NULL);
    LineTo(hdc, cx + 25, cy + 71);
    MoveToEx(hdc, cx + 25, cy + 73, NULL);
    LineTo(hdc, cx + 25, cy + 73);

    // neck шея

    SelectObject(hdc, hpenPalm);
    Rectangle(hdc, cx + 11, cy, cx + 18, cy - 4);
    SelectObject(hdc, hpenSoldier);
    MoveToEx(hdc, cx + 11, cy, NULL);
    LineTo(hdc, cx + 11, cy - 4);
    LineTo(hdc, cx + 18, cy - 4);
    LineTo(hdc, cx + 18, cy);
    LineTo(hdc, cx + 11, cy);

    // head голова
    SelectObject(hdc, hpenPalm);
    Ellipse(hdc, cx + 4, cy - 23, cx + 26, cy - 2);

    // eye_left левый глаз
    HBRUSH hpenEye = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hpenEye);
    Rectangle(hdc, cx + 10, cy - 16, cx + 12, cy - 13);

    // eye_right правый глаз
    Rectangle(hdc, cx + 17, cy - 16, cx + 19, cy - 13);

    // mouth рот
    Rectangle(hdc, cx + 10, cy - 9, cx + 19, cy - 7);

    // gun автомат
    //Rectangle(hdc, cx - 6, cy + 25, cx + 100, cy + 25);
    //Почему то объекты перестали отрисовываться!!! Ошибка

    DeleteObject(hpenSolBody);
    DeleteObject(hpenSoldier);
    DeleteObject(hpenPalm);
    DeleteObject(hpenEye);
}

// document документ

void DocumentSol(HDC hdc, int cx, int cy) {
    //document_1
    HPEN hpenLineBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hpenLineBlack);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, cx + 20, cy);
    LineTo(hdc, cx + 20, cy + 30);
    LineTo(hdc, cx, cy + 30);
    LineTo(hdc, cx, cy);
    // signature
    HBRUSH hpenSignBlue = CreateSolidBrush(RGB(20, 0, 255));
    SelectObject(hdc, hpenSignBlue);
    Rectangle(hdc, cx + 12, cy + 22, cx + 17, cy + 27);
    // lines
    SelectObject(hdc, hpenLineBlack);
    MoveToEx(hdc, cx + 3, cy + 3, NULL);
    LineTo(hdc, cx + 17, cy + 3);
    MoveToEx(hdc, cx + 3, cy + 7, NULL);
    LineTo(hdc, cx + 17, cy + 7);
    MoveToEx(hdc, cx + 3, cy + 11, NULL);
    LineTo(hdc, cx + 17, cy + 11);
    MoveToEx(hdc, cx + 3, cy + 16, NULL);
    LineTo(hdc, cx + 17, cy + 16);

    DeleteObject(hpenLineBlack);
    DeleteObject(hpenSignBlue);
}

// heal_kit аптечка
void HealKit(HDC hdc, int cx, int cy) {
    // grip ручка
    HBRUSH hpenGripBl = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hpenGripBl);
    Rectangle(hdc, cx, cy, cx + 20, cy + 5);
    DeleteObject(hpenGripBl);
    HBRUSH hpenGripS = CreateSolidBrush(RGB(196, 196, 196));
    SelectObject(hdc, hpenGripS);
    Rectangle(hdc, cx, cy + 5, cx + 5, cy + 8);
    Rectangle(hdc, cx + 15, cy + 5, cx + 20, cy + 8);
    DeleteObject(hpenGripS);
    // briefcase кейс
    HPEN hpenLineBl = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hpenLineBl);
    MoveToEx(hdc, cx - 5, cy + 7, NULL);
    LineTo(hdc, cx + 25, cy + 7);
    LineTo(hdc, cx + 25, cy + 27);
    LineTo(hdc, cx - 5, cy + 27);
    LineTo(hdc, cx - 5, cy + 7);
    DeleteObject(hpenLineBl);
    // cross красный крест
    HPEN hpenLineRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    SelectObject(hdc, hpenLineRed);
    MoveToEx(hdc, cx + 10, cy + 12, NULL);
    LineTo(hdc, cx + 10, cy + 22);
    MoveToEx(hdc, cx + 5, cy + 17, NULL);
    LineTo(hdc, cx + 15, cy + 17);
    DeleteObject(hpenLineRed);
}

// патроны
void Ammo(HDC hdc, int cx, int cy) {
    HBRUSH hpenAmmoS = CreateSolidBrush(RGB(251, 224, 131));
    SelectObject(hdc, hpenAmmoS);
    Rectangle(hdc, cx, cy, cx + 20, cy + 40);
    // Почему то срабатывает красная обводка Ошибка
}

//Зона эвакуации
void Evacuation(HDC hdc, int cx, int cy) {
    HPEN hpenLineBl = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hpenLineBl);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, cx + 120, cy);
    LineTo(hdc, cx + 120, cy + 120);
    LineTo(hdc, cx, cy + 120);
    LineTo(hdc, cx, cy);
    DeleteObject(hpenLineBl);
    HPEN hpenLineYel = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
    SelectObject(hdc, hpenLineYel);
    MoveToEx(hdc, cx + 100, cy + 20, NULL);
    LineTo(hdc, cx + 100, cy + 100);
    MoveToEx(hdc, cx + 100, cy + 60, NULL);
    LineTo(hdc, cx + 20, cy + 60);
    MoveToEx(hdc, cx + 20, cy + 20, NULL);
    LineTo(hdc, cx + 20, cy + 100);
    DeleteObject(hpenLineYel);
}

// игроки собирают документы
void SoldierCollectDocument() {
    int i = 0;
    do {
        if (DocumentSolVisible[i] == 1) {
            if (PSoldierX - 20 < DocumentSolX[i] && PSoldierX + 20 > DocumentSolX[i]
                && PSoldierY - 20 < DocumentSolY[i] && PSoldierY + 20 > DocumentSolY[i]) {

                DocumentSolVisible[i] = 0;
            }
        }
        i++;
    } while (i < NUM_DOCUMENTSOL);
}

void TwoPlayerCollectDocument() {
    int i = 0;
    do {
        if (TDocumentPVisible[i] == 1) {
            if (TPlayX - 20 < TDocumentPX[i] && TPlayX + 20 > TDocumentPX[i] && TPlayY - 20 < TDocumentPY[i] &&
                TPlayY + 20 > TDocumentPY[i]) {

                TDocumentPVisible[i] = 0;
            }
        }
        i++;
    } while (i < NUM_TDOCUMENTP);
}

// эвакуация игроков после сбора всех документов

// сколько осталось собрать документов солдату
int CollectSoldier() {
    int i = 0;
    int count = 0;
    do {
        if (DocumentSolVisible[i] == 1) {
            count++;
        }
        i++;
    } while (i < NUM_DOCUMENTSOL);

    return count;
}

// сколько осталось собрать документов второму игроку
int CollectTwoPlayer() {
    int i = 0;
    int count = 0;

    do {
        if (TDocumentPVisible[i] == 1) {
            count++;
        }
        i++;
    } while (i < NUM_TDOCUMENTP);
    
    return count;
}

// все ли прибыли на точку эвакуации
int EvacuationPlayers() {
    if (PSoldierX - 20 < PEvaX
        && PSoldierX + 20 > PEvaX
        && PSoldierY - 20 < PEvaY
        && PSoldierY + 20 > PEvaY
        && TPlayX - 20 < PEvaX
        && TPlayX + 20 > PEvaX
        && TPlayY - 20 < PEvaY
        && TPlayY + 20 > PEvaY) {

        return 0;
    }
}

//рандомное перемещение террористов по таймеру
void RandomPTerror() {
    int dx = rand() % 41 - 20;
    int dy = rand() % 41 - 20;

    PTerrorX += dx;
    PTerrorY += dy;
}

// убиваем солдата
void KillSol() {
    if (PSoldierX - 20 < PTerrorX
        && PSoldierX + 20 > PTerrorX
        && PSoldierY - 20 < PTerrorY
        && PSoldierY + 20 > PTerrorY) {
        HPSol--;
    };
}

// убиваем второго игрока
void KillTPlay() {
    if (TPlayX - 20 < PTerrorX
        && TPlayX + 20 > PTerrorX
        && TPlayY - 20 < PTerrorY
        && TPlayY + 20 > PTerrorY) {
        HPTPlay--;
    };
}

// проверка на сбор документов солдатом
void CollectDocumentSol(HDC hdc) {
    int i = 0;
    do {
        if (DocumentSolVisible[i]) {
            DocumentSol(hdc, DocumentSolX[i], DocumentSolY[i]);
        }
        i++;
    } while (i < NUM_DOCUMENTSOL);
}

//проверка на сбор документов вторым игроком

void CollectTDocumentP(HDC hdc) {
    int i = 0;
    do {
        if (TDocumentPVisible[i]) {
            TDocumentP(hdc, TDocumentPX[i], TDocumentPY[i]);
        }
        i++;
    } while (i < NUM_TDOCUMENTP);
}

// Функции

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
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CREATE:
        srand(time(NULL));
        SetTimer(hWnd, 1, 25, NULL); //запуск таймера(1 это номер таймера,1000 мс = 1 с то есть интервал срабатывания)
        break;

    case WM_TIMER:
        RandomPTerror();
        KillSol();
        if (HPSol == 0) {
            PostQuitMessage(0);
        }
        KillTPlay();
        if (HPTPlay == 0) {
            PostQuitMessage(0);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:
            PSoldierY -= 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case VK_DOWN:
            PSoldierY += 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case VK_LEFT:
            PSoldierX -= 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case VK_RIGHT:
            PSoldierX += 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x57:
            TPlayY -= 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x53:
            TPlayY += 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x41:
            TPlayX -= 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x44:
            TPlayX += 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        SoldierCollectDocument();
        TwoPlayerCollectDocument();
        if (CollectSoldier() == 0 && CollectTwoPlayer() == 0 && EvacuationPlayers() == 0) {
            PostQuitMessage(0);
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            //HealKit(hdc, 250, 200);
            Evacuation(hdc, PEvaX, PEvaY);
            //Ammo(hdc, 300, 200);
            CollectDocumentSol(hdc);
            CollectTDocumentP(hdc);
            TPalyer(hdc, TPlayX, TPlayY);
            Soldier(hdc, PSoldierX, PSoldierY);
            Terror(hdc, PTerrorX, PTerrorY);

            // ошибка в функции Evacuation не удалилась желтая обводка, хотя стоит делитобжект

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