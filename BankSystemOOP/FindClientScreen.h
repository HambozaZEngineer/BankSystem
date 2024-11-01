#pragma once
#include <iostream>
#include "Screen.h"
#include "BankClient.h"
#include "ZInputValidate.h"

class FindClientScreen :protected Screen
{

public:

    static void ShowFindClientScreen()
    {
        if (!_CheckAccess(User::PermissionsEnum::FindClient)) return;

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        AccountNumber = ZInputValidate::ReadString();
        while (!BankClient::DoesClientExists(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = ZInputValidate::ReadString();
        }

        BankClient Client1 = BankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client1);

    }

};
