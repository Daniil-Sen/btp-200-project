/* Citation and Sources...
Final Project Milestone 4
Module: Time
Filename: Time.cpp
Version 1.0
Author	Daniil Sen
Revision History
-----------------------------------------------------------
Date      Reason
2021/8/2  Completed
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include <cstring>
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {
    Time& Time::setToNow() {
        // TODO: insert return statement here
        if (debug) {
            std::cin.clear();
            std::cout << "Enter current time: ";
            int done = false;
            while (!done) {
                std::cin >> *this;
                if (std::cin.fail()) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Bad time entry, retry (HH:MM): ";
                }
                else {
                    done = true;
                }
            }
        }
        else {
            *this = getTime();
        }
        return *this;
    }

    Time::Time(unsigned int min) {
        m_min = min;
    }

    std::ostream& Time::write(std::ostream& ostr) const {
        unsigned int min = m_min % 60;
        unsigned int hr = (m_min - min) / 60;

        if (hr < 10)
            ostr << '0' << hr << ':';
        else
            ostr << hr << ':';

        if (min < 10)
            ostr << '0' << min;
        else
            ostr << min;
        return ostr;
    }

    // couldnt use getcstr as I need multiple delimiters with it.
    std::istream& Time::read(std::istream& istr) {        
        char hr_buff[64] = { '\0' };
        char min_buff[64] = { '\0' };
        int i = 0;
        char c = '\0';
        bool failed = false;

        // get hrs until delimiter
        while (istr.get(c) && !failed && i != 62) {
            if (c >= '0' && c <= '9') {
                hr_buff[i++] = c;
            }
            else if (c != ':') {
                istr.setstate(ios::failbit);
                failed = true;
                break;
            }
            else if (c == ':') {
                // done
                break;
            }
        }
        i = 0;
        // get mins until next line. failed here look tomorrow
        /// error is there is no end line but a comma delimiter
        while (istr.get(c) && !failed && i != 62) {
            if (c >= '0' && c <= '9') {
                min_buff[i++] = c;
            }
            else if (c != '\n' && c != ',') {
                istr.setstate(ios::failbit);
                failed = true;
                break;
            }
            else if (c == '\n' || c == ',') {
                break;
            }
        }
        if (!failed) {
            int hr = std::atoi(hr_buff);
            int mi = std::atoi(min_buff);
            this->m_min = mi + hr * 60;
        }
        return istr;
    }

    Time& Time::operator-=(const Time& D) {
        int min = this->m_min -= D.m_min;
        while (min < 0) {
            min += 24 * 60;
        }
        this->m_min = min;
        return *this;
    }

    Time Time::operator-(const Time& D) const {
        int min = this->m_min - D.m_min;
        while (min < 0) {
            min += 24 * 60;
        }
        Time t(min);
        return t;
    }

    Time& Time::operator+=(const Time& D) {
        this->m_min += D.m_min;
        return *this;
    }

    Time Time::operator+(const Time& D) const {
        Time t(this->m_min + D.m_min);
        return t;
    }

    Time& Time::operator=(unsigned int val) {
        this->m_min = val;
        return *this;
    }

    Time& Time::operator*=(unsigned int val) {
        this->m_min *= val;
        return *this;
    }

    Time& Time::operator/=(unsigned int val) {
        if (val != 0)
            this->m_min /= val;
        return *this;
    }

    Time Time::operator*(unsigned int val) const {
        Time t(this->m_min * val);
        return t;
    }

    Time Time::operator/(unsigned int val) const {
        if (val != 0) {
            Time t(this->m_min / val);
            return t;
        }
        else {
            return Time(0);
        }
    }

    Time::operator unsigned int() const {
        return m_min;
    }

    Time::operator int() const {
        return (int)(m_min);
    }

    std::ostream& operator<<(std::ostream& ostr, const Time& D) {
        D.write(ostr);
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Time& D) {
        D.read(istr);
        return istr;
    }
}