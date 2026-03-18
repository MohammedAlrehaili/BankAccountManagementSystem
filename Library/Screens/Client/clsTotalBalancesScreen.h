#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{

private:

    static void PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.getAccountNumber();
        cout << "| " << setw(40) << left << Client.getFullName();
        cout << "| " << setw(12) << left << Client.getAccountBalance();
    }

public:

    static void ShowTotalBalancesScreen()
    {

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t   Balances List Screen";
        string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout <<  setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_____________________________________\n" << endl;

        cout <<  setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout <<  setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "______________________________________\n" << endl;

        float TotalBalances = clsBankClient::GetTotalBalances();

        if(vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available in the system";
        else
            for(clsBankClient Client : vClients)
            {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << "\n\t\t_______________________________________________________";
        cout << "______________________________________\n" << endl;
        cout << "\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << "\t\t\t\t\t     ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }


};