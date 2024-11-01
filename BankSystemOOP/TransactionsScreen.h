#pragma once
#include <iostream>
#include <iomanip>
#include "ZInputValidate.h"
#include "Screen.h"
#include "DepositScreen.h"
#include "WithdrawScreen.h"
#include "TransferScreen.h"
#include "TransferLogScreen.h"
#include "TotalBalancesScreen.h"

using namespace std;

class TransactionsScreen : protected Screen
{
private:
    enum TransactionsMenuOptions {
        Deposit = 1, Withdraw = 2, Transfer = 3, TransferLog = 4,
        ShowTotalBalance = 5, ShowMainMenu = 6
    };

    static int ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        int choice; cin >> choice;
        return choice;
    }


    static void _ShowDepositScreen()
    {
        DepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        WithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTransferScreen()
    {
        TransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        TransferLogScreen::ShowTransferLogScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        TotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();

    }

    static void _PerformTransactionsMenuOption(TransactionsMenuOptions TransactionsMenuOption)
    {
        system("cls");

        switch (TransactionsMenuOption)
        {
            case TransactionsMenuOptions::Deposit: _ShowDepositScreen(); _GoBackToTransactionsMenu(); break;
            case TransactionsMenuOptions::Withdraw: _ShowWithdrawScreen(); _GoBackToTransactionsMenu(); break;
            case TransactionsMenuOptions::Transfer: _ShowTransferScreen(); _GoBackToTransactionsMenu(); break;
            case TransactionsMenuOptions::TransferLog: _ShowTransferLogScreen(); _GoBackToTransactionsMenu(); break;
            case TransactionsMenuOptions::ShowTotalBalance: _ShowTotalBalancesScreen(); _GoBackToTransactionsMenu(); break;
        }
    }

public:

    static void ShowTransactionsMenu()
    {
        if (!_CheckAccess(User::PermissionsEnum::Transactions))
        {
            _PauseScreen();
            return;
        }

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Transfer.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[5] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenuOption((TransactionsMenuOptions)ReadTransactionsMenuOption());
    }

};