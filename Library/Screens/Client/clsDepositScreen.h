#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber: ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:

    static void ShowDepositScreen()
    {

        _DrawScreenHeader("\t   Deposit Screen");
        
        string AccountNumber = _ReadAccountNumber();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient With [" << AccountNumber << "] does not exist, please try again: ";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        float Amount = 0;
        cout << "\nPlease enter deposit amount: ";
        Amount = clsInputValidate::ReadFloatNumber();

        char answer;
        cout << "\nAre you sure you want to perform this transaction? ";
        answer = clsInputValidate::ReadChar();

        if(answer == 'Y' || answer == 'y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is: " << Client.getAccountBalance();
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};