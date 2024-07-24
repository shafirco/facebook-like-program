#ifndef FAN_PAGE_H
#define FAN_PAGE_H
#include "status.h"
#include "member.h"
#include <string>
#include <vector>
class Member;

class FanPage {
private:
	std::string _pageName;
	std::vector <Member*> _pageFans;
	std::vector<Status*> _pageStatus;
public:
	FanPage(std::string str);
	~FanPage();
	std::string getPageName();
	void addFan(Member* member)noexcept(false);
	void removeFan(Member* member)noexcept(false);
	void showAllFans(bool withIndex);
	void showAllStatus();
	void addStatus(Status&);
	int getNumOfFans()const;
	std::vector<Member*> const getPageFans();
	bool operator>(const FanPage& other)const;
	bool operator>(const Member& other)const;

};
#endif // !FAN_PAGE_H
