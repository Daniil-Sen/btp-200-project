/* Citation and Sources...
Final Project Milestone 4
Module: CovidPatient
Filename: CovidPatient.cpp
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


#include "CovidPatient.h"

namespace sdds {
   int nextCovidTicket = 1;

   char CovidPatient::type() const {
       return 'C';
   }

   std::istream& CovidPatient::csvRead(std::istream& is) {
       this->Patient::csvRead(is);
       nextCovidTicket = Patient::number() + 1;
       is.ignore(1000, '\n');
       return is;
   }

   std::ostream& CovidPatient::write(std::ostream& os) const {
       if (fileIO()) {
           this->Patient::csvWrite(os);
       }
       else {
           os << "COVID TEST\n";
           this->Patient::write(os) << '\n';
       }
       return os;
   }

   std::istream& CovidPatient::read(std::istream& is) {
       if (fileIO()) {
           this->csvRead(is);
       }
       else {
           this->Patient::read(is);
       }
       return is;
   }
}