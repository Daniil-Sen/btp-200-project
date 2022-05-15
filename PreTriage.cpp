#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "CovidPatient.h"
#include "PreTriage.h"
#include "TriagePatient.h"
#include "utils.h"

using namespace std;

sdds::PreTriage::PreTriage(const char* dataFilename) :
    m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
    m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 3) {
    m_dataFilename = new char[strlen(dataFilename) + 1];
    strcpy(m_dataFilename, dataFilename);
    m_averCovidWait = 15;
    m_averTriageWait = 5;

    load();
}

sdds::PreTriage::~PreTriage() {
    cout << "Saving Average Wait Times,\n";

    // implement saves covid wait time and traige wait time in csv
    cout << "   COVID Test: " << m_averCovidWait << "\n";
    cout << "   Triage: " << m_averTriageWait << "\n";
    cout << "Saving m_lineup...\n";
    ofstream file;
    file.open(m_dataFilename);
    file << m_averCovidWait << ',' << m_averTriageWait << '\n';

    // saves all patient data in csv
    for (int i = 0; i < maxNoOfPatients; ++i) {
        if (m_lineup[i] != nullptr) {
            m_lineup[i]->fileIO(true);
            file << *m_lineup[i] << '\n';
            cout << (i + 1) << "- " << *m_lineup[i] << '\n';
        }
    }

    file.close();

    for (int i = 0; i < m_lineupSize; ++i) {
        delete m_lineup[i];
    }

    delete[] m_dataFilename;
    cout << "done!\n";
}

void sdds::PreTriage::run(void) {
    int option = -1;
    bool running = true;

    while (running) {
        m_appMenu >> option;
        switch (option)
        {
        case 0:
            running = false;
            break;
        case 1:
            reg();
            break;
        case 2:
            admit();
            break;
        default:
            running = false;
            break;
        }
    }
}

void sdds::PreTriage::reg() {
    if (m_lineupSize < maxNoOfPatients) {
        int option = -1;
        m_pMenu >> option;
        switch (option)
        {
        case 1:
            m_lineup[m_lineupSize] = new CovidPatient();
            m_lineup[m_lineupSize]->setArrivalTime();
            cout << "Please enter patient information: \n";
            cin >> *m_lineup[m_lineupSize];
            cout << "\n******************************************\n";
            cout << *m_lineup[m_lineupSize];
            cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << "\n******************************************\n\n";
            m_lineupSize++;
            break;
        case 2:
            m_lineup[m_lineupSize] = new TriagePatient();
            m_lineup[m_lineupSize]->setArrivalTime();
            cout << "Please enter patient information: \n";
            cin >> *m_lineup[m_lineupSize];
            cout << "\n******************************************\n";
            cout << *m_lineup[m_lineupSize];
            cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << "\n******************************************\n\n";
            m_lineupSize++;
            break;
        case 0:
            break;
        }
    }
    else {
        cout << "Line up full!\n";
    }
}

void sdds::PreTriage::admit() {
    int option = -1;\
    m_pMenu >> option;
    char c = '\0';
    switch (option)
    {
    case 0:
        break;
    case 1:
        c = 'C';
        break;
    case 2:
        c = 'T';
        break;
    default:
        break;
    }
    if (c != '\0') {
        int idx = -1;

        for (int i = 0; i < m_lineupSize; ++i) {
            if (m_lineup[i]->type() == c) {
                idx = i;
                break;
            }
        }

        if (idx >= 0) {
            cout << "\n******************************************\n";
            m_lineup[idx]->fileIO(false);
            cout << "Calling for " << *m_lineup[idx];            
            cout << "******************************************\n\n";
            setAverageWaitTime(*m_lineup[idx]);
            removePatientFromLineup(idx);
        }
    }
}

const sdds::Time sdds::PreTriage::getWaitTime(const Patient& p) const {
    Time t;

    for (int i = 0; i < m_lineupSize; ++i) {
        if (m_lineup[i]->type() == p.type()) {
            t += *m_lineup[i];
        }
    }
    return t;
}

void sdds::PreTriage::setAverageWaitTime(const Patient& p) {
    Time curr;
    curr.setToNow();
    Time patientsTime = p;

    if (p.type() == 'C') {
        m_averCovidWait = (((int)curr - (int)patientsTime) + ((int)m_averCovidWait * (p.number() - 1))) / p.number(); // idk
    }
    else {
        m_averTriageWait = (((int)curr - (int)patientsTime) + ((int)m_averCovidWait * (p.number() - 1))) / p.number(); // idk
    }
}

void sdds::PreTriage::removePatientFromLineup(int index) {
    removeDynamicElement<Patient>(m_lineup, index, m_lineupSize);
}

int sdds::PreTriage::indexOfFirstInLine(char type) const {
    int f = -1;
    for (int i = 0; i < maxNoOfPatients; ++i) {
        if (type == m_lineup[i]->type()) {
            f = i;
            break;
        }
    }
    return f;
}

void sdds::PreTriage::load() {
    cout << "Loading data...\n";
    // continue..
    ifstream file;
    file.open(m_dataFilename);
    // starts iff -1 to offset first line
    int size = -1;
    char ch;
    while (file.get(ch)) {
        if (ch == '\n') {
            size++;
        }
    }
    if (size > 0) {
        m_lineupSize = size;
        // reset file io
        file.clear();
        file.seekg(0);
        // read average times
        file >> m_averCovidWait;
        file >> m_averTriageWait;

        // greater than max size warning
        if (m_lineupSize > 100) {
            cout << "Warning: number of records exceeded 100\n";
            m_lineupSize = 100;
        }

        // read into array
        for (int i = 0; i < m_lineupSize; ++i) {
            char c = '\0';
            file.get(c);
            if (c == 'C') {
                m_lineup[i] = new CovidPatient();
            }
            else if (c == 'T') {
                m_lineup[i] = new TriagePatient();
            }
            m_lineup[i]->fileIO(true);
            file.ignore(1, ',');
            file >> *m_lineup[i];
            //cout << *m_lineup[i] << '\n';
            m_lineup[i]->fileIO(false);
        }
        cout << m_lineupSize << " Records imported...\n\n";
    }
    else {
        cout << "No data or bad data file!\n\n";
    }

    file.close();
}
