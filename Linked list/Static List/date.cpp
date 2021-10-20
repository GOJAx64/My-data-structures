#include "date.h"

using namespace std;

int Date::toInt() const
{
    return year * 10000 + month * 100 + day * 1;
}

int Date::getYear() const
{
    return year;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

string Date::toString() const
{
    char myDate[11];

    sprintf(myDate, "%04i/%02i/%02i", year, month, day);

    return myDate;
}

void Date::setYear(const int& y)
{
    year = y;
}

void Date::setMonth(const int& m)
{
    month = m;
}

void Date::setDay(const int& d)
{
    day = d;
}

bool Date::operator==(const Date& d) const
{
    return toInt() == d.toInt();
}

bool Date::operator!=(const Date& d) const
{
    return toInt() != d.toInt();
}

bool Date::operator<(const Date& d) const
{
    return toInt() < d.toInt();
}

bool Date::operator<=(const Date& d) const
{
    return toInt() <= d.toInt();
}

bool Date::operator>(const Date& d) const
{
    return toInt() > d.toInt();
}

bool Date::operator>=(const Date& d) const
{
    return toInt() >= d.toInt();
}


ostream& operator << (ostream& os, Date& d)
{
    os << d.year << endl;
    os << d.month << endl;
    os << d.day;

    ///os << d.year << endl << d.month << endl << d.day;

    return os;
}

istream& operator >> (istream& is, Date& d)
{
    string myStr;

    getline(is, myStr);
    d.year = atoi(myStr.c_str());
    getline(is, myStr);
    d.month = atoi(myStr.c_str());
    getline(is, myStr);
    d.day = atoi(myStr.c_str());

    return is;
}
