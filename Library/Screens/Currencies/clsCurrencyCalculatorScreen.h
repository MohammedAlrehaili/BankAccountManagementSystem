#include <iostream>
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

    static void _PrintCurrency(clsCurrency Currency, string Title)
    {
        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.GetCountry();
        cout << "\nCode       : " << Currency.GetCurrencyCode();
        cout << "\nName       : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) = : " << Currency.GetRate();
        cout << "\n_____________________________\n";
    }

    static clsCurrency _GetCurrency(string message)
    {
        string CurrencyCode;
        cout << message << endl;

        CurrencyCode = clsInputValidate::ReadString();

        while(!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;
    }

    static void _PrintCalculationsResult(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrency(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInUSD << " USD\n";

        if(Currency2.GetCurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrency(Currency2, "Convert To:");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.GetCurrencyCode() << endl;
 
    }

public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\t   Currency Calculator Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");

            cout << "\nPlease Enter Amount: ";
            float Amount = clsInputValidate::ReadFloatNumber();

            _PrintCalculationsResult(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ";
            Continue = clsInputValidate::ReadChar();
        }
    }
};