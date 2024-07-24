#ifndef MEMBER_EXCEPTION
#define MEMBER_EXCEPTION
#include <string>
#include "UserException.h"


class MemberToHimself : public UserException
{
public:
	std::string addMemberToHimself() const;
	std::string removeMemberToHimself() const;
};

class InvalidBirthDate : public UserException
{

public:
	virtual std::string what() const;
};




#endif //!MEMBER_EXCEPTION