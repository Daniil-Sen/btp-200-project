/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.h
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


#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H

#include "Patient.h"

namespace sdds {

    extern int nextTriageTicket;

    class TriagePatient : public Patient {
    public:
        TriagePatient() : Patient(nextTriageTicket++) {
            m_symptoms = nullptr;
        }
        ~TriagePatient();
        char type() const;
        std::ostream& csvWrite(std::ostream& os) const;
        std::istream& csvRead(std::istream& is);
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    private:
        char* m_symptoms;
    };
}
#endif // !SDDS_TRIAGEPATIENT_H


