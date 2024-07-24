#ifndef USER_EXCEPTION
#define USER_EXCEPTION
#include <string>

class UserException
{
public:
	virtual std::string what() const;
};

class DuplicateNameException : public UserException
{
private:
	std::string message;
public:
	DuplicateNameException(std::string name);
	virtual std::string what() const;
};

class NullUser : public UserException
{
public:
	virtual std::string what() const;
};

class UserNotFound : public UserException
{
public:
	virtual std::string what() const;
};

class IndexOutOfRange : public UserException
{
public:
	virtual std::string what() const;
};
#endif // !USER_EXCEPTION
