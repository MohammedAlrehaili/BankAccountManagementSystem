#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

private:

    static void ReadClientInfo(clsBankClient &Client)
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
        cout << "\n\nUpdate Client Info::\n\n";
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

    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClient(Client);

        cout << "\nAre you sure you want to update this client? ";
        char answer = clsInputValidate::ReadChar();

        if(answer == 'Y' || answer == 'y')
        {
            ReadClientInfo(Client);
        
            
            clsBankClient::enSaveResult SaveResult;

            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResult::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client);
                break;
            }
            case clsBankClient::enSaveResult::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
    }

};
