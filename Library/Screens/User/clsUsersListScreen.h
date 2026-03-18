#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include <iomanip>

using namespace std;

class clsUsersListScreen : protected clsScreen
{

private:

    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.GetUserName();
        cout << "| " << setw(20) << left << User.getFullName();
        cout << "| " << setw(12) << left << User.getPhone();
        cout << "| " << setw(35) << left << User.getEmail();
        cout << "| " << setw(30) << left << clsString::Encryption(User.GetPassword(),5);
        cout << "| " << setw(12) << left << User.GetPermissions();
    }

public:

    static void ShowUsersList()
    {

        vector <clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(35) << "Email";
        cout << "| " << left << setw(30) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________________________________________________\n" << endl;

        if(vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available in the system";
        else
            for(clsUser User : vUsers)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________________________________________________\n" << endl;

    }



};
