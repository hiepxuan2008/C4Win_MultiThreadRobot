#pragma once
#include "Attributes/Attributes.h"
#include "Bucket.h"
#include "Center.h"
#include <vector>
#include <list>
using namespace std;

enum class Direct { North, East, South, West};

class Line
{
protected:
	list<Bucket*> buckets;
	list<Bucket*> stockBuckets;
	WCHAR* Name;
	Direct direct;
	Point firstPlace, lastPlace;

public:
	Color color;
	int Id;

public:
	Line();
	~Line();

public:
	virtual void move() = 0;
	virtual void draw(HDC hDC) = 0;
	virtual bool isOverLastPlace(Point pos) = 0;
	virtual bool isOverFirstPlace(Point pos) = 0;
	int getStockBucketsSize();
};