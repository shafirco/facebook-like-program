#ifndef DATE_H
#define DATE_H

const int MAX_YEAR = 2023;

class Date
{
private:
	int _day, _month, _year;
public:
	Date();
	Date(int day, int month, int year) noexcept(false);
	int getDay() const;
	int getMonth()const;
	int getYear()const;
	void showDate() const;
	bool isAboveAge(int age) const;
};
#endif // !DATE_H