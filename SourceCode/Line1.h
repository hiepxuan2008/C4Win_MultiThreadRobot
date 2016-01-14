#pragma once
#include "ReceiverLine.h"
class Line1 : public ReceiverLine
{
public:
	Line1();
	~Line1();
	bool isOverLastPlace(Point pos);
	bool isOverFirstPlace(Point pos);
	void draw(HDC hDC);
};

