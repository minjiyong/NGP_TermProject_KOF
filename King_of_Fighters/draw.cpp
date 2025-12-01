#include "draw.h"

void draw_framerectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	RECT rt{ x1, y1, x2, y2 };
	FrameRect(mDC, &rt, hBrush);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	Rectangle(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}