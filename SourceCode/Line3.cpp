#include "stdafx.h"
#include "Line3.h"
#include "AppController.h"
#include "Config.h"

Line3::Line3()
{
	this->Id = 3;
	this->Name = L"LINE 3";
	this->direct = Direct::South;
	this->lastPlace = AppController::getInstance()->getSouthPoint();
	this->firstPlace = this->lastPlace;
	this->firstPlace.y = AppController::getInstance()->getEastPoint().y + Config::PIPE_WIDTH / 2;

	this->color = Color(255, 0, 255);
}


Line3::~Line3()
{
}

bool Line3::isOverLastPlace(Point pos)
{
	if (pos.y - Config::BUCKET_WIDTH / 2 >= lastPlace.y)
		return true;

	return false;
}

bool Line3::isOverFirstPlace(Point pos)
{
	if (pos.y - Config::BUCKET_WIDTH / 2 >= firstPlace.y)
		return true;

	return false;
}

void Line3::draw(HDC hDC)
{
	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
		(*it)->draw(hDC);

	COLORREF oldColor = SetTextColor(hDC, RGB(color.r, color.g, color.b));

	WCHAR buff[100];
	wsprintf(buff, L"(Count=%d)", buckets.size() + stockBuckets.size());
	TextOut(hDC, lastPlace.x + 100, lastPlace.y - 80, Name, wcslen(Name));
	TextOut(hDC, lastPlace.x + 100, lastPlace.y - 50, buff, wcslen(buff));

	SetTextColor(hDC, oldColor);
}