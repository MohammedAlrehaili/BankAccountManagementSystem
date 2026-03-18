#pragma once
#include <iostream>
#include "../clsScreen.h"
#include <iomanip>
#include "../../Core/clsBankClient.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{

private:

    static void _PrintTransferLogLine(stTransferLogRegister Log)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Log.DateTime;
        cout << "| " << setw(10) << left << Log.SourceAccountNumber;
        cout << "| " << setw(10) << left << Log.DestinationAccountNumber;
        cout << "| " << setw(10) << left << Log.Amount;
        cout << "| " << setw(10) << left << Log.SourceBalance;
        cout << "| " << setw(10) << left << Log.DestinationBalance;
        cout << "| " << setw(10) << left << Log.UserName;
    }

public:

    static void ShowTransferLogScreen()
    {

        vector <stTransferLogRegister> vLog = clsBankClient::GetTransferLogListList();   
    
        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t   (" + to_string(vLog.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

        if(vLog.size() == 0)
            cout << "\t\t\t\tNo Log Register Available in the system";
        else
            for(stTransferLogRegister Log : vLog)
            {
                _PrintTransferLogLine(Log);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;


    }
};