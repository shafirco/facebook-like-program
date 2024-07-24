#ifndef STATUS_H
#define STATUS_H

#include <time.h>
#include "date.h"
#include "time.h"
#include <string>
class Status
{
private:
	Date _statusDate;
	Time _statusTime;
	std::string _content;

public:
	Status(std::string, const Date date,const Time time);
	Status(Status&) = delete;
	std::string getContent() const;
	const Date getDate() const;
	const Time getTime() const;
	void showStatus() const;
	bool operator== (const Status&) const;
	bool operator!= (const Status&) const;
};

#endif // !STATUS_H