#include "userException.h"
#include <string>
using namespace std;
string UserException::what() const
{
	return string("Error while adding member to facebook.");
}

DuplicateNameException::DuplicateNameException(string name)
{
	message = string();
	message.append(name);
	message.append(" is already on facebook");
}

string DuplicateNameException::what() const
{
	return message;
}

string NullUser::what() const
{
	return "invalid address.";
}

string UserNotFound::what() const
{
	return "user not found.";
}

string IndexOutOfRange::what() const
{
	return "index out of range.";
}