/* Citation and Sources...
Final Project Milestone 4
Module: Patient
Filename: Patient.h
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

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_

#include "IOAble.h"
#include "Ticket.h"

namespace sdds {
    class Patient : public IOAble {
    private:
        char* m_name;
        int m_ohipNum;
        Ticket m_ticket;
        bool m_ioFlag;
    public:
        Patient(int ticketNum = 0, bool ioFlag = false);
        Patient(const Patient& p);
        Patient& operator=(const Patient& p);
        ~Patient();
        virtual char type() const = 0;
        bool fileIO() const;
        void fileIO(bool flag);
        bool operator==(char c) const;
        bool operator==(const Patient& p) const;
        void setArrivalTime();
        operator sdds::Time() const; // odd
        int number() const;
        std::ostream& csvWrite(std::ostream& os) const;
        std::istream& csvRead(std::istream& is);
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    };
}

#endif // !SDDS_PATIENT_H_
