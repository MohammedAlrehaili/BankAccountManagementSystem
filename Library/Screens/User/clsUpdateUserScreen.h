#include <iostream>
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsScreen.h"
#include <iomanip>
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{

private:

    static void _ReadUserInfo(clsUser &User)
    {
        cout << "\nEnter FirstName: ";
        User.setFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.setLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.setEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.setPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.setPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permissions: ";
        User.setPermissions(_ReadPermissionsToSet());
    }

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

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        
        char Answer = 'n';
        cout << "\nDo you want to give full access? ";
        Answer = clsInputValidate::ReadChar();

        if(Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n";

        cout << "\nShow Client List? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client List? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage Users? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nLogin Register? ";
        Answer = clsInputValidate::ReadChar();
        if(Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;
    }

public:

    static void ShowUpdateUserScreen()
    {

        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter Client UserName: ";
        UserName = clsInputValidate::ReadString();
        while(!clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        cout << "\nAre you sure you want to update this User? ";
        char answer = clsInputValidate::ReadChar();

        if(answer == 'Y' || answer == 'y')
        {
            _ReadUserInfo(User);
        
            
            clsUser::enSaveResult SaveResult;

            SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUser::enSaveResult::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResult::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;
            }
            }
        }
    }

};
