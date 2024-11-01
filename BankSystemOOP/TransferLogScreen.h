#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "BankClient.h"
using namespace std;

class TransferLogScreen : protected Screen
{
private:
    static void _PrintLogRecordLine(BankClient::TransferLog log)
    {
        cout << "\t\t| " << left << setw(24) << log.date;
        cout << "| " << left << setw(9) << log.firstClientAccountNumber;
        cout << "| " << left << setw(9) << log.secondClientAccountNumber;
        cout << "| " << left << setw(7) << log.amount;
        cout << "| " << left << setw(9) << log.firstClientBalanceAfterTransfer;
        cout << "| " << left << setw(11) << log.secondClientBalanceAfterTransfer;
        cout << "| " << left << setw(12) << log.userName;
    }

public:

    static void ShowTransferLogScreen()
    {
        if (!_CheckAccess(User::PermissionsEnum::LoginRegister)) return;

        vector<BankClient::TransferLog> logs = BankClient::GetTransferLogs();

        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(logs.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_______________________________________\n" << endl;

        cout << "\t\t| " << left << setw(24) << "Date/Time";
        cout << "| " << left << setw(9) << "S. Acct";
        cout << "| " << left << setw(9) << "D. Acct";
        cout << "| " << left << setw(7) << "Amount";
        cout << "| " << left << setw(9) << "S. Balance";
        cout << "| " << left << setw(10) << "D. Balance";
        cout << "| " << left << setw(12) << "User" << endl;
        cout << "\t\t_______________________________________________________";
        cout << "_______________________________________\n" << endl;

        if (logs.size() == 0)
        {
            cout << "\t\t\t\tNo records yet...";
        }
        else
        {
            for (BankClient::TransferLog log : logs)
            {
                _PrintLogRecordLine(log);
                cout << endl;
            }
        }


        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_______________________________________\n" << endl;
    }
};