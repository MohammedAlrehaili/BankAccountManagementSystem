#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include <iomanip>
#include "../clsMainScreen.h"
#include "../../../Main/Global.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{

private:

    static bool _Login()
    {
        bool LoginFaild = false;
        short FaildLoginCount = 0;

        string Username, Password;

        do
        {
            if(LoginFaild)
            {
                FaildLoginCount++;

                cout << "\nInvalid Username/Password";  
                cout << "\nYou have " << (3-FaildLoginCount) << " Trials to login.\n";
            }

            if(FaildLoginCount == 3)
            {
                cout << "\n\nYou are Locked after " << FaildLoginCount << " Trials to login.";
                return false;
            }

            cout << "\nEnter Username: ";
            cin >> Username;

            cout << "\nEnter Password: ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username,Password);

            LoginFaild = CurrentUser.IsEmpty();
        } while (LoginFaild);

        
        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenu();
        return true;
    }

public:

    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t    Login Screen");
        return _Login();
    }

};