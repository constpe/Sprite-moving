#include <windowsx.h>
#include "SpriteMoving.h"

Sprite* sprite; 
RECT screenRect;
bool isMove = false;
bool isAnimation = false;
int areaWidth;
int areaHeight;
int r, g, b;
HMENU hMenu = CreateMenu();
HMENU hPopupMenuFile = CreatePopupMenu();
HMENU hPopupMenuAnimation = CreatePopupMenu();
HBITMAP hBitmap;
BITMAP bm;
HDC hdc, mBit;

ATOM RegWindowClass(HINSTANCE hInstance, LPCTSTR lpzClassName)
{
	WNDCLASS wcWindowClass = { 0 };

	wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
	wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	wcWindowClass.hInstance = hInstance;
	wcWindowClass.lpszClassName = lpzClassName;
	wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;

	return RegisterClass(&wcWindowClass);
}

void ClearWorkspace(HWND hWnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	FillRect(hdc, &rect, (HBRUSH)(COLOR_APPWORKSPACE));
}

void CreateBrush(HDC hdc, int r, int g, int b)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
	SelectObject(hdc, hBrush);
}

void FormMenu(HWND hWnd, HINSTANCE hInstance)
{
	AppendMenu(hPopupMenuFile, MFT_RADIOCHECK, 0, TEXT("Rectangle"));
	AppendMenu(hPopupMenuFile, MFT_RADIOCHECK, 1, TEXT("Ellipse"));
	AppendMenu(hPopupMenuFile, MFT_RADIOCHECK, 2, TEXT("Image"));

	AppendMenu(hPopupMenuAnimation, MFT_RADIOCHECK, 3, TEXT("Start"));
	AppendMenu(hPopupMenuAnimation, MFT_RADIOCHECK, 4, TEXT("Stop"));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenuFile, TEXT("Sprite view"));
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenuAnimation, TEXT("Animation"));

	EnableMenuItem(hPopupMenuAnimation, 4, MF_DISABLED);

	SetMenu(hWnd, hMenu);
	SetMenu(hWnd, hPopupMenuFile);
}

