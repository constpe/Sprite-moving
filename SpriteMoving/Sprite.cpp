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
	Rectangle(hdc, this->getX(), this->getY(), this->getX() + this->getWidth(), this->getY() + this->getHeight());
}

RectSprite::RectSprite(int x, int y, int width, int height) : Sprite(x, y, width, height){	}

EllipseSprite::EllipseSprite(int x, int y, int width, int height) : Sprite(x, y, width, height){	}

void EllipseSprite::draw(HDC hdc)
{
	Ellipse(hdc, this->getX(), this->getY(), this->getX() + this->getWidth(), this->getY() + this->getHeight());
}
