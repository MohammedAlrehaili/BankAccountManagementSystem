#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{

private:

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

    static void ShowFindClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if(!Client.IsEmpty())
        {
            cout << "\nClient Found:-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }
        
        _PrintClient(Client);
        
    }
};