#pragma once
#include <iostream>
#include "Screen.h"
#include "Person.h"
#include "BankClient.h"
#include "ZInputValidate.h"

class UpdateClientScreen :protected Screen
{
private:

    static void ReadClientInfo(BankClient& Client)
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\nEnter FirstName: ";
        Client.FirstName = ZInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = ZInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = ZInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = ZInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = ZInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        float accountBalance; cin >> accountBalance;
        Client.AccountBalance = accountBalance;
    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!_CheckAccess(User::PermissionsEnum::UpdateClient)) return;

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = ZInputValidate::ReadString();

        while (!BankClient::DoesClientExists(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = ZInputValidate::ReadString();
        }

        BankClient Client1 = BankClient::Find(AccountNumber);

        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";


            ReadClientInfo(Client1);


            BankClient::SaveResult saveResult = Client1.Save();

            switch (saveResult)
            {
            case  BankClient::SaveResult::Succeded:
                cout << "\nAccount Added Successfully :-)\n";
                _PrintClient(Client1);
                break;

            case BankClient::SaveResult::FailedEmpty:
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }

    }
};
