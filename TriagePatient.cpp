/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.cpp
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


#include "TriagePatient.h"

#include <cstring>
#include <iostream>

namespace sdds {

   int nextTriageTicket = 1;

   TriagePatient::~TriagePatient() {
       if (m_symptoms != nullptr) {
           delete[] m_symptoms;
       }
   }

   char TriagePatient::type() const {
       return 'T';
   }

   std::ostream& TriagePatient::csvWrite(std::ostream& os) const {
       this->Patient::csvWrite(os) << ',' << m_symptoms;
       return os;
   }

   std::istream& TriagePatient::csvRead(std::istream& is) {
       if (m_symptoms != nullptr) {
           delete[] m_symptoms;
       }
       this->Patient::csvRead(is);
       is.get();
       char buffer[512] = {'\0'};
       is.getline(buffer, 512, '\n');
       int s = strlen(buffer);
       m_symptoms = new char[s+1];
       strcpy(m_symptoms, buffer);
       //is.ignore(INT_MAX);
       nextTriageTicket = Patient::number() + 1;
       return is;
   }

   std::ostream& TriagePatient::write(std::ostream& os) const {
       if (fileIO()) {
           csvWrite(os);
       }
       else {
           os << "TRIAGE\n";
           this->Patient::write(os) << "\nSymptoms: " << m_symptoms  << '\n';
       }
       return os;
   }

   std::istream& TriagePatient::read(std::istream& is) {
       if (fileIO()) {
           csvRead(is);
       }
       else {
           if (m_symptoms != nullptr) {
               delete[] m_symptoms;
           }
           this->Patient::read(is);
           std::cout << "Symptoms: ";
           char buffer[512] = { '\0' };
           is.getline(buffer, 512, '\n');
           int s = strlen(buffer);
           m_symptoms = new char[s + 1];
           strcpy(m_symptoms, buffer);
       }
       return is;
   }

}