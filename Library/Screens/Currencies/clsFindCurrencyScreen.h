#include <iostream>
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{

private:

    enum enFindMethodOption {FindByCode = 1, FindByCountry = 2};

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

    static enFindMethodOption PerformFindMethodOption(enFindMethodOption MethodOption)
    {
        switch (MethodOption)
        {
        case enFindMethodOption::FindByCode:
            return enFindMethodOption::FindByCode;        
        case enFindMethodOption::FindByCountry:
            return enFindMethodOption::FindByCountry;        
        }
        return enFindMethodOption::FindByCode;
    }

public:

    static void ShowFindCurrencyScreen()
    {

        _DrawScreenHeader("\t   Find Currency Screen");

        enFindMethodOption FindOption;
        cout << "\nFind By: [1] Code or [2] Country: ";
        FindOption = PerformFindMethodOption(enFindMethodOption(clsInputValidate::ReadShortNumberBetween(1,2)));

        if(FindOption == enFindMethodOption::FindByCode)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

            if(!Currency.IsEmpty())
            {
                cout << "\nCurrency Found :-)\n";
                _PrintCurrency(Currency);
            }
            else
            {
                cout << "\nCurrency Was not found.\n";
            }
        }
        else if(FindOption == enFindMethodOption::FindByCountry)
        {
            string CountryName;
            cout << "\nPlease Enter Country Name: ";
            CountryName = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCountry(CountryName);

            if(!Currency.IsEmpty())
            {
                cout << "\nCurrency Found :-)\n";
                _PrintCurrency(Currency);
            }
            else
            {
                cout << "\nCurrency Was not found.\n";
            }
        }
        else
        {
            cout << "\nThere's Been an error.\n";
        }
    }

};