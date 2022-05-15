/* Citation and Sources...
Final Project Milestone 4
Module: utils
Filename: utils.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }

   int getInt(const char* prompt) {
       if (prompt != nullptr) {
           std::cout << prompt;
       }
       bool done = false;
       int ans = 0;
       while (!done) {
           char buff[512] = {'\0'};
           std::cin.getline(buff, 512);
           bool non_numeric = false;
           bool has_integer = false;
           int size = strlen(buff);
           for (int i = 0; i < size; ++i) {
               if ((buff[i] < '0' || buff[i] > '9') && buff[i] != '-') {
                   non_numeric = true;
               }
               else if (buff[i] >= '0' || buff[i] <= '9') {
                   has_integer = true;
               }
           }
           if (!non_numeric) {
               ans = std::atoi(buff);
               done = true;
           }
           else {
               if (has_integer) {
                   std::cout << "Enter only an integer, try again: ";
               }
               else {
                   std::cout << "Bad integer value, try again: ";
               }
           }
       }
       return ans;
   }

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
       int ans = 0;
       bool done = false;
       
       ans = getInt(prompt);
       while (!done) {
           if (ans >= min && ans <= max) {
               done = true;
           }
           else {
               if (errorMessage != nullptr) {
                   std::cout << errorMessage;
               }
               if (showRangeAtError) {
                   std::cout << "[" << min << " <= value <= " << max << "]: ";
               }
           }
           if (!done) {
               ans = getInt();
           }             
       }
       return ans;
   }

   char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
       if (prompt != nullptr) {
           std::cout << prompt;
       }
       char buff[512] = { '\0' };
       istr.getline(buff, 511, delimiter);
       int s = strlen(buff);
       char* ans = new char[s+1];
       strcpy(ans, buff);
       return ans;
   }
}