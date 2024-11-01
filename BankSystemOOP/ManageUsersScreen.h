#pragma once
#include <iostream>
#include <iomanip>
#include "ZInputValidate.h"
#include "Screen.h"
#include "ListUsersScreen.h"
#include "AddUserScreen.h"
#include "DeleteUserScreen.h"
#include "UpdateUserScreen.h"
#include "FindUserScreen.h"

using namespace std;

class ManageUsersScreen : protected Screen
{

private:
    enum ManageUsersMenuOptions {
        ListUsers = 1, AddNewUser = 2, DeleteUser = 3,
        UpdateUser = 4, FindUser = 5, MainMenue = 6
    };

    static int ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        int choice; cin >> choice;
        return choice;
        return choice;
    }

    static void _GoBackToManageUsersMenu()
    {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen()
    {
        ListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        AddUserScreen::ShowAddUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        DeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        UpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        FindUserScreen::ShowFindUserScreen();
    }


    static void _PerformManageUsersMenuOption(ManageUsersMenuOptions manageUsersMenuOption)
    {
        system("cls");

        switch (manageUsersMenuOption)
        {
            case ManageUsersMenuOptions::ListUsers: _ShowListUsersScreen(); _GoBackToManageUsersMenu(); break;
            case ManageUsersMenuOptions::AddNewUser: _ShowAddNewUserScreen(); _GoBackToManageUsersMenu(); break;
            case ManageUsersMenuOptions::DeleteUser: _ShowDeleteUserScreen(); _GoBackToManageUsersMenu(); break;
            case ManageUsersMenuOptions::UpdateUser: _ShowUpdateUserScreen(); _GoBackToManageUsersMenu(); break;
            case ManageUsersMenuOptions::FindUser: _ShowFindUserScreen(); _GoBackToManageUsersMenu(); break;
        }
    }



public:

    static void ShowManageUsersMenu()
    {
        if (!_CheckAccess(User::PermissionsEnum::ManageUsers))
        {
            _PauseScreen();
            return;
        }

        system("cls");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenuOption((ManageUsersMenuOptions)ReadManageUsersMenuOption());
    }

};
