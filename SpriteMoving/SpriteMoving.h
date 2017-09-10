#include <Windows.h>
#include "Sprite.h"

#ifndef __SPRITEMOVING_H__
#define __SPRITEMOVING_H__

ATOM RegisterWindowClass(HINSTANCE hInstance, LPCTSTR lpzClassName);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void ClearWorkspace(HWND hWnd, HDC hdc);

void checkCollision();

void FormMenu(HWND hWnd, HINSTANCE hInstance);

#endif