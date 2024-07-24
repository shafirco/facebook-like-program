#define _CRT_SECURE_NO_WARNINGS


#include "status.h"
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

Status::Status(string str, const Date date, const Time time) : _statusDate(date), _statusTime(time)
{
	_content = str;
}

string Status:: getContent() const
{
	return _content;
}
const Date Status::getDate() const
{
	return _statusDate;
}
const Time Status::getTime() const
{
	return _statusTime;
}

void Status:: showStatus() const
{
	_statusDate.showDate();
	cout << "\n";
	_statusTime.showHour();
	cout << "\n"<< _content;
}

bool Status:: operator== (const Status& other) const
{
	return other._content == this->_content;
}

bool Status:: operator!= (const Status& other) const
{
	return other._content != this->_content;
}

