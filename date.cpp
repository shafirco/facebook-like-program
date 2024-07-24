#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
#include <ctime>
#include <iostream>
#include "dateException.h"
using namespace std;

Date::Date() 
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	_day = localtm->tm_mday;
	_month = localtm->tm_mon + 1;
	_year = localtm->tm_year + 1900;
}

Date::Date(int day, int month, int year) noexcept(false)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
	{
		if (day > 31 || day < 1)
			throw InvalidDayException(day);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30 || day < 1)
		{
			throw InvalidDayException(day);
		}
	}
	else if (year % 4 == 0) 
	{
		if (day > 29 || day < 1)
			throw InvalidDayException(day);
	}
	else
	{
		if (day > 28 || day < 1)
			throw InvalidDayException(day);
	}

	if (month > 12 || month < 1)
		throw InvalidMonthException(month);
	if (year > MAX_YEAR)
		throw InvalidYearException(year);
	_day = day;
	_month = month;
	_year = year;
}

int Date::getDay() const
{
	return _day;
}
int Date::getMonth() const
{
	return _month;
}
int Date::getYear() const
{
	return _year;
}


void Date::showDate() const
{
	cout << _day << "." << _month << "." << _year;
}

bool Date::isAboveAge(int age) const
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	int year = localtm->tm_year + 1900;

	if (year - _year >= age)
		return true;
	return false;
}