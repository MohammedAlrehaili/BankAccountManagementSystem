#include <iostream>
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:\n\n";
        cout << "----------------------------------------------------------\n";
        cout << left << setw(18) << "Full Name    :"   << Client.getFullName() << endl;
        cout << left << setw(18) << "Acc. Number  :"   << Client.getAccountNumber() << endl;
        cout << left << setw(18) << "Balance      :"   << Client.getAccountBalance() << endl;
        cout << "----------------------------------------------------------\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();
        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount: ";

        Amount = clsInputValidate::ReadFloatNumber();

        while(Amount > SourceClient.getAccountBalance())
        {
            cout << "\nAmount Exceeds the available Balance, Enter another amount : ";
            Amount = clsInputValidate::ReadFloatNumber();
        }
        return Amount;
    }



public:

    static void ShowTransferScreen()
    {

        _DrawScreenHeader("\t   Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);

        char answer;
        cout << "\nAre you sure you want to perform this operation? ";
        answer = clsInputValidate::ReadChar();

        if(answer == 'Y' || answer == 'y')
        {
            if(SourceClient.Transfer(Amount,DestinationClient,CurrentUser.GetUserName()))
            {
                cout << "\nTransfer done sucessfully!\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }

};