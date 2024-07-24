#include "functions.h"
#include "memberException.h"
#include "dateException.h"
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#define ADD_NEW_MEMBER 1
#define ADD_NEW_FAN_PAGE 2
#define ADD_NEW_STATUS_TO_MEMBER 3
#define ADD_NEW_STATUS_TO_FAN_PAGE 4
#define SHOW_ALL_STATUS_OF_MEMBER 5
#define SHOW_ALL_STATUS_OF_FAN_PAGE 6
#define SHOW_MEMBER_LATEST_FRIENDS_STATUSES 7
#define CREATE_NEW_FRIENDSHIP 8
#define CANCEL_FRIENDSHIP 9
#define ADD_FAN_TO_FAN_PAGE 10
#define REMOVE_FAN_TO_FAN_PAGE 11
#define SHOW_ALL 12
#define SHOW_ALL_MEMBER_FRIENDS 13
#define SHOW_ALL_FANS_OF_FAN_PAGE 14
#define EXIT 15
using namespace std;


// display the system menu.
void displayMenu()
{
	cout << "1 - Add new member.\n2 - Add new fan page.\n3 - Add status to member.\n"
		<<"4 - Add status to fan page.\n5 - Show a member statuses.\n6 - Show a fan page statuses\n"
		<<"7 - Show a member latest 10 statuses.\n8 - Create new friendship between two members.\n"
		<<"9 - Cancel a friendship between 2 friends\n10 - Add a members as a fan to a fan page.\n"
		<<"11 - Remove a member from a fan page.\n12 - Show all members in facebook.\n"
		<<"13 - Show a member friends.\n" "14 - Show a fan page fans.\n15 - Exit\n";
}

// get the user choice number, and based on it executing his choice.
bool getChoice(Facebook& facebook)
{
	int choice;
	displayMenu();
	do {
		cin >> choice;
	} while (choice < 1 || choice > 15);
	getchar();
	switch (choice)
	{
	case ADD_NEW_MEMBER:
	{
		addNewMember(facebook);
		break;
	}
	case ADD_NEW_FAN_PAGE:
	{
		addNewFanPage(facebook);
		break;
	}
	case ADD_NEW_STATUS_TO_MEMBER:
	{
		if(facebook.getNumOfMembers() != 0)
			addStatusToMember(facebook);
		break;
	}
	case ADD_NEW_STATUS_TO_FAN_PAGE:
	{
		if (facebook.getNumOfMembers() != 0)
			addStatusToPage(facebook);
		break;
	}
	case SHOW_ALL_STATUS_OF_MEMBER:
	{
		showAllStatusOfMember(facebook);
		break;
	}
	case SHOW_ALL_STATUS_OF_FAN_PAGE:
	{
		showAllStastusOfPage(facebook);
		break;
	}
	case SHOW_MEMBER_LATEST_FRIENDS_STATUSES:
	{
		showLatestStatusOfFriend(facebook);
		break;
	}
	case CREATE_NEW_FRIENDSHIP:
	{
		makeFriends(facebook);
		break;
	}
	case CANCEL_FRIENDSHIP:
	{
		cancelFriendship(facebook);
		break;
	}
	case ADD_FAN_TO_FAN_PAGE:
	{
		addMemberToPage(facebook);
		break;
	}
	case REMOVE_FAN_TO_FAN_PAGE:
	{
		removeMemberFromPage(facebook);
		break;
	}
	case SHOW_ALL:
	{
		showAll(facebook);
		break;
	}
	case SHOW_ALL_MEMBER_FRIENDS:
	{
		showMemberFriends(facebook);
		break;
	}
	case SHOW_ALL_FANS_OF_FAN_PAGE :
	{
		showPageFans(facebook);
		break;
	}
	case EXIT:
	{
		cout << "------------------\nGOODBYE!\n------------------";
		return false;
	}
	}
	return true;
}

// adds a new member to facebook. 
// gets from user the name and birthdate.
// if there is already a member in facebook with same name, free the name and the new member.
void addNewMember(Facebook& facebook) 
{
	int day, month, year;
	string* name;
	cout << "Please enter the new member's name:\n";
	name = getString();
	cout << "Please enter:\nDay Month Year, seperated with white space\n";
	cin >> day >> month >> year;
	Member* member = nullptr;
	try
	{
		member = new Member(*name, Date(day, month, year));
		facebook.addMember(*member);
	}
	catch (DuplicateNameException& dupName)
	{
		cout << dupName.what();
	}
	catch (InvalidBirthDate& invDate)
	{
		cout << invDate.what();
	}
	catch (InvalidDayException& dayExc)
	{
		cout << dayExc.what() << endl;
	}
	catch (InvalidMonthException& monthExc)
	{
		cout << monthExc.what() << endl;
	}
	catch (InvalidYearException& yearExe)
	{
		cout << yearExe.what() << endl;
	}
	catch (...)
	{
		cout << "something wrong. try again";
	}
	if(member)
		delete member;
	delete name;
}

