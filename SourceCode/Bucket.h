#pragma once
#include "Shapes/Shapes.h"

class Bucket
{
public:
	int id;
	ShapeRectangle shape;
	Point pos;
	Color color;
	
public:
	void draw(HDC hDC);

public:
	Bucket(int id);
	~Bucket();
};

