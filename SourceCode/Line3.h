#pragma once
#include "ReceiverLine.h"
class Line3 : public ReceiverLine
{
public:
	Line3();
	~Line3();
	bool isOverLastPlace(Point pos);
	bool isOverFirstPlace(Point pos);
	void draw(HDC hDC);
};

