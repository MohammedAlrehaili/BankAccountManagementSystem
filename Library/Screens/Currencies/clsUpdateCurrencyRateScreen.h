#include <iostream>
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.GetCountry();
        cout << "\nCode       : " << Currency.GetCurrencyCode();
        cout << "\nName       : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) = : " << Currency.GetRate();
        cout << "\n_____________________________\n";
    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\t   Update Currency Screen");

        string CurrencyCode = "";
        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        if(!Currency.IsEmpty())
        {
            _PrintCurrency(Currency);

            char Answer;
            cout << "\nAre you sure you want to update the rate of this Currency y/n: ";
            Answer = clsInputValidate::ReadChar();

            if(Answer == 'y' || Answer == 'Y')
            {
                float Rate;
                cout << "\nUpdate Currency Rate:\n";
                cout << "--------------------------\n";
                cout << "\n Enter New Rate: ";
                Rate = clsInputValidate::ReadFloatNumber();

                Currency.SetRate(Rate);

                cout << "\nCurrency Rate Updated Sucessfully :-)\n";

                _PrintCurrency(Currency);
            }
        }
    }
};