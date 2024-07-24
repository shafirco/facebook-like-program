#define _CRT_SECURE_NO_WARNINGS
#include "member.h"
#include "functions.h"
#include "fanPage.h"
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

Member::Member(string str, const Date birthDay) : _dateOfBirth(birthDay)
{
	_memberName = str;
}


Member:: ~Member()
{
	vector<Status*>::iterator itr = _memberStatus.begin();
	vector<Status*>::iterator itrEnd = _memberStatus.end();
	for (; itr != itrEnd; ++itr)
	{
		delete* itr;
	}
}

// gets a ref to a status and adds its address to the member statuses arr.
void Member::addStatus(Status& status)
{
	Status* statusToAdd = new Status(status.getContent(), status.getDate(), status.getTime());
	_memberStatus.push_back(statusToAdd);
}

void Member:: operator+=(Member& memberToAdd)
{
	addFriend(&memberToAdd);
}

bool Member:: operator>(const Member& other) const
{
	return getNumOfFriends() > other.getNumOfFriends();
}

int Member:: getNumOfStatuses() const
{
	return _memberStatus.size();
}

// add friendToAdd address to this members friends arr.
void Member::addFriend(Member* friendToAdd) noexcept(false)
{
	if (this == friendToAdd)
		throw MemberToHimself();
	else if (friendToAdd == nullptr)
		throw NullUser();

	vector<Member*>::iterator itr = _memberFriends.begin();
	vector<Member*>::iterator itrEnd = _memberFriends.end();
	vector<Member*>::iterator tmp = find(itr, itrEnd, friendToAdd);
	if (tmp != itrEnd)
		return;

	_memberFriends.push_back(friendToAdd);
	friendToAdd->addFriend(this);
}

// removes the friendToRemove address from this member friends arr.
void  Member:: removeFriend(Member* friendToRemove) noexcept(false)
{
	if (friendToRemove == nullptr)
		throw NullUser();
	else if (this == friendToRemove)
		throw MemberToHimself();

	vector<Member*>::iterator itr = _memberFriends.begin();
	vector<Member*>::iterator itrEnd = _memberFriends.end();
	vector<Member*>::iterator tmp = find(itr, itrEnd, friendToRemove);
	if (tmp == itrEnd)
		return;
	_memberFriends.erase(tmp); // add exeption if 
	friendToRemove->removeFriend(this);
}

// add the fanPageToAdd address to this member pages arr.
void Member::addPage(FanPage* fanPageToAdd) noexcept(false)
{
	if (fanPageToAdd == nullptr)
		throw NullUser();

	vector<FanPage*>::iterator itr = _memberFanPages.begin();
	vector<FanPage*>::iterator itrEnd = _memberFanPages.end();
	vector<FanPage*>::iterator tmp = find(itr, itrEnd, fanPageToAdd);
	if (tmp != itrEnd)
		return;

	_memberFanPages.push_back(fanPageToAdd);
	fanPageToAdd->addFan(this);
}

// removes fanPageToRemove from this member pages arr.
void Member:: removePage(FanPage* fanPageToRemove) noexcept(false)
{
	if (fanPageToRemove == nullptr)
		throw NullUser();

	vector<FanPage*>::iterator itr = _memberFanPages.begin();
	vector<FanPage*>::iterator itrEnd = _memberFanPages.end();
	vector<FanPage*>::iterator tmp = find(itr, itrEnd, fanPageToRemove);
	if (tmp == itrEnd)
		return;
	_memberFanPages.erase(tmp);
	fanPageToRemove->removeFan(this);
}

void Member::showAllStatus() const
{

	vector<Status*>::const_iterator itr = _memberStatus.begin();
	vector<Status*>::const_iterator itrEnd = _memberStatus.end();
	for (; itr != itrEnd; ++itr)
	{
		(*itr)->showStatus();
		cout << "\n---------------------\n";
	}
}

string Member:: getMemberName() const
{
	return _memberName;
}

Date Member:: getMemberBirthDate() const
{
	return _dateOfBirth;
}

// shows the member friends.
// if withIndex == true, prints it with fixed indexes.
void Member::showAllFriends(bool withIndex) const
{
	vector<Member*>::const_iterator itr = _memberFriends.begin();
	vector<Member*>::const_iterator itrEnd = _memberFriends.end();
	if (getNumOfFriends() == 0)
		cout << _memberName << "Has no friends yet." <<endl;
	else if (withIndex)
	{
		for (int i = 1; itr != itrEnd; ++itr, ++i)
			cout << i << ". " << (*itr)->getMemberName() << "\n";
	}
	else
	{
		for (; itr != itrEnd; ++itr)
			cout << (*itr)->getMemberName() << "\n";
	}
}

// shows the fanpages the member is fan of.
// if withIndex == true, prints it with fixed indexes.
void Member::showAllFanpages(bool withIndex) const
{
	vector<FanPage*>::const_iterator itr = _memberFanPages.begin();
	vector<FanPage*>::const_iterator itrEnd = _memberFanPages.end();
	if (withIndex) {
		for (int i = 1; itr != itrEnd; ++itr, ++i)
			cout << i << ". " << (*itr)->getPageName() << "\n";
	}
	else {
		for (; itr != itrEnd; ++itr)
			cout << (*itr)->getPageName() << "\n";
	}
}

// shows the last max 10 statuses of this member's friends.
void Member::showLatestFriendsStatus() const
{
	vector<Member*>::const_iterator itr1 = _memberFriends.begin();
	vector<Member*>::const_iterator itrEnd1 = _memberFriends.end();
	vector<Status*>::const_iterator itr2;
	vector<Status*>::const_iterator itrEnd2;
	cout << _memberName << " friends latest statuses: \n\n";
	for (; itr1 != itrEnd1; ++itr1)
	{
		int numOfStatuses = (*itr1)->getNumOfStatuses();
		if (numOfStatuses == 0)
			continue;
		cout << (*itr1)->getMemberName() << ":\n\n";

		itr2 = (*itr1)->_memberStatus.begin();
		itrEnd2 = (*itr1)->_memberStatus.end();

		for (; itr2 != itrEnd2; ++itr2)
		{
			(*itr2)->showStatus();
			cout << "\n---------------\n";
		}
	}

}


int Member::getNumOfFriends() const
{
	return _memberFriends.size();
}

vector<Member*> const Member::getAllMembers()
{
	return _memberFriends;
}

bool Member:: operator>(const FanPage& other) const
{
	return getNumOfFriends() > other.getNumOfFans();
}