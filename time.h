#ifndef TIME_H
#define TIME_H

class Time
{
private:
	int hour, minutes;

public:
	Time();
	int getHours();
	int getMinutes();
	void showHour() const;

};
#endif // !TIME_H