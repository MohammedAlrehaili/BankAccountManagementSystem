#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsPerson
{

private:

    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:

    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    //Property Set

    void setFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string getFirstName()
    {
        return _FirstName;
    }

    void setLastName(string LastName)
    {
        _LastName = LastName;
    }

    string getLastName()
    {
        return _LastName;
    }

    void setEmail(string Email)
    {
        _Email = Email;
    }

    string getEmail()
    {
        return _Email;
    }

    void setPhone(string Phone)
    {
        _Phone = Phone;
    }

    string getPhone()
    {
        return _Phone;
    }

    string getFullName()
    {
        return _FirstName + " " + _LastName;
    }

};