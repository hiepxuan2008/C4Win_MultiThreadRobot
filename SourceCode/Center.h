#pragma once
#include "Bucket.h"

class Center
{
private:
	Bucket* bucket;
	Point pos;

public:
	void setColor(Color color);
	void setBucket(Bucket* bucket);
	Bucket* getBucket();
	void emptyBucket();

	void draw(HDC hDC);

public:
	Center();
	~Center();
};

