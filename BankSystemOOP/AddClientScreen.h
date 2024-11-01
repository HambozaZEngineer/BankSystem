#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "Screen.h"
#include "BankClient.h"
#include "ZInputValidate.h"

class AddClientScreen : protected Screen
{
private:
    static void _ReadClientInfo(BankClient& client)
    {
        cout << "\nEnter FirstName: ";
        client.FirstName = ZInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        client.LastName = ZInputValidate::ReadString();

        cout << "\nEnter Email: ";
        client.Email = ZInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        client.Phone = ZInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        client.PinCode = ZInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        float accountBalance; cin >> accountBalance;
        client.AccountBalance = accountBalance;
    }

public:

    static void ShowAddClientScreen()
    {
        if (!_CheckAccess(User::PermissionsEnum::AddClient)) return;

        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = ZInputValidate::ReadString();
        while (BankClient::DoesClientExists(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = ZInputValidate::ReadString();
        }

        BankClient NewClient = BankClient::AddNewClient(AccountNumber);

        _ReadClientInfo(NewClient);

        BankClient::SaveResult saveResult = NewClient.Save();

        switch (saveResult)
        {
            case  BankClient::SaveResult::Succeded:
                cout << "\nAccount Added Successfully :-)\n";
                _PrintClient(NewClient);
                break;

            case BankClient::SaveResult::FailedEmpty:
                cout << "\nError account was not saved because it's Empty";
                break;
        }
    }
};
