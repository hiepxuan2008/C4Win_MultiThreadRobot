#pragma once
#include "Shapes/Shapes.h"
#include <vector>

class Background
{
private:
	std::vector<IShape*> shapes;
public:
	void draw(HDC hDC);

public:
	Background();
	~Background();
};