#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include <iomanip>

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{

private:

    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter FirstName: ";
        Client.setFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.setLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.setEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.setPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.setPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.setAccountBalance(clsInputValidate::ReadFloatNumber());
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:\n\n";
        cout << "----------------------------------------------------------\n";
        cout << left << setw(18) << "FirstName    :"   << Client.getFirstName() << endl;
        cout << left << setw(18) << "LastName     :"   << Client.getLastName() << endl;
        cout << left << setw(18) << "Full Name    :"   << Client.getFullName() << endl;
        cout << left << setw(18) << "Email        :"   << Client.getEmail() << endl;
        cout << left << setw(18) << "Phone        :"   << Client.getPhone() << endl;
        cout << left << setw(18) << "Acc. Number  :"   << Client.getAccountNumber() << endl;
        cout << left << setw(18) << "PinCode      :"   << Client.getPinCode() << endl;
        cout << left << setw(18) << "Balance      :"   << Client.getAccountBalance() << endl;
        cout << "----------------------------------------------------------\n";
    }

public:

    static void ShowAddNewClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        _DrawScreenHeader("\t   Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while(clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);
        
        clsBankClient::enSaveResult SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Added Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError Account was not saved because its Empty";
            break;
        }
        case clsBankClient::enSaveResult::svFailedAccountNumberExisit:
        {
            cout << "\nError account was not saved because account number is used\n";
            break;
        }
        }
    }

};