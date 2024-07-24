#include "memberException.h"
#include <string>
using namespace std;

// returns a message string that you can't make a member friend with himself
string MemberToHimself::addMemberToHimself() const
{
	return "cannot add member to himself";
}

// returns a message string that you can't remove a member from being a friend with himself
string MemberToHimself::removeMemberToHimself() const
{
	return "cannot remove member from himself";
}

// returns a string message of invalid date.
string InvalidBirthDate::what() const
{
	return "invalid date.";
}
