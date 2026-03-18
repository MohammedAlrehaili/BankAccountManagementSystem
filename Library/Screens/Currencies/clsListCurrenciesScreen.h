#include <iostream>
#include "../clsScreen.h"
#include <iomanip>
using namespace std;

class clsListCurrenciesScreen : protected clsScreen
{

private:

    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Currency.GetCountry();
        cout << "| " << setw(15) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(50) << left << Currency.GetCurrencyName();
        cout << "| " << setw(15) << left << Currency.GetRate();
    }

public:

    static void ShowListCurrenciesScreen()
    {

        vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        string Title = "Currencies List Screen";
        string SubTitle = "(" + to_string(vCurrencies.size()) + ") Currency.";

        _DrawScreenHeader(Title,SubTitle);

                cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Country";
        cout << "| " << left << setw(15) << "Code";
        cout << "| " << left << setw(50) << "Name";
        cout << "| " << left << setw(15) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________________________\n" << endl;

        if(vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available in the system";
        else
            for(clsCurrency Currency : vCurrencies)
            {
                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

                cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________________________\n" << endl;

    
    }
};