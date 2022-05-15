/* Citation and Sources...
Final Project Milestone 4
Module: CovidPatient
Filename: CovidPatient.h
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


#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_

#include "Patient.h"

namespace sdds {

    extern int nextCovidTicket;

    class CovidPatient : public Patient {
    public:
        CovidPatient() : Patient(nextCovidTicket++) {}

        char type() const;

        std::istream& csvRead(std::istream& is);
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    };

}
#endif // !SDDS_COVIDPATIENT_H_



