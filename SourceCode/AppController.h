#pragma once
#include "Attributes/Point.h"
#include "Background.h"
#include "Line.h"
#include "ProviderLine.h"
#include "ReceiverLine.h"
#include <vector>

class Line;

class AppController
{
private:
	static AppController* _instance;
	AppController();
public:
	static AppController* getInstance();
	~AppController();

//Windows
private:
	HWND hWnd;
	HINSTANCE hInst;

public:
	Background* background = NULL;
	Center* center = NULL;
	ReceiverLine* line1, *line2, *line3;
	ProviderLine* providerLine;
	std::vector<Line*> lines; //lines Controller

public:
	int numberOfBucket;
	int movingSpeed;

public:
	HANDLE hMutex;
	HANDLE hMutexRobotChecking = NULL;
	bool isChecking = false;

public:
	void Initialize(HWND hWnd, HINSTANCE hInst);

	void OnCreate();
	void OnStart();
	void Refresh();
	void Draw(HDC hDC);
	void OnSize();
	void OnChangeSliderSpeed(HWND hDlg, int pos);

public:
	void StartGameInit();
	void ReleaseMemory();

public:
	bool canProviderLineMove();

	//Threads
public:
	static void ThreadOnStart(LPVOID lpParam);
	static void ThreadMain(LPVOID lpParam);
	static void ThreadRobot1(LPVOID lpParam);
	static void ThreadRobot2(LPVOID lpParam);
	static void ThreadRobot3(LPVOID lpParam);

public:
	bool IsThreadMainComplete();
	bool IsThreadRobot1Complete();
	bool IsThreadRobot2Complete();
	bool IsThreadRobot3Complete();

public:
	int getWidth();
	int getHeight();

	Point getWestPoint();
	Point getNorthPoint();
	Point getEastPoint();
	Point getSouthPoint();
	Point getCenterPoint();
};

