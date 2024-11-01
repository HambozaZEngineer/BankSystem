#pragma once
#include <iostream>
#include "Screen.h"
#include "BankClient.h"
#include "ZInputValidate.h"

class DeleteClientScreen :protected Screen
{

public:
    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccess(User::PermissionsEnum::DeleteClient)) return;

        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = ZInputValidate::ReadString();
        while (!BankClient::DoesClientExists(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = ZInputValidate::ReadString();
        }

        BankClient Client1 = BankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {


            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }

};
