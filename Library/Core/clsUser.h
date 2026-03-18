#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/clsDate.h"
#include <vector>
#include <fstream>
using namespace std;

struct stLoginRegisterRecord
{
    string DateTime;
    string UserName;
    string Password;
    int Permissions;
};

class clsUser : public clsPerson
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::SplitString(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsString::Decryption(LoginRegisterDataLine[2],5);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {   

        string LoginRecord = "";

        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += GetUserName() + Seperator;
        LoginRecord += clsString::Encryption(GetPassword(),5) + Seperator;
        LoginRecord += to_string(GetPermissions());

        return LoginRecord;
    }

    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {   

        string stUserRecord = "";

        stUserRecord += User.getFirstName() + Seperator;
        stUserRecord += User.getLastName() + Seperator;
        stUserRecord += User.getEmail() + Seperator;
        stUserRecord += User.getPhone() + Seperator;
        stUserRecord += User.GetUserName() + Seperator;
        stUserRecord += clsString::Encryption(User.GetPassword(),5) + Seperator;
        stUserRecord += to_string(User.GetPermissions());

        return stUserRecord;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::SplitString(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsString::Decryption(vUserData[5],5), stoi(vUserData[6]));

    }

    static vector <clsUser> _LoadUserDataFromFile()
    {

        vector<clsUser> vUsers;

        fstream MyFile;
        MyFile.open("../data/Users.txt", ios::in); //read Mode

        if(MyFile.is_open())
        {
            string Line;

            while(getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> _vUsers)
    {

        fstream MyFile;
        MyFile.open("../data/Users.txt", ios::out); //overwrite

        string Line;

        if(MyFile.is_open())
        {
            for(clsUser U : _vUsers)
            {
                if(U.MarkedForDeleted() == false)
                {
                    Line = _ConvertUserObjectToLine(U);
                    MyFile << Line << endl;                
                }
            }
            MyFile.close();
        }
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUserDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.GetUserName() == GetUserName())
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("../data/Users.txt", ios::out | ios::app);

        if(MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128
    };

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
    string UserName, string Password, int Permissions) :
    clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void setUserName(string UserName)
    {
        _UserName = UserName;
    }

    string GetPassword()
    {
        return _Password;
    }

    void setPassword(string Password)
    {
        _Password = Password;
    }

    int GetPermissions()
    {
        return _Permissions;
    }

    void setPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("../data/Users.txt", ios::in); //read Mode

        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if(User.GetUserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("../data/Users.txt", ios::in); //read Mode

        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if(User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExisit};
    
    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    enSaveResult Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if(IsEmpty())
            {
                return enSaveResult::svFaildEmptyObject;
            }
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResult::svSucceeded;
        }
        case enMode::AddNewMode:
            if(clsUser::IsUserExist(_UserName))
            {
                return enSaveResult::svFailedAccountNumberExisit;
            }
            else
            {

                _AddNew();
                
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }
    }
        return enSaveResult::svFaildEmptyObject;
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUserDataFromFile();

        for(clsUser &U : _vUsers)
        {
            if(U.GetUserName() == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUserDataFromFile();
    }

    static  vector <stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector <stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("../data/LoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stLoginRegisterRecord LoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);

            }

            MyFile.close();

        }

        return vLoginRegisterRecord;

    }


    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->_Permissions == enPermissions::eAll)
            return true;

        if ((Permission & this->_Permissions) == Permission)
            return true;
        else
            return false;

    }

    void RegisterLogin()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("../data/LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

};