/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author	Daniil Sen
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/30  Completed
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_

namespace sdds {
    class Menu {
        char* m_text;
        int m_noOfSel;
        void display()const;
    public:
        Menu(const char* MenuContent, int noOfSelections);
        Menu(const Menu& m);
        virtual ~Menu();
        int& operator>>(int& Selection);
        Menu& operator=(const Menu& m);
    };
}

#endif // !SDDS_MENU_H_
