#define _CRT_SECURE_NO_WARNINGS
#include "member.h"
#include "date.h"
#include "status.h"
#include "functions.h"
#include "facebook.h"
#include <iostream>
using namespace std;
int main()
{
	Facebook facebook;


	char name[4][8] = { "shafir", "efron", "ohad", "ronald"};
	char statusStr[10][15] = { "Yala HBS" , "Yarok Ole", "Hakuna Matata", "Ma Nishma?", "Tnu Like", "My Status", 
	"Efron The King", "Shaf Shaf 6", "MHOD", "THIS IS TERNER"};
	char fanPageStr[2][11] = { "Green Apes" , "Vasermilia"};;
	Member efron(name[1], Date(22, 7, 1997));
	Member shafir(name[0], Date(9, 6, 1997));
	Member ohad(name[2], Date(1, 1, 1997));
	Member roni(name[3], Date(2, 2, 1997));
	Status status1(statusStr[0], Date(), Time());
	Status status2(statusStr[1], Date(), Time());
	Status status3(statusStr[2], Date(), Time());
	Status status4(statusStr[3], Date(), Time());
	Status status5(statusStr[4], Date(), Time());
	Status status6(statusStr[5], Date(), Time());
	FanPage mhod(fanPageStr[0]);
	FanPage vs(fanPageStr[1]);
	facebook.addMember(efron);
	facebook.addMember(shafir);
	facebook.addMember(ohad);
	facebook.addMember(roni);
	Member* member1 = facebook.findMember(0);
	Member* member2 = facebook.findMember(1);
	Member* member3 = facebook.findMember(2);
	Member* member4 = facebook.findMember(3);
	facebook.addPage(vs);
	facebook.addPage(mhod);
	FanPage* page1 = facebook.findFanPage(0);
	FanPage* page2 = facebook.findFanPage(1);
	facebook.addStatusToMember(*member1,status1);
	facebook.addStatusToMember(*member1, status4);
	facebook.addStatusToMember(*member2,status2);
	facebook.addStatusToMember(*member3, status3);
	facebook.makeFriends(*member2, *member3);
	facebook.makeFriends(*member1, *member2);
	facebook.makeFriends(*member3, *member4);
	facebook.makeFriends(*member1, *member4);
	facebook.addMemberToPage(*page1, *member2);
	facebook.addMemberToPage(*page1, *member1);
	facebook.addMemberToPage(*page2, *member1);
	facebook.addMemberToPage(*page2, *member4);

	cout << "Welcome to FACEBOOK\n----------------------\nPlease choose one of the following:\n";
	while (getChoice(facebook))
	{
		cout << "\n----------------------\n";
		continue;
	}
}