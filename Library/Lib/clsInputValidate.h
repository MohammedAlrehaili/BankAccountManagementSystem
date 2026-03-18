#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsDate.h"
#include "clsPeriod.h"
#include "clsString.h"

using namespace std;

class clsInputValidate
{
   
public:

    static bool IsNumberBetween(int Number, int From, int To)
    {
        return (Number >= From) && (Number <= To);
    }

    static bool IsNumberBetween(short Number, short From, short To)
    {
        return (Number >= From) && (Number <= To);
    }

    static bool IsNumberBetween(double Number, double From, double To)
    {
        return (Number >= From) && (Number <= To);
    }

    static bool IsNumberBetween(float Number, float From, float To)
    {
        return (Number >= From) && (Number <= To);
    }

    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        clsPeriod Period(From,To);
        return Period.isDateInPeriod(Date);
    }

    static int ReadIntNumber(string message = "Invalid Number")
    {
        int Number;
        while(!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message;
        }
        return Number;
    }

    static double ReadDoubleNumber(string message = "Invalid Number")
    {
        double Number;
        while(!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message;
        }
        return Number;
    }

    static double ReadFloatNumber(string message = "Invalid Number")
    {
        float Number;
        while(!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message;
        }
        return Number;
    }

    static short ReadShortNumber(string message = "Invalid Number")
    {
        short Number;
        while(!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message;
        }
        return Number;
    }

    static int ReadIntNumberBetween(int from, int to, string message = "not within range")
    {
        int Number = ReadIntNumber("Invalid Number, Enter again: ");

        while(!IsNumberBetween(Number, from,to))
        {
            cout << message;
            Number = ReadIntNumber("Invalid Number, Enter again: ");
        }
        return Number;
    }

    static double ReadDoubleNumberBetween(double from, double to, string message = "not within range")
    {
        double Number = ReadDoubleNumber("Invalid Number, Enter again: ");

        while(!IsNumberBetween(Number, from,to))
        {
            cout << message;
            Number = ReadDoubleNumber("Invalid Number, Enter again: ");
        }
        return Number;
    }

    static short ReadShortNumberBetween(short from, short to, string message = "not within range")
    {
        short Number = ReadShortNumber();

        while(!IsNumberBetween(Number, from,to))
        {
            cout << message;
            Number = ReadShortNumber();
        }
        return Number;
    }

    static string ReadString()
    {
        string s1 = "";
        getline(cin >> ws ,s1);  
        return s1;
    }

    static char ReadChar(string message = "Invalid Character")
    {
        char Character;
        while(!(cin >> Character))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message;
        }
        return Character;     
    }
    
    static bool IsValidDate(clsDate Date)
    {
        return clsDate::isValidDate(Date);
    }

};