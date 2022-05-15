/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
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

#include <cstring>

#include "Menu.h"
#include "utils.h"

void sdds::Menu::display() const {
    std::cout << m_text << "\n0- Exit" << std::endl;
}

sdds::Menu::Menu(const char* MenuContent, int noOfSelections) {
    this->m_text = nullptr;
    if (MenuContent != nullptr) {
        this->m_text = new char[strlen(MenuContent) + 1];
        strcpy(m_text, MenuContent);
    }
    this->m_noOfSel = noOfSelections;
}

sdds::Menu::Menu(const Menu& m) {
    this->m_text = nullptr;
    if (m.m_text != nullptr) {
        this->m_text = new char[strlen(m.m_text)+1];
        strcpy(m_text, m.m_text);
    }
    this->m_noOfSel = m.m_noOfSel;
}

sdds::Menu::~Menu() {
    if (m_text != nullptr) {
        delete[] m_text;
    }
}

int& sdds::Menu::operator>>(int& Selection) {
    display();
    Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
    return Selection;
}

sdds::Menu& sdds::Menu::operator=(const Menu& m) {
    return *this;
}
