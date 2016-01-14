#include "ShapeRectangle.h"

ShapeRectangle::ShapeRectangle()
{
	_iLeft = _iTop = _iBottom = _iRight = 0;
}

ShapeRectangle::ShapeRectangle(int iLeft, int iTop, int iRight, int iBottom) : _iLeft(iLeft), _iTop(iTop), _iRight(iRight), _iBottom(iBottom)
{
}

void ShapeRectangle::moveHandleTo(Point pMouse)
{
	_iRight = pMouse.x;
	_iBottom = pMouse.y;
}

void ShapeRectangle::draw(HDC hdc)
{
	HPEN hPen = CreatePen(_stroke.style, _stroke.width, RGB(_stroke.color.r, _stroke.color.g, _stroke.color.b));
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HGDIOBJ hOld = SelectObject(hdc, hPen);
	HGDIOBJ hOld2 = SelectObject(hdc, hBrush);
	Rectangle(hdc, _iLeft, _iTop, _iRight, _iBottom);

	SelectObject(hdc, hOld);
	SelectObject(hdc, hOld2);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

int ShapeRectangle::getWidth()
{
	return abs(_iRight - _iLeft);
}

int ShapeRectangle::getHeight()
{
	return abs(_iBottom - _iTop);
}

int ShapeRectangle::getLeft()
{
	return _iLeft < _iRight ? _iLeft : _iRight;
}

int ShapeRectangle::getTop()
{
	return _iTop < _iBottom ? _iTop : _iBottom;
}

void ShapeRectangle::update(Point centerPos, int width, int height)
{
	int haftWidth = width / 2;
	int haftHeight = height / 2;

	this->_iLeft = centerPos.x - haftWidth;
	this->_iTop = centerPos.y - haftHeight;
	this->_iRight = centerPos.x + haftWidth;
	this->_iBottom = centerPos.y + haftHeight;
}