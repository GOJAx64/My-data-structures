#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED

#include <string>
#include <iostream>

class Name
{
private:
    std::string last;
    std::string first;

public:
    ///Name();
    ///Name(const);

    std::string getLast() const;
    std::string getFirst() const;

    std::string toString() const;

    void setLast(const std::string&);
    void setFirst(const std::string&);

    bool operator == (const Name&) const;
    bool operator != (const Name&) const;
    bool operator < (const Name&) const;
    bool operator <= (const Name&) const;
    bool operator > (const Name&) const;
    bool operator >= (const Name&) const;

    friend std::ostream& operator << (std::ostream&, Name&);
    friend std::istream& operator >> (std::istream&, Name&);

};

#endif // NAME_H_INCLUDED
