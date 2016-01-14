#include "stdafx.h"
#include "Bucket.h"
#include "Config.h"

Bucket::Bucket(int id)
{
	this->id = id;
	this->color = Color(0, 0, 0); //Default black color
}

Bucket::~Bucket()
{
	
}

void Bucket::draw(HDC hDC)
{
	Stroke stroke;
	stroke.width = 3;
	stroke.color = color;

	//Draw rectangle of the bucket
	shape.setStroke(stroke);
	shape.update(pos, Config::BUCKET_WIDTH, Config::BUCKET_HEIGHT);
	shape.draw(hDC);
	
	//Draw id in center of the bucket
	WCHAR text[10];
	wsprintf(text, L"%d", this->id);
	UINT oldAlign = SetTextAlign(hDC, TA_CENTER);
	UINT oldColor = SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, pos.x, pos.y, text, wcslen(text));
	SetTextColor(hDC, oldColor);
	SetTextAlign(hDC, oldAlign);
}