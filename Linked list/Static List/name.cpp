#include "name.h"

using namespace std;

string Name::getLast() const
{
    return last;
}

string Name::getFirst() const
{
    return first;
}

string Name::toString() const
{
    return last + ", " + first;
}

void Name::setLast(const string& l)
{
    last = l;
}

void Name::setFirst(const string& f)
{
    first = f;
}

bool Name::operator==(const Name& n) const
{
    return toString() == n.toString();
}

bool Name::operator!=(const Name& n) const
{
    return toString() != n.toString();
}

bool Name::operator<(const Name& n) const
{
    return toString() < n.toString();
}

bool Name::operator<=(const Name& n) const
{
    return toString() <= n.toString();
}

bool Name::operator>(const Name& n) const
{
    return toString() > n.toString();
}

bool Name::operator>=(const Name& n) const
{
    return toString() >= n.toString();
}


ostream& operator << (ostream& os, Name& n)
{
    os << n.last << endl;
    os << n.first;

    return os;
}

istream& operator >> (istream& is, Name& n)
{
    getline(is, n.last);
    getline(is, n.first);

    return is;
}
