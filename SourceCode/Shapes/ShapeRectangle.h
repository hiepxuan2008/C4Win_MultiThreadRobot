#pragma once
#include "IShape.h"
class ShapeRectangle : public IShape
{
private:
	int _iLeft, _iTop, _iRight, _iBottom;

public:
	ShapeRectangle();
	ShapeRectangle(int iLeft, int iTop, int iRight, int iBottom);

	void moveHandleTo(Point pMouse);
	void draw(HDC hdc);

	int getWidth();
	int getHeight();
	int getLeft();
	int getTop();
	void update(Point centerPos, int width, int height);
};

