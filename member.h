#ifndef MEMBER_H
#define MEMBER_H


#include "date.h"
#include "status.h"
#include "fanPage.h"
#include "memberException.h"
#include <string>
#include <vector>
const int NOT_FOUND = -1;

class FanPage;

class Member {

private:
	Date _dateOfBirth;
	std::string _memberName;
	std::vector<Status*> _memberStatus;
	std::vector<Member*> _memberFriends;
	std::vector<FanPage*> _memberFanPages;

public:
	Member(std::string str, const Date birthDay);
	Member(const Member&) = delete;
	~Member();
	
	void addFriend(Member* friendToAdd) noexcept(false);
	void removeFriend(Member* friendToRemove) noexcept(false);
	void addPage(FanPage* fanPageToAdd) noexcept(false);
	void removePage(FanPage* fanPageToRemove) noexcept(false);
	void addStatus(Status& statusToAdd); 
	std::string getMemberName() const;
	int getNumOfStatuses() const;
	Date getMemberBirthDate() const;
	void showAllStatus() const;
	void showAllFanpages(bool withIndex) const;
	void showAllFriends(bool withIndex) const;
	void showLatestFriendsStatus() const;
	int getNumOfFriends()const;
	std::vector<Member*> const getAllMembers(); // not use//
	void operator+=(Member& memberToAdd);
	bool operator>(const Member& other) const;
	bool operator>(const FanPage& other) const;
};
#endif // !MEMBER_H