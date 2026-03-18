#pragma once
#include <iostream>
#include "../Core/clsCurrency.h"
#include "../../Main/Global.h"
using namespace std;

class clsScreen
{

protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\tUser: " << CurrentUser.GetUserName();
        cout << "\n\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl; 
    }

    static bool CheckAccessRights(clsUser::enPermissions Permissions)
    {
        if(!CurrentUser.CheckAccessPermission(Permissions))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};