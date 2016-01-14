#include "stdafx.h"
#include "Line1.h"
#include "AppController.h"
#include "Config.h"

Line1::Line1()
{
	this->Id = 1;
	this->Name = L"LINE 1";
	this->direct = Direct::North;
	this->lastPlace = AppController::getInstance()->getNorthPoint();
	this->firstPlace = this->lastPlace;
	this->firstPlace.y = AppController::getInstance()->getEastPoint().y - Config::PIPE_WIDTH / 2;

	this->color = Color(255, 0, 0);
}

Line1::~Line1()
{
}

bool Line1::isOverLastPlace(Point pos)
{
	if (pos.y + Config::BUCKET_WIDTH / 2 <= lastPlace.y)
		return true;

	return false;
}

bool Line1::isOverFirstPlace(Point pos)
{
	if (pos.y + Config::BUCKET_WIDTH / 2 <= firstPlace.y)
		return true;

	return false;
}

void Line1::draw(HDC hDC)
{
	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
		(*it)->draw(hDC);

	COLORREF oldColor = SetTextColor(hDC, RGB(color.r, color.g, color.b));

	WCHAR buff[100];
	wsprintf(buff, L"(Count=%d)", buckets.size() + stockBuckets.size());
	TextOut(hDC, lastPlace.x + 100, lastPlace.y, Name, wcslen(Name));
	TextOut(hDC, lastPlace.x + 100, lastPlace.y + 30, buff, wcslen(buff));

	SetTextColor(hDC, oldColor);
}