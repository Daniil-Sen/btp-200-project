/* Citation and Sources...
Final Project Milestone 4
Module: IOAble
Filename: IOAble.h
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

#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_

#include <iostream>

namespace sdds {
    class IOAble {
    public:
        virtual std::ostream& csvWrite(std::ostream& os) const = 0;
        virtual std::istream& csvRead(std::istream& is) = 0;
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual ~IOAble();
    };

    std::ostream& operator<<(std::ostream& os, IOAble& ioa);
    std::istream& operator>>(std::istream& is, IOAble& ioa);
}

#endif // SDDS_IOABLE_H_
