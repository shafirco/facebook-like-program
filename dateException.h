#ifndef DATE_EXCEPTION_H
#define DATE_EXCEPTION_H
#include <string>

class DateException
{
private:

public:
	virtual std::string what() const;
};

class InvalidDayException : public DateException
{
private:
	int wrongDay;
public:
	InvalidDayException(int day);
	virtual std::string what() const;
};

class InvalidMonthException : public DateException
{
private:
	int wrongMonth;
public:
	InvalidMonthException(int month);
	virtual std::string what() const;
};

class InvalidYearException : public DateException
{
private:
	int wrongYear;
public:
	InvalidYearException(int year);
	virtual std::string what() const;
};


#endif // !DATE_EXCEPTION_H
