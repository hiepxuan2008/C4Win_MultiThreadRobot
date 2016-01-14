#include "stdafx.h"
#include "ProviderLine.h"
#include "AppController.h"
#include "Config.h"
#include <iostream>

ProviderLine::ProviderLine()
{
	this->direct = Direct::East;
	this->firstPlace = Point(50, AppController::getInstance()->getHeight() / 2);
	this->lastPlace = Point(AppController::getInstance()->getWidth() / 2, AppController::getInstance()->getHeight() / 2);

	this->color = Color(0, 0, 0);
}

ProviderLine::~ProviderLine()
{
}

bool ProviderLine::isOverLastPlace(Point pos)
{
	if (pos.x >= lastPlace.x)
		return true;

	return false;
}

bool ProviderLine::isOverFirstPlace(Point pos)
{
	if (pos.x >= firstPlace.x + Config::DISTANCE_BETWEEN_ADJACENT_BUCKETS)
		return true;

	return false;
}

void ProviderLine::move()
{
	int directX[] = { 0, 1, 0, -1 };
	int directY[] = {-1, 0, 1, 0};

	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
	{
		(*it)->pos.x += directX[(int)direct] * AppController::getInstance()->movingSpeed;
		(*it)->pos.y += directY[(int)direct] * AppController::getInstance()->movingSpeed;
	}

	if (buckets.size() > 0 && isOverLastPlace(buckets.back()->pos)) {
		Bucket* bucket = buckets.back();
		buckets.pop_back();
		AppController::getInstance()->center->setBucket(bucket);
	}

	if (stockBuckets.size() > 0 && (buckets.size() == 0 || isOverFirstPlace(buckets.front()->pos))) {
		buckets.push_front(stockBuckets.back());
		buckets.front()->pos = this->firstPlace;

		stockBuckets.pop_back();
	}
}

void ProviderLine::setStockBuckets(list<Bucket*> stockBuckets)
{
	this->stockBuckets = stockBuckets;
	total = this->stockBuckets.size();
}

bool ProviderLine::isAvailable()
{
	return (this->buckets.size() + this->stockBuckets.size()) > 0;
}

void ProviderLine::draw(HDC hDC)
{
	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
		(*it)->draw(hDC);

	COLORREF oldColor = SetTextColor(hDC, RGB(color.r, color.g, color.b));

	WCHAR buff[100];
	wsprintf(buff, L"Total=%d", this->total);
	TextOut(hDC, firstPlace.x, firstPlace.y - 130, buff, wcslen(buff));
	wsprintf(buff, L"Remaining=%d", this->stockBuckets.size() + this->buckets.size());
	TextOut(hDC, firstPlace.x, firstPlace.y - 100, buff, wcslen(buff));

	SetTextColor(hDC, oldColor);
}