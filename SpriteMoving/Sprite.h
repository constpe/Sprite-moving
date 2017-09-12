#include <Windows.h>

#ifndef __Sprite_h__
#define __Sprite_h__

class Sprite
{
protected:
	int x;
	int y;
	int width;
	int height;
	int xSpeed;
	int ySpeed;
	HDC mBit;
public:
	Sprite(int x, int y, int width, int height);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setXSpeed(int xSpeed);
	void setYSpeed(int ySpeed);
	int getXSpeed();
	int getYSpeed();
	void setMBit(HDC mBit);
	virtual void draw(HDC hdc) = 0;
};

class RectSprite : public Sprite
{
public:
	RectSprite(int x, int y, int width, int height);
	virtual void draw(HDC hdc);
};

class EllipseSprite : public Sprite
{
public:
	EllipseSprite(int x, int y, int width, int height);
	virtual void draw(HDC hdc);
};

class ImageSprite : public Sprite
{
public:
	ImageSprite(int x, int y, int width, int height);
	HDC getMBit();
	virtual void draw(HDC hdc);
};

#endif