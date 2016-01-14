#include "stdafx.h"
#include "AppController.h"
#include "Line1.h"
#include "Line2.h"
#include "Line3.h"
#include "ProviderLine.h"
#include "Config.h"
#include "Resource.h"
#include <iostream>
#include <time.h>

AppController* AppController::_instance = NULL;

AppController::AppController()
{
	numberOfBucket = Config::DEFAULT_NUMBER_OF_BUCKETS;
	movingSpeed = Config::DEFAULT_MOVING_SPEEED;
}

AppController::~AppController()
{
	ReleaseMemory();
}

AppController* AppController::getInstance()
{
	if (_instance == NULL)
		_instance = new AppController();
	return _instance;
}

void AppController::Initialize(HWND hWnd, HINSTANCE hInst)
{
	this->hWnd = hWnd;
	this->hInst = hInst;
}

void AppController::OnCreate()
{
	
}

void AppController::ThreadMain(LPVOID lpParam)
{
	while (true)
	{
		if (AppController::getInstance()->IsThreadMainComplete())
		{
			std::cout << "IsThreadMainComplete()" << std::endl;
			return;
		}	

		vector<Line*>& lines = AppController::getInstance()->lines;
		for (size_t i = 1; i < lines.size(); ++i)
			lines[i]->move();

		if (AppController::getInstance()->canProviderLineMove())
		{
			AppController::getInstance()->providerLine->move();
		}

		AppController::getInstance()->Refresh();
		Sleep(50);
	}
}

void AppController::ThreadRobot1(LPVOID lpParam)
{
	while (true)
	{
		if (AppController::getInstance()->IsThreadRobot1Complete())
		{
			std::cout << "IsThreadRobot1Complete()" << std::endl;
			return;
		}

		if (WaitForSingleObject(AppController::getInstance()->hMutex, INFINITE) == 0)
		{
			if (AppController::getInstance()->center->getBucket() != NULL)
			{
				//Checking
				ReceiverLine* line1 = AppController::getInstance()->line1;
				AppController::getInstance()->center->setColor(line1->color);

				AppController::getInstance()->isChecking = true;
				Sleep(1000); //1s
				AppController::getInstance()->isChecking = false;
				//If ok then pass to line1
				Bucket* centerBucket = AppController::getInstance()->center->getBucket();

				if (centerBucket->id == line1->Id)
					line1->appendCenterBucket();

			}
			ReleaseMutex(AppController::getInstance()->hMutex);
		}
	}
}

void AppController::ThreadRobot2(LPVOID lpParam)
{
	while (true)
	{
		if (AppController::getInstance()->IsThreadRobot2Complete())
		{
			std::cout << "IsThreadRobot2Complete()" << std::endl;
			return;
		}

		if (WaitForSingleObject(AppController::getInstance()->hMutex, INFINITE) == 0)
		{
			if (AppController::getInstance()->center->getBucket() != NULL)
			{
				//Checking
				ReceiverLine* line2 = AppController::getInstance()->line2;
				AppController::getInstance()->center->setColor(line2->color);

				AppController::getInstance()->isChecking = true;
				Sleep(1000); //1s
				AppController::getInstance()->isChecking = false;
				//If ok then pass to line2
				Bucket* centerBucket = AppController::getInstance()->center->getBucket();

				if (centerBucket->id == line2->Id)
					line2->appendCenterBucket();

			}
			ReleaseMutex(AppController::getInstance()->hMutex);
		}
	}
}

void AppController::ThreadRobot3(LPVOID lpParam)
{
	while (true)
	{
		if (AppController::getInstance()->IsThreadRobot3Complete())
		{
			std::cout << "IsThreadRobot3Complete()" << std::endl;
			return;
		}

		if (WaitForSingleObject(AppController::getInstance()->hMutex, INFINITE) == 0)
		{
			if (AppController::getInstance()->center->getBucket() != NULL)
			{
				//Checking
				ReceiverLine* line3 = AppController::getInstance()->line3;
				AppController::getInstance()->center->setColor(line3->color);

				AppController::getInstance()->isChecking = true;
				Sleep(1000); //1s
				AppController::getInstance()->isChecking = false;
				//If ok then pass to line3
				Bucket* centerBucket = AppController::getInstance()->center->getBucket();

				if (centerBucket->id == line3->Id)
					line3->appendCenterBucket();

			}
			ReleaseMutex(AppController::getInstance()->hMutex);
		}
	}
}

void AppController::OnStart()
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadOnStart, NULL, 0, 0);
}

void AppController::Refresh()
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, false);
}

void AppController::Draw(HDC hDC)
{
	if (background != NULL)
		background->draw(hDC);

	for (size_t i = 0; i < lines.size(); ++i)
		lines[i]->draw(hDC);

	if (center != NULL)
		center->draw(hDC);
}

