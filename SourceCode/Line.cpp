#include "stdafx.h"
#include "Line.h"


Line::Line()
{

}

Line::~Line()
{
	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
		delete (*it);

	for (list<Bucket*>::iterator it = stockBuckets.begin(); it != stockBuckets.end(); ++it)
		delete (*it);
}

int Line::getStockBucketsSize()
{
	return (int)stockBuckets.size();
}