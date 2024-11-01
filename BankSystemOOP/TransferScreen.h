#pragma once
#include <iostream>
#include "Screen.h"
using namespace std;

class TransferScreen : protected Screen
{
public:
	
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t    Transfer Screen");

        string accountNumber1;
        cout << "\nPlease Enter Account Number to transfer from: ";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        accountNumber1 = ZInputValidate::ReadString();
        while (!BankClient::DoesClientExists(accountNumber1))
        {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber1 = ZInputValidate::ReadString();
        }

        BankClient client1 = BankClient::Find(accountNumber1);

        _PrintClient(client1);

        string accountNumber2;
        cout << "\nPlease Enter Account Number to transfer to: ";

        accountNumber2 = ZInputValidate::ReadString();
        while (!BankClient::DoesClientExists(accountNumber2))
        {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber2 = ZInputValidate::ReadString();
        }

        while (accountNumber1 == accountNumber2)
        {
            cout << "\nYou can't transfer to the same person, choose another one: ";
            accountNumber2 = ZInputValidate::ReadString();
        }

        BankClient client2 = BankClient::Find(accountNumber2);

        _PrintClient(client2);

        cout << "Enter transfer amount: ";
        float transferAmount; cin >> transferAmount;

        while (transferAmount > client1.AccountBalance)
        {
            cout << "Amount exceeds the available balance, please enter another amount: ";
            cin >> transferAmount;
        }

        cout << "Are you sure you want to perform this operation (y/n)?: ";
        char choice; cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            client1.Transfer(transferAmount, client2);
            cout << "\nTransfer done successfully.\n" << endl;
            _PrintClient(client1);
            _PrintClient(client2);
        }
    }
};