// adds a new page to facebook. 
// gets from user the name and birthdate.
// if there is already a page in facebook with same name, free the name and the new page.
void addNewFanPage(Facebook& facebook)
{
	string* name;
	cout << "Please enter the new page's name:\n";
	name = getString();

	FanPage* fanPage = new FanPage(*name);
	try
	{
		facebook.addPage(*fanPage);
	}
	catch (DuplicateNameException& dupName)
	{
		cout << dupName.what();
	}
	catch (...)
	{
		cout << "something wrong. try again";
	}
	delete fanPage;
	delete name;
}

// adds a new status to page. 
// gets from user the page to add the status to, the date and the content.
void addStatusToPage(Facebook& facebook) 
{
	int choice;/* checkInputFanPages(facebook);*/
	string* content = nullptr;
	Status* newStatus = nullptr;
	facebook.showPages(true);
	cin >> choice;
	getchar();
	try
	{
		FanPage* fanPageChoice = facebook.findFanPage(choice - 1);
		cout << "\nEnter content: \n";
		content = getString();
		newStatus = new Status(*content, Date(), Time());
		facebook.addStatusToFanPage(*fanPageChoice, *newStatus);
	}
	catch(IndexOutOfRange& indOutOfR)
	{
		cout << indOutOfR.what();
	}
	catch(UserNotFound& unf)
	{
		cout << unf.what();
	}
	catch (...)
	{
		cout << "something wrong. try again";
	}
	if(newStatus)
		delete newStatus;
	if (content)
		delete content;
}

// adds a new status to member. 
// gets from user the member to add the status to, the date and the content.
void addStatusToMember(Facebook& facebook)
{
	int choice;
	string* content = nullptr;
	Status* newStatus = nullptr;
	facebook.showMembers(true);
	cin >> choice;
	getchar();
	try
	{
		Member* memberChoice = facebook.findMember(choice - 1);
		cout << "\nEnter content: \n";
		content = getString();
		newStatus = new Status(*content, Date(), Time());
		facebook.addStatusToMember(*memberChoice, *newStatus);
	}
	catch (IndexOutOfRange& indOutOfR)
	{
		cout << indOutOfR.what();
	}
	catch (UserNotFound& unf)
	{
		cout << unf.what();
	}
	catch (...)
	{
		cout << "something wrong. try again";
	}
	if (newStatus)
		delete newStatus;
	if (content)
		delete content;
}


// gets from user a string.
// returns a string 
string* getString()
{
	string* str = new string();
	getline(cin, *str);
	return str;
}


// gets from user a page choice and shows all of his statuses.
void showAllStastusOfPage(Facebook& facebook)
{
	int choice;
	facebook.showPages(true);
	if (facebook.getNumOfPages() != 0)
	{
		cout << "Please choose one fan page:\n";
		cin >> choice;
		getchar();
		try
		{
			facebook.findFanPage(choice - 1)->showAllStatus();
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what();
		}
		catch (...)
		{
			cout << "something wrong. try again";
		}
	}
}

// gets from user a member choice and shows all of his statuses.
void showAllStatusOfMember(Facebook& facebook)
{
	int choice;
	facebook.showMembers(true);
	if (facebook.getNumOfMembers() != 0)
	{
		cout << "Please choose one member:\n";
		cin >> choice;
		getchar();
		try
		{
			facebook.findMember(choice - 1)->showAllStatus();
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what();
		}
		catch (...)
		{
			cout << "something wrong. try again";
		}
	}
}

