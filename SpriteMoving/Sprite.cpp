#include "Sprite.h"

Sprite::Sprite(int x, int y, int width, int height)
{
	Sprite::x = x;
	Sprite::y = y;
	Sprite::width = width;
	Sprite::height = height;
}

int Sprite::getX()
{
	return Sprite::x;
}

int Sprite::getY()
{
	return Sprite::y;
}

int Sprite::getWidth()
{
	return Sprite::width;
}

int Sprite::getHeight()
{
	return Sprite::height;
}

void Sprite::setX(int x)
{
	Sprite::x = x;
}

void Sprite::setY(int y)
{
	Sprite::y = y;
}

void Sprite::setWidth(int width)
{
	Sprite::width = width;
}

void Sprite::setHeight(int height)
{
	Sprite::height = height;
}

void Sprite::setXSpeed(int xSpeed)
{
	Sprite::xSpeed = xSpeed;
}

void Sprite::setYSpeed(int ySpeed)
{
	Sprite::ySpeed = ySpeed;
}

int Sprite::getXSpeed()
{
	return xSpeed;
}

int Sprite::getYSpeed()
{
	return ySpeed;
}

void RectSprite::draw(HDC hdc)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

RectSprite::RectSprite(int x, int y, int width, int height) : Sprite(x, y, width, height){	}

EllipseSprite::EllipseSprite(int x, int y, int width, int height) : Sprite(x, y, width, height){	}

void EllipseSprite::draw(HDC hdc)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

ImageSprite::ImageSprite(int x, int y, int width, int height) : Sprite(x, y, width, height){ }

void ImageSprite::draw(HDC hdc)
{
	StretchBlt(hdc, x, y, width, height, mBit, 0, 0, width * 2, height * 2, SRCCOPY);
}

HDC ImageSprite::getMBit()
{
	return mBit;
}

void Sprite::setMBit(HDC mBit)
{
	this->mBit = mBit;
}
