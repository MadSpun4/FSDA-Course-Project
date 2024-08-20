#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <sstream>

using namespace std;

class Date
{
public:
    Date();
    Date(short _year, short _month, short _day);
    explicit Date(const string &date);
    ~Date();

    bool operator==(const Date &date) const;
    bool operator!=(const Date &date) const;
    bool operator>(const Date &date) const;
    bool operator<(const Date &date) const;
    void operator=(const Date &date);

    friend ostream &operator<<(ostream &out, const Date &date);

    string toString() const;
    void fromString(const std::string& dateStr);

    short getYear() const;
    short getMonth() const;
    short getDay() const;

private:
    [[nodiscard]] bool correctDate() const;

private:
    short m_year;
    short m_month;
    short m_day;
};

inline ostream &operator<<(ostream &out, const Date &date)
{
    out << date.getDay() << "." << date.getMonth() << "." << date.getYear();
    return out;
}

#endif // DATE_H
