#include "facebook.h"
#include "functions.h"

#include <iostream>
using namespace std;

Facebook::Facebook()
{
}

// d'tor for Facebook class
// delete all members and pages allocations. 
Facebook::~Facebook()
{
	vector<FanPage*>::const_iterator itr1 = _fanPages.begin();
	vector<FanPage*>::const_iterator itrEnd1 = _fanPages.end();
	vector<Member*>::const_iterator itr2 = _members.begin();
	vector<Member*>::const_iterator itrEnd2 = _members.end();

	for (; itr1 != itrEnd1; ++itr1)
	{
		delete *itr1;
	}
	for (; itr2 != itrEnd2; ++itr2)
	{
		delete *itr2;
	}
}

int Facebook::getNumOfMembers() const
{
	return (int)_members.size();
}

int Facebook::getNumOfPages() const
{
	return (int)_fanPages.size();
}

// gets a ref to Member and adds it to facebook
void Facebook::addMember(Member& newMember) noexcept(false)
{
	if (isNameMemberUsed(newMember)) // to avoid duplicate names on facebook
	{
		throw DuplicateNameException(newMember.getMemberName());
	}
	else if (!(newMember.getMemberBirthDate().isAboveAge(MAX_AGE))) // to avoid teenagers join our system
	{
		throw InvalidBirthDate();
	}
	else
	{
		Member* memberToAdd = new Member(newMember.getMemberName(), newMember.getMemberBirthDate());
		_members.push_back(memberToAdd);
	}
}

// gets a ref to FanPage and adds it to facebook
bool Facebook::addPage(FanPage& newPage) noexcept(false)
{
	if (isNameFanPageUsed(newPage))
		throw DuplicateNameException(newPage.getPageName()); // to avoid two pages with same name
	else
	{
		FanPage* fanPageToAdd = new FanPage(newPage.getPageName());
		_fanPages.push_back(fanPageToAdd);
		return true;
	}
	return false;
}

// shows all members in facebook.
void Facebook::showMembers(bool index) const
{
	cout << "Members: \n";

	vector<Member*>::const_iterator itr = _members.begin();
	vector<Member*>::const_iterator itrEnd = _members.end();
	if (itr == itrEnd)
	{
		cout << "No Members"<< endl;
	}
	else if(index) // if there is a need in fixed indexes (for choosing purposes etc.)
	{
		for (int i=1; itr != itrEnd;++i, ++itr)
			cout << i << ". " << (*itr)->getMemberName() << endl;
	}
	else
	{
		for (; itr != itrEnd; ++itr)
			cout << (*itr)->getMemberName() << endl;
	}
}

// shows all pages in facebook
void Facebook::showPages(bool index) const
{
	cout << "Pages: \n";
	vector<FanPage*>::const_iterator itr = _fanPages.begin();
	vector<FanPage*>::const_iterator itrEnd = _fanPages.end();
	if (itr == itrEnd)
	{
		cout << "No Pages" << endl;
	}
	else if(index)// if there is a need in fixed indexes (for choosing purposes etc.)
	{
		for (int i = 1; itr != itrEnd; ++i, ++itr)
			cout << i << ". " << (*itr)->getPageName() << endl;
	}
	else
	{
		for (; itr != itrEnd; ++itr)
			cout << (*itr)->getPageName() << endl;
	}

}



bool Facebook::isNameMemberUsed(Member& member) const
{
	vector<Member*>::const_iterator itr = _members.begin();
	vector<Member*>::const_iterator itrEnd = _members.end();

	for (; itr != itrEnd; ++itr)
	{
		if (member.getMemberName() == (*itr)->getMemberName())
			return true;
	}
	return false;
}

// a boolean function that get a ref to fanPage and returns true if the name of the fanPage's name is taken.
bool Facebook::isNameFanPageUsed(FanPage& fanPage) const
{
	vector<FanPage*>::const_iterator itr = _fanPages.begin();
	vector<FanPage*>::const_iterator itrEnd = _fanPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if (fanPage.getPageName() == (*itr)->getPageName())
			return true;
	}
	return false;
}

