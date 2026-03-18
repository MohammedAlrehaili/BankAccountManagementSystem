#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/clsDate.h"
using namespace std;

struct stTransferLogRegister
{
    string DateTime;
    string SourceAccountNumber;
    string DestinationAccountNumber;
    float Amount;
    float SourceBalance;
    float DestinationBalance;
    string UserName;
};

class clsBankClient : public clsPerson
{

private:


    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static stTransferLogRegister _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferLogRegister TransferLogRecord;


        vector <string> LoginRegisterDataLine = clsString::SplitString(Line, Seperator);

        TransferLogRecord.DateTime = LoginRegisterDataLine[0];
        TransferLogRecord.SourceAccountNumber = LoginRegisterDataLine[1];
        TransferLogRecord.DestinationAccountNumber = LoginRegisterDataLine[2];
        TransferLogRecord.Amount = stoi(LoginRegisterDataLine[3]);
        TransferLogRecord.SourceBalance = stoi(LoginRegisterDataLine[4]);
        TransferLogRecord.DestinationBalance = stoi(LoginRegisterDataLine[5]);
        TransferLogRecord.UserName = LoginRegisterDataLine[6];

        return TransferLogRecord;
    }

    string _PrepareTransferLog(float Amount, clsBankClient DestinationClient, string UserName ,string Seperator = "#//#")
    {   

        string LoginRecord = "";
        
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += getAccountNumber() + Seperator;
        LoginRecord += DestinationClient.getAccountNumber() + Seperator;
        LoginRecord += to_string(Amount) + Seperator;
        LoginRecord += to_string(getAccountBalance()) + Seperator;
        LoginRecord += to_string(DestinationClient.getAccountBalance()) + Seperator;
        LoginRecord += UserName;

        return LoginRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient ,string UserName)
    {
        string stDataLine = _PrepareTransferLog(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("../data/TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }    
    }

    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::SplitString(Line,Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
        vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {   

        string stClientRecord = "";

        stClientRecord += Client.getFirstName() + Seperator;
        stClientRecord += Client.getLastName() + Seperator;
        stClientRecord += Client.getEmail() + Seperator;
        stClientRecord += Client.getPhone() + Seperator;
        stClientRecord += Client.getAccountNumber() + Seperator;
        stClientRecord += Client.getPinCode() + Seperator;
        stClientRecord += to_string(Client.getAccountBalance());

        return stClientRecord;
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector<clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::in); //read Mode

        if(MyFile.is_open())
        {
            string Line;

            while(getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    static void _SaveClientsDataToFile(vector <clsBankClient> _vClients)
    {

        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::out); //overwrite

        string Line;

        if(MyFile.is_open())
        {
            for(clsBankClient C : _vClients)
            {
                if(C.getMarkedForDeleted() == false)
                {
                    Line = _ConvertClientObjectToLine(C);
                    MyFile << Line << endl;                
                }
            }
            MyFile.close();
        }
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::out | ios::app);

        if(MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        
        for(clsBankClient &C : _vClients)
        {
            if(C.getAccountNumber() == getAccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }
public:

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
         string AccountNumber, string PinCode, float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return(_Mode == enMode::EmptyMode);
    }

    string getAccountNumber()
    {
        return _AccountNumber;
    }

    void setPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string getPinCode()
    {
        return _PinCode;
    }

    void setAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float getAccountBalance()
    {
        return _AccountBalance;
    }

    bool getMarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    void Deposit(float Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(float Amount)
    {
        if(Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
        }
        return true;
    }

    bool Transfer(float Amount, clsBankClient &DestinationClient, string UserName)
    {
        if (Amount > getAccountBalance())
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount,DestinationClient,UserName);
        return true;
    }

    void Print()
    {
        cout << "\nClient Card:\n\n";
        cout << "----------------------------------------------------------\n";
        cout << left << setw(18) << "FirstName    :"   << getFirstName() << endl;
        cout << left << setw(18) << "LastName     :"   << getLastName() << endl;
        cout << left << setw(18) << "Full Name    :"   << getFullName() << endl;
        cout << left << setw(18) << "Email        :"   << getEmail() << endl;
        cout << left << setw(18) << "Phone        :"   << getPhone() << endl;
        cout << left << setw(18) << "Acc. Number  :"   << getAccountNumber() << endl;
        cout << left << setw(18) << "PinCode      :"   << getPinCode() << endl;
        cout << left << setw(18) << "Balance      :"   << getAccountBalance() << endl;
        cout << "----------------------------------------------------------\n";
    }

    static clsBankClient Find(string AccountNumber)
    {
        vector <clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::in); //read Mode

        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if(Client.getAccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        vector <clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::in); //read Mode

        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if(Client.getAccountNumber() == AccountNumber && Client.getPinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }
  
    enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExisit};

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
            if(clsBankClient::IsClientExist(_AccountNumber))
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

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for(clsBankClient &C : _vClients)
        {
            if(C.getAccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static float GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for(clsBankClient Client : vClients)
        {
            TotalBalances += Client.getAccountBalance();
        }

        return TotalBalances;
    }

    static  vector <stTransferLogRegister> GetTransferLogListList()
    {
        vector <stTransferLogRegister> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("../data/TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTransferLogRegister TransferLogRecord;

            while (getline(MyFile, Line))
            {

                TransferLogRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferLogRecord);

            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }
};