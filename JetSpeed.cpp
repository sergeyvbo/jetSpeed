// JetSpeed.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "JetSpeed.h"
#include "cCheats.h"

#define MAX_LOADSTRING 100



// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


char tWindowName[256] = "Battlefield 4"; /* tWindowName ? Target Window Name */
HWND tWnd;

DWORD pid = 0; //Process ID
HANDLE pHandle = 0; //Process handle

HWND hWnd;

LocalPlayer lp;
int res = 500;
int res2 = 0;
COLORREF textColor = RGB(128, 128, 128);

void SetWindowToTarget()
{
	char ErrorMsg[125];

	while(true)
	{
		tWnd = FindWindowA(0, tWindowName);

		if (tWnd)
		{
			GetWindowThreadProcessId(tWnd, &pid);
			pHandle = OpenProcess(PROCESS_VM_READ, false, pid);
		}
		else
		{
			Sleep(10000);
			//exit(1);
		}
		Sleep(100);
	}
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_JETSPEED, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JETSPEED));

	SetTimer(hWnd, 10001, 100, NULL);

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	KillTimer(hWnd, 10001);

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JETSPEED));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_JETSPEED);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char s[80];
	HFONT f;

	static double v = 100.0;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...

		f = CreateFont(200,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
        SelectObject(hdc, f);

		RECT r;
		r.left = 0;
		r.top = 0;
		r.right = 800;
		r.bottom = 500;

		SetTextColor(hdc, textColor);

		sprintf_s(s, "%.2f", lp.VehicleSpeed);
		DrawTextA(hdc, s, -1, &r, DT_LEFT | DT_TOP);
		DeleteObject(f);

		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		res = updateFromGameContext();
		res2 = readLocalPlayer(&lp);
		textColor = getTextColor(lp.VehicleSpeed);
		InvalidateRect(hWnd, NULL, true);
		playSound(lp.VehicleSpeed);
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

COLORREF getTextColor(double speed) 
{
	int R=0, G=255, B=0;
	
	// RED COLOR
	if (speed <= 312.0)
		R = 0;
	if (speed > 312.0 && speed <= 320.0)
		R = scaleColor(speed, 312.0, 320.0);
	if (speed > 320.0)
		R = scaleColor(speed, 320.0, 400.0, 128.0, 255.0, false);

	// GREEN COLOR
	if (speed < 300.0)
		G = 0;
	if (speed >= 300.0 && speed < 312.0)
		G = scaleColor(speed, 300.0, 312.0);
	if (speed >=312.0 && speed < 326.0)
		G = scaleColor(speed, 312.0, 326.0, 0.0, 255.0, false);
	if (speed >= 326)
		G = 0;

	// BLUE COLOR
	if (speed >= 312.0)
		B = 0;
	if (speed >= 300.0 && speed < 312.0)
		B = scaleColor(speed, 300.0, 312.0, 0.0, 255.0, false);
	if (speed < 300.0)
		B = scaleColor(speed, 0.0, 300.0);



	return RGB(R, G, B);
}

int scaleColor(double speed, double minSpeed, double maxSpeed, double minColor, double maxColor, bool minToMax)
{
	double step = (maxColor - minColor) / (maxSpeed - minSpeed);
	double color = min(maxColor, ((speed - minSpeed) * step + minColor));
	if (minToMax)
		return (int)color;
	else
		return 255 - (int)color;
}

void playSound(double speed)
{
	if (speed > 320)
		MessageBeep(MB_OK);
	if(speed > 260 && speed < 300)
		MessageBeep(MB_ICONHAND);
}