#include "stdafx.h"
#include "Center.h"
#include "AppController.h"

Center::Center()
{
	bucket = NULL;
	pos = Point(AppController::getInstance()->getWidth() / 2, AppController::getInstance()->getHeight() / 2);
}

Center::~Center()
{
}


void Center::setColor(Color color)
{
	if (bucket != NULL)
	{
		bucket->color = color;
	}
}

void Center::setBucket(Bucket* bucket)
{
	this->bucket = bucket;
	if (bucket != NULL)
		this->bucket->pos = this->pos;
}

Bucket* Center::getBucket()
{
	return this->bucket;
}

void Center::emptyBucket()
{
	this->bucket = NULL;
}

void Center::draw(HDC hDC)
{
	if (bucket != NULL)
	{
		bucket->draw(hDC);
	}
}