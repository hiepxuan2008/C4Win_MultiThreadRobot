#pragma once
#include "ReceiverLine.h"
class Line2 : public ReceiverLine
{
public:
	Line2();
	~Line2();
	bool isOverLastPlace(Point pos);
	bool isOverFirstPlace(Point pos);
	void draw(HDC hDC);
};

