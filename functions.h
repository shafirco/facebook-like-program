#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include "facebook.h"
#include "member.h"
#include "fanPage.h"
#include "status.h"
#include <string>


class Facebook;

void displayMenu();
bool getChoice(Facebook& facebook);
void addNewMember(Facebook& facebook);
std::string* getString();
void addNewFanPage(Facebook& facebook);
void addStatusToPage(Facebook& facebook);
void addStatusToMember(Facebook& facebook);
void showAllStatusOfMember(Facebook& facebook);
void showAllStastusOfPage(Facebook& facebook);
void showLatestStatusOfFriend(Facebook& facebook);
void makeFriends(Facebook& facebook);
void cancelFriendship(Facebook& facebook);
void addMemberToPage(Facebook& facebook);
void removeMemberFromPage(Facebook& facebook);
void showAll(Facebook& facebook);
void showMemberFriends(Facebook& facebook);
void showPageFans(Facebook& facebook);
#endif // !FUNCTIONS_H
