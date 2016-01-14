#include "stdafx.h"
#include "ReceiverLine.h"
#include "AppController.h"
#include "Config.h"

ReceiverLine::ReceiverLine()
{
}


ReceiverLine::~ReceiverLine()
{
}

void ReceiverLine::move()
{
	int directX[] = { 0, 1, 0, -1 };
	int directY[] = { -1, 0, 1, 0 };

	for (list<Bucket*>::iterator it = buckets.begin(); it != buckets.end(); ++it)
	{
		(*it)->pos.x += directX[(int)direct] * AppController::getInstance()->movingSpeed;
		(*it)->pos.y += directY[(int)direct] * AppController::getInstance()->movingSpeed;
	}

	// Receive
	if (buckets.size() > 0 && isOverLastPlace(buckets.back()->pos))
	{
		stockBuckets.push_front(buckets.back());
		buckets.pop_back();
	}


	/*Center* center = Center::getInstance();
	if (center->bucket != NULL && center->bucket->IsVerified && center->bucket->Id == this->Id && isOverFirstPlace(buckets.front()->pos))
	{
	buckets.push_front(center->bucket);
	center->bucket = NULL;
	}*/
}

void ReceiverLine::appendCenterBucket()
{
	if (AppController::getInstance()->center->getBucket() != NULL)
	{
		buckets.push_front(AppController::getInstance()->center->getBucket());
		AppController::getInstance()->center->emptyBucket();
	}
}

bool ReceiverLine::isAlright()
{
	if ((buckets.size() == 0) || (buckets.size() > 0 && isOverFirstPlace(buckets.front()->pos)))
		return true;

	return false;
}