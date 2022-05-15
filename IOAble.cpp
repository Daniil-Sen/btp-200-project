/* Citation and Sources...
Final Project Milestone 4
Module: IOAble
Filename: IOAble.cpp
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

#include "IOAble.h"

sdds::IOAble::~IOAble() {
}

std::ostream& sdds::operator<<(std::ostream& os, IOAble& ioa) {
    return ioa.write(os);
}

std::istream& sdds::operator>>(std::istream& is, IOAble& ioa) {
    return ioa.read(is);
}
