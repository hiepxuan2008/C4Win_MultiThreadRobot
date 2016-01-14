#pragma once
#include "Line.h"
#include <list>
class Line;

class ProviderLine : public Line
{
public:
	int total;
public:
	ProviderLine();
	~ProviderLine();
	void move();
	void setStockBuckets(std::list<Bucket*> stockBuckets);
	bool isAvailable();
	virtual void draw(HDC hDC);

private:
	bool isOverLastPlace(Point pos);
	bool isOverFirstPlace(Point pos);
};

