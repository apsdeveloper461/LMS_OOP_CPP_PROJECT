#include "Date.h"

const int Date::DAYS_PER_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

 Date::Date() : m_year(2024), m_day(25), m_month(2) {}

 Date::Date(string& date)
{
    bool set_d;
    do {
        set_d = false;
        set_d = check_date(date);
        if (!set_d) {
            cout << "\n\t --> Enter date in form <Year is greater than 2000 and less then 2050>(DDMMYYYY) :: ";
            cin >> date;
        }
        else {
            break;
        }
    } while (true);
}

 void Date::set_date(string& date)
{
    bool set_d;
    do {
        set_d = false;
        set_d = check_date(date);
        if (!set_d) {
            cout << "\n\t --> Enter date in form <Year is greater than 2000 and less then 2050>(DDMMYYYY) :: ";
            cin >> date;
        }
        else {
            break;
        }
    } while (true);
}

 bool Date::is_leap_year(int year) const
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

 string Date::get_date() const
{
    string date = to_string(m_year) + "-" + to_string(m_month) + "-" + to_string(m_day);
    return date;
}

 bool Date::check_date(const string& date)
{
    bool is_date_valid = false;

    if (date.length() != 8)
    {
        cout << "Invalid date format. Please enter the date in the format DDMMYYYY and try again." << endl;
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(2, 2));
    int year = stoi(date.substr(4, 8));
    cout << date << " " << day << " " << month << " " << year << endl;
    if (year >= 2000 && year <= 2050)
    {
        is_date_valid = true;
    }
    else
    {
        cout << "Invalid year. Please enter a year between 2000 and 2050 and try again." << endl;
        return false;
    }

    if (month >= 1 && month <= 12)
    {
        is_date_valid = true;
    }
    else
    {
        cout << "Invalid month. Please enter a month between 1 and 12 and try again." << endl;
        return false;
    }

    if (is_date_valid)
    {


        if (month == 2)
        {
            if (is_leap_year(year))
            {
                if (day >= 1 && day <= 29)
                {
                    is_date_valid = true;
                }
                else
                {
                    cout << "Invalid day. Please enter a day between 1 and 29 for February in a leap year and try again." << endl;
                    return false;
                }
            }
            else
            {
                if (day >= 1 && day <= 28)
                {
                    is_date_valid = true;
                }
                else
                {
                    cout << "Invalid day. Please enter a day between 1 and 28 for February in a non-leap year and try again." << endl;
                    return false;
                }
            }
        }
        else if (month >= 1 && month <= 12)
        {
            if (day >= 1 && day <= DAYS_PER_MONTH[month - 1])
            {
                is_date_valid = true;
            }
            else
            {
                cout << "Invalid day. Please enter a day between 1 and " << DAYS_PER_MONTH[month - 1] << " for month " << month << " and try again." << endl;
                return false;
            }
        }
    }

    if (is_date_valid)
    {
        m_day = day;
        m_month = month;
        m_year = year;
        cout << "Date is valid." << endl;
        return true;
    }
}
