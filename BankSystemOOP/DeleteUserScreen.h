#pragma once
#include <iostream>
#include "Screen.h"
#include "Person.h"
#include "User.h"
#include "ZInputValidate.h"

class DeleteUserScreen : protected Screen
{

public:
    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\nPlease Enter UserName: ";
        UserName = ZInputValidate::ReadString();
        while (!User::DoesUserExists(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = ZInputValidate::ReadString();
        }

        User User1 = User::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User1.UserName == "Admin")
            {
                cout << "\nYou can't delete admin." << endl; return;
            }
            if (User1.UserName == currentUser.UserName)
            {
                cout << "\nYou can't delete yourself." << endl; return;
            }

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};
