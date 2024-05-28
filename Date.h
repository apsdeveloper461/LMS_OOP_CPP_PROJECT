#pragma once
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Date
{
public:
    Date();
    Date( string& date);
    void set_date( string& date);
    bool is_leap_year(int year) const;
    string get_date() const;

private:
    static const int DAYS_PER_MONTH[12];
    bool check_date(const string& date);

    int m_day = 0;
    int m_month = 0;
    int m_year = 0;
};