// gets from user a member choice and shows all of his friends 10 latest statuses.
void showLatestStatusOfFriend(Facebook& facebook)
{
	int choice;
	facebook.showMembers(true);
	if (facebook.getNumOfMembers() != 0)
	{
		cout << "Please choose one member:\n";
		cin >> choice;
		getchar();
		try
		{
			facebook.findMember(choice - 1)->showLatestFriendsStatus();
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what();
		}
		catch (...)
		{
			cout << "something wrong. try again";
		}
	}
}
// gets from user two members and connect both of them as friends on facebook
void makeFriends(Facebook& facebook)
{
	int choice1, choice2;
	int numOfMembers = facebook.getNumOfMembers();
	facebook.showMembers(true);
	if (numOfMembers != 0)
	{
		cout << "Please choose two members:\n";
		cin >> choice1 >> choice2;
		try
		{
			Member* temp1 = facebook.findMember(choice1 - 1);
			Member* temp2 = facebook.findMember(choice2 - 1);
			facebook.makeFriends(*temp1, *temp2);
		}
		catch (MemberToHimself& exp)
		{
			cout << exp.what() << endl;
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what();
		}
		catch (UserNotFound& unf)
		{
			cout << unf.what();
		}
		catch (...)
		{
			cout << "something wrong. try again";
		}
	}
}
// gets from user two members and remove them from being friends on facebook.
void cancelFriendship(Facebook& facebook)
{

	int choice1;
	int choice2;
	int numOfMembers = facebook.getNumOfMembers();
	facebook.showMembers(true);
	if (numOfMembers != 0)
	{
		cout << "Please choose two members:";
		try
		{
			cin >> choice1;
			getchar();
			cin >> choice2;
			getchar();
			Member* member1 = facebook.findMember(choice1 - 1);
			Member* member2 = facebook.findMember(choice2 - 1);

			facebook.cancelFriendship(*member2, *member1);
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what();
		}
		catch (MemberToHimself& sameMember)
		{
			cout << sameMember.removeMemberToHimself();
		}
	}

}
// gets from the user a member and a page choice.
// adds the member to be a fan of the fan page.
void addMemberToPage(Facebook& facebook)
{
	int page; 
	int member;
	int numOfMembers = facebook.getNumOfMembers();
	int numOfPages = facebook.getNumOfPages();
	facebook.showMembers(true);
	if (numOfMembers != 0) 
	{
		cout << "Please choose one member:";
		cin >> member;
		facebook.showPages(true);
		if (numOfPages != 0)
		{
			cout << "Please choose one page:";
			cin >> page;
			try
			{
				FanPage* pageP = facebook.findFanPage(page - 1);
				Member* memberP = facebook.findMember(member - 1);
				facebook.addMemberToPage(*pageP, *memberP);
			}
			catch (UserNotFound& unf)
			{
				cout << unf.what();
			}
			catch (IndexOutOfRange& indOutOfR)
			{
				cout << indOutOfR.what();
			}
		}
	}
}

// gets a member and a fan page and removes the member from being a fan of the page.
void removeMemberFromPage(Facebook& facebook)
{
	int page; 
	int member;
	int numOfMembers = facebook.getNumOfMembers();
	int numOfPages = facebook.getNumOfPages();
	facebook.showMembers(true);
	if (numOfMembers != 0)
	{
		cout << "Please choose one member:";
		cin >> member;
		facebook.showPages(true);
		if (numOfPages != 0)
		{
			cout << "Please choose one page:";
			cin >> page;
			try
			{
				FanPage* fanPageToRemoveFrom = facebook.findFanPage(page - 1);
				Member* memberToRemove = facebook.findMember(member - 1);
				facebook.removeMemberFromPage(*fanPageToRemoveFrom, *memberToRemove);
			}
			catch (UserNotFound& unf)
			{
				cout << unf.what();
			}
			catch (IndexOutOfRange& indOutOfR)
			{
				cout << indOutOfR.what();
			}
		}
	}
}

// shows all members and pages on facebook.
void showAll(Facebook& facebook)
{
	facebook.showMembers(false);
	cout << "\n----------------\n";
	facebook.showPages(false);

}

// gets a member and shows all of his friends
void showMemberFriends(Facebook& facebook)
{
	int choice;
	facebook.showMembers(true);
	if (facebook.getNumOfMembers() != 0)
	{
		cout << "Please choose one member: ";
		cin >> choice;
		getchar();
		try
		{
			Member* memberP = facebook.findMember(choice - 1);
			facebook.showMemberFriend(*memberP);
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what()<<endl;
		}
		catch (UserNotFound& userNotFound)
		{
			cout << userNotFound.what() << endl;
		}
	}
}

// gets a page and shows all of his fans
void showPageFans(Facebook& facebook)
{
	int choice;
	facebook.showPages(true);
	if (facebook.getNumOfPages() != 0)
	{
		cout << "Please choose one page: ";
		cin >> choice;
		getchar();
		try
		{
			FanPage* fPage = facebook.findFanPage(choice - 1);
			facebook.showPageFans(*fPage);
		}
		catch (IndexOutOfRange& indOutOfR)
		{
			cout << indOutOfR.what() << endl;
		}
		catch (UserNotFound& userNotFound)
		{
			cout << userNotFound.what() << endl;
		}
	}
}

