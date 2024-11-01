#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Screen.h"
#include "User.h"

class LoginRegisterScreen : protected Screen
{
private:
    static void _PrintLogRecordLine(User::LogInfo log)
    {
        cout << "\t\t| " << left << setw(28) << log.date;
        cout << "| " << left << setw(25) << log.userName;
        cout << "| " << left << setw(17) << log.password;
        cout << "| " << left << setw(12) << log.permissions;
    }

public:
	
	static void ShowLoginRegisterScreen()
	{
        if (!_CheckAccess(User::PermissionsEnum::LoginRegister)) return;

        vector<User::LogInfo> logs = User::LoadLogs();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(logs.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_______________________________________\n" << endl;

        cout << "\t\t| " << left << setw(28) << "Date/Time";
        cout << "| " << left << setw(25) << "UserName";
        cout << "| " << left << setw(17) << "Password";
        cout << "| " << left << setw(12) << "Permissions" << endl;
        cout << "\t\t_______________________________________________________";
        cout << "_______________________________________\n" << endl;

        if (logs.size() == 0)
        {
            cout << "\t\t\t\tNo records yet...";
        }
        else
        {
            for (User::LogInfo log : logs)
            {
                _PrintLogRecordLine(log);
                cout << endl;
            }
        }


        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_______________________________________\n" << endl;
	}
};