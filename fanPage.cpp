#define _CRT_SECURE_NO_WARNINGS
#include "fanPage.h"
#include "functions.h"
#include <iostream>
#include <string.h>
#include <string>
using namespace std;


FanPage:: FanPage( string str)
{
	_pageName = str;
}

FanPage:: ~FanPage()
{
	vector<Status*>::iterator itr = _pageStatus.begin();
	vector<Status*>::iterator itrEnd = _pageStatus.end();
	for (; itr != itrEnd; ++itr)
	{
		delete* itr;
	}
}

// adds a new status to the page
void FanPage:: addStatus(Status& status)
{
	Status* newStatus = new Status(status.getContent(), status.getDate(), status.getTime());
	_pageStatus.push_back(newStatus);
}

// adds a new fan to the page.
void FanPage::addFan(Member* fanToAdd) noexcept(false)
{
	if (fanToAdd == nullptr)
		throw NullUser();

	vector<Member*>::iterator itr = _pageFans.begin();
	vector<Member*>::iterator itrEnd = _pageFans.end();
	vector<Member*>::iterator tmp = find(itr, itrEnd, fanToAdd);
	if (tmp != itrEnd)
		return;

	_pageFans.push_back(fanToAdd);
	fanToAdd->addPage(this);
}

// removes a member from being a fan of the page
void FanPage::removeFan(Member* fan) noexcept(false)
{
	if (fan == nullptr)
		throw NullUser();

	vector<Member*>::iterator itr = _pageFans.begin();
	vector<Member*>::iterator itrEnd = _pageFans.end();
	vector<Member*>::iterator tmp = find(itr, itrEnd, fan);
	if (tmp == itrEnd)
		return;
	_pageFans.erase(tmp);
	fan->removePage(this);
}

// shows all of the fans of the page.
void FanPage::showAllFans(bool withIndex)
{
	cout << _pageName << " Fans: \n";
	vector<Member*>::const_iterator itr = _pageFans.begin();
	vector<Member*>::const_iterator itrEnd = _pageFans.end();
	if (itr == itrEnd){
		cout << "No Pages" << endl;
	}
	else{
		if (withIndex)
		{
			for (int i = 1; itr != itrEnd; ++itr, ++i)
				cout << i << ". " << (*itr)->getMemberName() << endl;
		}
		else
		{
			for (; itr != itrEnd; ++itr)
				cout << (*itr)->getMemberName() << endl;
		}
	}
}

// shows all of the statuses of the page.
void FanPage::showAllStatus()
{
	vector<Status*>::const_iterator itr = _pageStatus.begin();
	vector<Status*>::const_iterator itrEnd = _pageStatus.end();
	for (; itr != itrEnd; ++itr)
	{
		(*itr)->showStatus();
		cout << "\n---------------------\n";
	}

}

string FanPage:: getPageName()
{
	return _pageName;
}

int FanPage:: getNumOfFans() const
{
	return (int)_pageFans.size();
}

vector<Member*> const FanPage::getPageFans()
{
	return _pageFans;
}

bool FanPage:: operator>(const FanPage& other)const
{
	return getNumOfFans() > other.getNumOfFans();
}

bool FanPage:: operator>(const Member& other)const
{
	return getNumOfFans() > other.getNumOfFriends();
}