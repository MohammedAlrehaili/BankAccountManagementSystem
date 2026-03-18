#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include <iomanip>
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{

private:

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:\n\n";
        cout << "----------------------------------------------------------\n";
        cout << left << setw(18) << "FirstName    :"   << User.getFirstName() << endl;
        cout << left << setw(18) << "LastName     :"   << User.getLastName() << endl;
        cout << left << setw(18) << "Full Name    :"   << User.getFullName() << endl;
        cout << left << setw(18) << "Email        :"   << User.getEmail() << endl;
        cout << left << setw(18) << "Phone        :"   << User.getPhone() << endl;
        cout << left << setw(18) << "User Name    :"   << User.GetUserName() << endl;
        cout << left << setw(18) << "Password     :"   << User.GetPassword() << endl;
        cout << left << setw(18) << "Permissions  :"   << User.GetPermissions() << endl;
        cout << "----------------------------------------------------------\n";
    }

public:

    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while(!clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        char answer = 'n';
        cout << "\nAre you sure you want to delete this user y/n? ";
        answer = clsInputValidate::ReadChar();

        if(answer == 'y' || answer == 'Y')
        {

            if(User.Delete())
            {
            cout << "\nUser Deleted Successfully :-)\n";

            _PrintUser(User);

            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};