// gets a ref to fanPage and a ref to Member and removes the member from being a fan of the fan page
// if the member is not a fan of page, throws an exception.
void Facebook:: removeMemberFromPage(FanPage& page, Member& member) noexcept(false)
{
	if (!findFanPage(page) || !findMember(member))
		throw UserNotFound();

	page.removeFan(&member);
}

// gets two refs to Member and cancel their friendship.
// if they are not friends, throws an exception.
void Facebook::cancelFriendship(Member& mem1, Member& mem2) noexcept(false)
{
	if (!findMember(mem2) || !findMember(mem1))
		throw UserNotFound();

	mem1.removeFriend(&mem2);
}

// a function that gets an index of a fanPage* and returns the element.
// if the index isn't in range of the size of the vector throws an exception
FanPage* Facebook::findFanPage(int index)noexcept(false)
{
	if (index < 0 || index >= getNumOfPages())
		throw IndexOutOfRange();

	vector<FanPage*>::iterator itr = _fanPages.begin() + index;
	return (*itr);
	//exception
}

// a function that gets an index of a fanPage* and returns the element.
// if the index isn't in range of the size of the vector throws an exception
Member* Facebook::findMember(int index) noexcept(false)
{
	if (index < 0 || index >= getNumOfMembers())
		throw IndexOutOfRange();

	vector<Member*>::iterator itr = _members.begin() + index;
	return (*itr);
}

// gets a ref to fanPage and Member and adds the member to be a fan of the page.
void Facebook::addMemberToPage(FanPage& page, Member& member) noexcept(false)
{
	if (!findFanPage(page) || !findMember(member))
		throw UserNotFound();

	page.addFan(&member);
}

// gets a ref to status and member and adds the status to the member statuses.
void Facebook::addStatusToMember(Member& member, Status& status)noexcept(false)
{
	if (findMember(member) == nullptr) // member could be a ref to some member outside facebook, so we want to avoid that.
		throw UserNotFound();
    
	member.addStatus(status);
}

// gets a ref to status and page and adds the status to the page statuses.
void Facebook::addStatusToFanPage(FanPage& fanPage, Status& status)noexcept(false)
{
	if (findFanPage(fanPage) == nullptr)
		throw UserNotFound();

	fanPage.addStatus(status);
}

// gets two refs of members and make them friends
// if member1 and member2 are same member, throws an exception
void Facebook::makeFriends(Member& member1, Member& member2) noexcept(false)
{
	if (member1.getMemberName() == member2.getMemberName())
		throw MemberToHimself();
	else if (!findMember(member1)|| !findMember(member2))
		throw UserNotFound();
	member1.addFriend(&member2);
}

// a function to find a fan page inside facebook.
// gets a ref to fanPage and returns a pointer to that fanPage
FanPage* Facebook::findFanPage(FanPage& fanPage)
{

	vector<FanPage*>::iterator itr = _fanPages.begin();
	vector<FanPage*>::iterator itrEnd = _fanPages.end();
	vector<FanPage*>::iterator tmp = find(itr, itrEnd, &fanPage);

	if (tmp != itrEnd)
		return *tmp;
	return nullptr;
}

// a function to find a Member inside facebook.
// gets a ref to Member and returns a pointer to that Member
Member* Facebook::findMember(Member& member)
{
	vector<Member*>::iterator itr = _members.begin();
	vector<Member*>::iterator itrEnd = _members.end();
	vector<Member*>::iterator tmp = find(itr, itrEnd, &member);

	if (tmp != itrEnd)
		return *tmp;
	return nullptr;
}

// a function to show a member from facebook's friends
// gets a ref to that member.
// if the member isn't on facebook, throws an exception
void Facebook::showMemberFriend(Member& member) noexcept(false)
{
	if (!findMember(member))
		throw UserNotFound();
	member.showAllFriends(false);
}

// a function to show a fanPage fans.
// gets a ref to that fanPage.
// if the fanPage isn't on facebook, throws an exception
void Facebook::showPageFans(FanPage& fPage) noexcept(false)
{
	if (!findFanPage(fPage))
		throw UserNotFound();
	fPage.showAllFans(false);
}