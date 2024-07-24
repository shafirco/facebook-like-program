#define _CRT_SECURE_NO_WARNINGS
#include "time.h"
#include <ctime>
#include <iostream>
using namespace std;

Time::Time()
{
	time_t now = time(0);
	tm *localtm = localtime(&now);
	hour = localtm->tm_hour;
	minutes = localtm->tm_min;
}
int Time::getHours()
{
	return hour;
}
int Time::getMinutes()
{
	return minutes;
}

void Time::showHour() const
{
	cout << (hour<10? "0":"") << hour << ":" << (minutes<10 ? "0":"") << minutes;
}