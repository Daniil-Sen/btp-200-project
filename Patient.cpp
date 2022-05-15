/* Citation and Sources...
Final Project Milestone 4
Module: Patient
Filename: Patient.cpp
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

#include "Patient.h"
#include "Time.h"
#include "utils.h"

sdds::Patient::Patient(int ticketNum, bool ioFlag) : m_ticket(ticketNum) {
    this->m_name = nullptr;
    this->m_ohipNum = 0;
    this->m_ioFlag = ioFlag;
}

sdds::Patient::Patient(const Patient& p) : m_ticket(0) {
    this->m_name = nullptr;
    this->m_ohipNum = 0;
    this->m_ioFlag = false;
}

sdds::Patient& sdds::Patient::operator=(const Patient& p) {
    return *this;
}

sdds::Patient::~Patient() {
    if (this->m_name != nullptr)
        delete[] this->m_name;
}

bool sdds::Patient::fileIO() const {
    return this->m_ioFlag;
}

void sdds::Patient::fileIO(bool flag) {
    this->m_ioFlag = flag;
}

bool sdds::Patient::operator==(char c) const {
    return this->type() == c;
}

bool sdds::Patient::operator==(const Patient& p) const {
    return this->type() == p.type();
}

void sdds::Patient::setArrivalTime() {
    this->m_ticket.resetTime();
}

sdds::Patient::operator sdds::Time() const {
    Time t(this->m_ticket);
    return t;
}

int sdds::Patient::number() const {
    return this->m_ticket.number();
}

std::ostream& sdds::Patient::csvWrite(std::ostream& os) const {
    os << this->type() << ',' << this->m_name << ',' << m_ohipNum << ',';
    return m_ticket.csvWrite(os);
}

std::istream& sdds::Patient::csvRead(std::istream& is) {
    char buffer[512] = { '\0' };
    is.getline(buffer, 512, ',');
    int s = strlen(buffer);
    // the last line in csv is read but it shoulnt change the obj.
    if (s > 0) {
        if (this->m_name != nullptr)
            delete[] m_name;
        this->m_name = new char[s + 1];
        strcpy(this->m_name, buffer);
        is.getline(buffer, 512, ',');
        this->m_ohipNum = std::atoi(buffer);
        this->m_ticket.csvRead(is);
        // looks like the WalkinPatient read function ignores lines until the '\n' is found.
        // problem is this function has no extra characters so i had to putback the '\n' char
        // so it will work with that function.
        is.putback('\n');
    }
    return is;
}

std::ostream& sdds::Patient::write(std::ostream& os) const {
    int s = strlen(this->m_name);
    if (s > 25) {
        char name[26] = { '\0' };
        strncpy(name, this->m_name, 25);
        name[25] = '\0';
        this->m_ticket.write(os) << '\n' << name << ", OHIP: " << this->m_ohipNum;
    }
    else {
        this->m_ticket.write(os) << '\n' << this->m_name << ", OHIP: " << this->m_ohipNum;
    }
    return os;
}

std::istream& sdds::Patient::read(std::istream& is) {
    this->m_name = getcstr("Name: ", is, '\n');
    this->m_ohipNum = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
    return is;
}