void AppController::OnSize()
{

}

void AppController::OnChangeSliderSpeed(HWND hDlg, int pos)
{
	movingSpeed = pos;

	WCHAR buff[100];
	wsprintf(buff, L"%d", movingSpeed);
	SetDlgItemText(hDlg, IDC_STATIC_MOVINGSPEED, buff);

}

void AppController::ThreadOnStart(LPVOID lpParam)
{
	AppController::getInstance()->StartGameInit();

	HANDLE hThreadRobot1, hThreadRobot2, hThreadRobot3, hThreadMain;
	hThreadMain = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMain, NULL, 0, 0);
	hThreadRobot1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRobot1, NULL, 0, 0);
	hThreadRobot2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRobot2, NULL, 0, 0);
	hThreadRobot3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRobot3, NULL, 0, 0);
	HANDLE hAll[4] = { hThreadMain, hThreadRobot1, hThreadRobot2, hThreadRobot3 };

	//Wait until thread process completely
	WaitForMultipleObjects(4, hAll, TRUE, INFINITE);

	WCHAR statement[100];
	wsprintf(statement, L"Each of robots took: \r\nRobot 1: %d bucket(s)\r\nRobot 2: %d bucket(s)\r\nRobot 3: %d bucket(s)", AppController::getInstance()->line1->getStockBucketsSize(), AppController::getInstance()->line2->getStockBucketsSize(), AppController::getInstance()->line3->getStockBucketsSize());
	MessageBox(AppController::getInstance()->hWnd, statement, L"Result", MB_OK);
	EnableMenuItem(GetMenu(AppController::getInstance()->hWnd), ID_START, MF_BYCOMMAND | MF_ENABLED);
}

void AppController::StartGameInit()
{
	ReleaseMemory(); //Release old memory

	//Disable menu item Start
	EnableMenuItem(GetMenu(hWnd), ID_START, MF_BYCOMMAND | MF_GRAYED);

	center = new Center();
	background = new Background();
	line1 = new Line1();
	line2 = new Line2();
	line3 = new Line3();
	providerLine = new ProviderLine();

	lines.resize(0);
	lines.push_back(providerLine);
	lines.push_back(line1);
	lines.push_back(line2);
	lines.push_back(line3);

	//Random Buckets
	srand((UINT)time(NULL));
	list<Bucket*> buckets;
	for (int i = 0; i < numberOfBucket; ++i)
	{
		Bucket* bucket = new Bucket(rand() % 3 + 1);
		buckets.push_back(bucket);
	}
	providerLine->setStockBuckets(buckets);

	hMutex = CreateMutex(NULL, FALSE, L"MutexRobot");
	if (hMutex == NULL)
	{
		MessageBox(hWnd, L"Can't create hMutex", L"Error", MB_OK);
	}
}

void AppController::ReleaseMemory()
{
	delete center;
	delete background;
	for (size_t i = 0; i < lines.size(); ++i)
		delete lines[i];
}

bool AppController::canProviderLineMove()
{
	return line1->isAlright() && line2->isAlright() && line3->isAlright() && !isChecking;
}

bool AppController::IsThreadMainComplete()
{
	return providerLine->total == line1->getStockBucketsSize() + line2->getStockBucketsSize() + line3->getStockBucketsSize();
}

bool AppController::IsThreadRobot1Complete()
{
	return IsThreadMainComplete();
	//return (!AppController::getInstance()->providerLine->isAvailable()) && (AppController::getInstance()->center->bucket == NULL);
}

bool AppController::IsThreadRobot2Complete()
{
	return IsThreadMainComplete();
	//return (!AppController::getInstance()->providerLine->isAvailable()) && (AppController::getInstance()->center->bucket == NULL);
}

bool AppController::IsThreadRobot3Complete()
{
	return IsThreadMainComplete();
	//return (!AppController::getInstance()->providerLine->isAvailable()) && (AppController::getInstance()->center->bucket == NULL);
}

int AppController::getWidth()
{
	int nWidth = 0;
	RECT rect;
	GetClientRect(hWnd, &rect);
	nWidth = rect.right - rect.left;
	
	return nWidth;
}

int AppController::getHeight()
{
	int nHeight = 0;
	RECT rect;
	GetClientRect(hWnd, &rect);
	nHeight = rect.bottom - rect.top;

	return nHeight;
}

Point AppController::getWestPoint()
{
	return Point(20, getHeight() / 2);
}

Point AppController::getNorthPoint()
{
	return Point(getWidth() / 2, 20);
}

Point AppController::getEastPoint()
{
	return Point(getWidth() - 20, getHeight() / 2);
}

Point AppController::getSouthPoint()
{
	return Point(getWidth() / 2, getHeight() - 10);
}

Point AppController::getCenterPoint()
{
	return Point(getWidth() / 2, getHeight() / 2);
}

