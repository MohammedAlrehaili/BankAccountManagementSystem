#pragma once
#include <iostream>
#include "../clsScreen.h"
#include <iomanip>
using namespace std;

class clsLoginRegisterListScreen : protected clsScreen
{

private:

    static void _PrintLoginRegisterLine(stLoginRegisterRecord Log)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Log.DateTime;
        cout << "| " << setw(20) << left << Log.UserName;
        cout << "| " << setw(20) << left << Log.Password;
        cout << "| " << setw(20) << left << Log.Permissions;
    }

public:

    static void ShowLoginRegisterList()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }

        vector <stLoginRegisterRecord> vLog = clsUser::GetLoginRegisterList();   
    
        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t   (" + to_string(vLog.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(20) << "Premissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

        if(vLog.size() == 0)
            cout << "\t\t\t\tNo Log Register Available in the system";
        else
            for(stLoginRegisterRecord Log : vLog)
            {
                _PrintLoginRegisterLine(Log);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

    }



};