void checkCollision()
{
	if (sprite->getX() <= 0)
	{
		sprite->setX(0);
		sprite->setXSpeed(-sprite->getXSpeed());
	}
	if (sprite->getY() <= 0)
	{
		sprite->setY(0);
		sprite->setYSpeed(-sprite->getYSpeed());
	}
	if (sprite->getX() + sprite->getWidth() >= areaWidth)
	{
		sprite->setX(areaWidth - sprite->getWidth());
		sprite->setXSpeed(-sprite->getXSpeed());
	}
	if (sprite->getY() + sprite->getHeight() >= areaHeight)
	{
		sprite->setY(areaHeight - sprite->getHeight());
		sprite->setYSpeed(-sprite->getYSpeed());
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	int xCenter = GET_X_LPARAM(lParam);
	int yCenter = GET_Y_LPARAM(lParam);
	int delta = GET_WHEEL_DELTA_WPARAM(wParam);
	int x, y, width, height;

	if (sprite)
	{
		x = sprite->getX();
		y = sprite->getY();
		width = sprite->getWidth();
		height = sprite->getHeight();
	}
	
	switch (message)
	{
	case WM_LBUTTONUP:
		if (!isAnimation)
			isMove = !isMove;
		break;
	case WM_MOUSEWHEEL:
		if (!isAnimation)
		{
			switch (GET_KEYSTATE_WPARAM(wParam))
			{
			case MK_SHIFT:
				CreateBrush(hdc, r, g, b);
				sprite->setX(x + delta / 4);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);

				break;
			default:
				CreateBrush(hdc, r, g, b);
				sprite->setY(y - delta / 4);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
		}

		ReleaseDC(hWnd, hdc);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_NUMPAD1:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setX(x - 5);
				sprite->setY(y + 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setXSpeed(-20);
				sprite->setYSpeed(15);
			}

			break;
		case VK_NUMPAD2:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setY(y + 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setYSpeed(15);
			}

			break;
		case VK_NUMPAD3:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setX(x + 5);
				sprite->setY(y + 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setXSpeed(20);
				sprite->setYSpeed(15);
			}

			break;
		case VK_NUMPAD4:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setX(x - 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setXSpeed(-20);
			}

			break;
		case VK_NUMPAD6:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setX(x + 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setXSpeed(20);
			}

			break;
		case VK_NUMPAD7:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setX(x - 5);
				sprite->setY(y - 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setXSpeed(-20);
				sprite->setYSpeed(-15);
			}

			break;
		case VK_NUMPAD8:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setY(y - 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setYSpeed(-15);
			}

			break;
		case VK_NUMPAD9:
			if (!isAnimation)
			{
				CreateBrush(hdc, r, g, b);
				sprite->setX(x + 5);
				sprite->setY(y - 5);
				checkCollision();
				ClearWorkspace(hWnd, hdc);
				sprite->draw(hdc);
			}
			else
			{
				sprite->setXSpeed(20);
				sprite->setYSpeed(-15);
			}

			break;
		}

		ReleaseDC(hWnd, hdc);
		break;
	case WM_MOUSEMOVE:
		if (isMove)
		{
			CreateBrush(hdc, r, g, b);
			sprite->setX(xCenter - width / 2);
			sprite->setY(yCenter - height / 2);
			checkCollision();
			ClearWorkspace(hWnd, hdc);
			sprite->draw(hdc);
		}

		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		CreateBrush(hdc, r, g, b);
		sprite->draw(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			ClearWorkspace(hWnd, hdc);
			r = 255, g = 100, b = 0;
			CreateBrush(hdc, r, g, b);
			sprite = new RectSprite(x, y, 200, 100);
			sprite->draw(hdc);
			break;
		case 1:
			ClearWorkspace(hWnd, hdc);
			r = 90; g = 0; b = 157;
			CreateBrush(hdc, r, g, b);
			sprite = new EllipseSprite(x, y, 200, 100);
			sprite->draw(hdc);
			break;
		case 2:
			ClearWorkspace(hWnd, hdc);
			sprite = new ImageSprite(x, y, bm.bmWidth / 2, bm.bmHeight / 2);
			checkCollision();
			sprite->setMBit(mBit);
			sprite->draw(hdc);
			break;
		case 3:
			sprite->setXSpeed(20);
			sprite->setYSpeed(15);
			EnableMenuItem(hPopupMenuFile, 0, MF_DISABLED);
			EnableMenuItem(hPopupMenuFile, 1, MF_DISABLED);
			EnableMenuItem(hPopupMenuFile, 2, MF_DISABLED);
			EnableMenuItem(hPopupMenuAnimation, 3, MF_DISABLED);
			EnableMenuItem(hPopupMenuAnimation, 4, MF_ENABLED);
			isAnimation = true;
			isMove = false;
			SetTimer(hWnd, 1, 200, NULL);
			break;
		case 4:
			KillTimer(hWnd, 1);
			isAnimation = false;
			EnableMenuItem(hPopupMenuFile, 0, MF_ENABLED);
			EnableMenuItem(hPopupMenuFile, 1, MF_ENABLED);
			EnableMenuItem(hPopupMenuFile, 2, MF_ENABLED);
			EnableMenuItem(hPopupMenuAnimation, 3, MF_ENABLED);
			EnableMenuItem(hPopupMenuAnimation, 4, MF_DISABLED);
			break;
		}

		ReleaseDC(hWnd, hdc);
		break;
	case WM_TIMER:
		sprite->setX(sprite->getX() + sprite->getXSpeed());
		sprite->setY(sprite->getY() + sprite->getYSpeed());
		checkCollision();
		CreateBrush(hdc, r, g, b);
		ClearWorkspace(hWnd, hdc);
		sprite->draw(hdc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_SIZE:
		areaWidth = LOWORD(lParam);
		areaHeight = HIWORD(lParam);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default:
		ReleaseDC(hWnd, hdc);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPCTSTR lpzClass = TEXT("My Window Class");

	if (!RegWindowClass(hInstance, lpzClass))
		return 1;
	
	GetWindowRect(GetDesktopWindow(), &screenRect);
	int x = screenRect.right / 2 - 500;
	int y = screenRect.bottom / 2 - 300;

	HWND hWnd = CreateWindow(lpzClass, TEXT("SpriteMove"), WS_OVERLAPPED | WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU, x, y, 1000, 600, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return 2;

	GetWindowRect(hWnd, &screenRect);

	FormMenu(hWnd, hInstance);

	hBitmap = (HBITMAP)LoadImage(NULL, TEXT("sprite_image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);      
	mBit = CreateCompatibleDC(hdc);      
	SelectObject(mBit, hBitmap);   
	
	r = 255, g = 100, b = 0;
	CreateBrush(hdc, r, g, b);
	sprite = new RectSprite(400, 250, 200, 100);
	sprite->draw(hdc);
	ReleaseDC(hWnd, hdc);

	MSG msg;
	int iGetOk = 0;
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (iGetOk == -1)
			return 3;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteDC(mBit);
	return msg.wParam;
}

