#pragma once
#include <iostream>
#include "Screen.h"
#include "User.h"
#include "ZInputValidate.h"

class FindUserScreen : protected Screen
{

public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        UserName = ZInputValidate::ReadString();
        while (!User::DoesUserExists(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = ZInputValidate::ReadString();
        }

        User User1 = User::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};
