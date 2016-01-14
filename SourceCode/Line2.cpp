#include "stdafx.h"
#include "Line2.h"
#include "AppController.h"
#include "Config.h"

Line2::Line2()
{
	this->Id = 2;
	this->Name = L"LINE 2";
	this->direct = Direct::East;
	this->lastPlace = AppController::getInstance()->getEastPoint();
	this->firstPlace = this->lastPlace;
	this->firstPlace.x = AppController::getInstance()->getNorthPoint().x + Config::PIPE_WIDTH / 2;

	this->color = Color(0, 0, 255);
}


Line2::~Line2()
{
}

bool Line2::isOverLastPlace(Point pos)
{
	if (pos.x - Config::BUCKET_WIDTH / 2 >= lastPlace.x)
		return true;

	return false;
}

bool Line2::isOverFirstPlace(Point pos)
{
	if (pos.x - Config::BUCKET_WIDTH / 2 >= firstPlace.x)
		return true;

	return false;
}

void Line2::draw(HDC hDC)
{
	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
		(*it)->draw(hDC);

	COLORREF oldColor = SetTextColor(hDC, RGB(color.r, color.g, color.b));

	WCHAR buff[100];
	wsprintf(buff, L"(Count=%d)", buckets.size() + stockBuckets.size());
	TextOut(hDC, lastPlace.x - 50, lastPlace.y - 130, Name, wcslen(Name));
	TextOut(hDC, lastPlace.x - 50, lastPlace.y - 100, buff, wcslen(buff));

	SetTextColor(hDC, oldColor);
}