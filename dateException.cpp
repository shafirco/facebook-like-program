#include "dateException.h"
#include <string>

using namespace std;

string DateException::what() const
{
	return "Wrong date values. try again\n";
}

// init wrong day.
InvalidDayException::InvalidDayException(int day)
{
	wrongDay = day;
}

// returns a string with a suitable message to to exception
string InvalidDayException::what() const
{
	string msg = "day value can't be ";
	msg.append(to_string(wrongDay));
	return msg;
}

InvalidMonthException::InvalidMonthException(int month)
{
	wrongMonth = month;
}

// returns a string with a suitable message to to exception
string InvalidMonthException::what() const
{
	string msg = "month value can't be ";
	msg.append(to_string(wrongMonth));
	return msg;
}

InvalidYearException::InvalidYearException(int year)
{
	wrongYear = year;
}

// returns a string with a suitable message to to exception
string InvalidYearException::what() const
{
	string msg = "year value can't be ";
	msg.append(to_string(wrongYear));
	return msg;
}