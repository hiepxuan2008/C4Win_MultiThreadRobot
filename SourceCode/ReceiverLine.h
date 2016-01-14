#pragma once
#include "Line.h"
class ReceiverLine : public Line
{
public:
	ReceiverLine();
	~ReceiverLine();
	virtual void draw(HDC hDC) = 0;
	void move();
	virtual bool isOverLastPlace(Point pos) = 0;
	virtual bool isOverFirstPlace(Point pos) = 0;
	void appendCenterBucket();
	bool isAlright();
	
};

