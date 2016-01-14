#include "stdafx.h"
#include "Background.h"
#include "AppController.h"
#include "Config.h"

Background::Background()
{
	int pipeWidth = Config::PIPE_WIDTH;
	Point westPoint = AppController::getInstance()->getWestPoint();
	Point northPoint = AppController::getInstance()->getNorthPoint();
	Point centerPoint = AppController::getInstance()->getCenterPoint();
	Point eastPoint = AppController::getInstance()->getEastPoint();
	Point southPoint = AppController::getInstance()->getSouthPoint();
	Stroke stroke;
	stroke.width = 5;

	shapes.push_back(new ShapeLine(Point(westPoint.x, westPoint.y - pipeWidth / 2), Point(northPoint.x - pipeWidth / 2, westPoint.y - pipeWidth / 2), stroke));
	shapes.push_back(new ShapeLine(Point(northPoint.x - pipeWidth / 2, westPoint.y - pipeWidth / 2), Point(northPoint.x - pipeWidth / 2, northPoint.y), stroke));
	shapes.push_back(new ShapeLine(Point(northPoint.x + pipeWidth / 2, westPoint.y - pipeWidth / 2), Point(northPoint.x + pipeWidth / 2, northPoint.y), stroke));
	shapes.push_back(new ShapeLine(Point(northPoint.x + pipeWidth / 2, westPoint.y - pipeWidth / 2), Point(eastPoint.x, westPoint.y - pipeWidth / 2), stroke));
	shapes.push_back(new ShapeLine(Point(northPoint.x + pipeWidth / 2, westPoint.y + pipeWidth / 2), Point(eastPoint.x, westPoint.y + pipeWidth / 2), stroke));
	shapes.push_back(new ShapeLine(Point(northPoint.x + pipeWidth / 2, eastPoint.y + pipeWidth / 2), Point(northPoint.x + pipeWidth / 2, southPoint.y), stroke));
	shapes.push_back(new ShapeLine(Point(northPoint.x - pipeWidth / 2, eastPoint.y + pipeWidth / 2), Point(northPoint.x - pipeWidth / 2, southPoint.y), stroke));
	shapes.push_back(new ShapeLine(Point(westPoint.x, westPoint.y + pipeWidth / 2), Point(northPoint.x - pipeWidth / 2, westPoint.y + pipeWidth / 2), stroke));
}


Background::~Background()
{
	for (size_t i = 0; i < shapes.size(); ++i)
		delete shapes[i];
}

void Background::draw(HDC hDC)
{
	for (size_t i = 0; i < shapes.size(); ++i)
		shapes[i]->draw(hDC);
}
