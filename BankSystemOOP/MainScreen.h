#pragma once
#include <iostream>
#include <iomanip>
#include "ZInputValidate.h"
#include "Screen.h"
#include "User.h"
#include "ClientsListScreen.h"
#include "AddClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientScreen.h"
#include "FindClientScreen.h"
#include "TransactionsScreen.h"
#include "ManageUsersScreen.h"
#include "LoginRegisterScreen.h"
#include "Global.h"
using namespace std;

class MainScreen : protected Screen
{
private:

    enum MainMenuOptions {Show_All_Clients = 1, Add_Client = 2, Delete_Client = 3, Update_Client = 4, 
        Find_Client = 5, Transactions = 6, Manage_Users = 7, Login_Register = 8, Logout  = 9};

    static int _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        int choice; cin >> choice;
        return choice;
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";

        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowAllClientsScreen()
    {
        ClientListScreen::ShowClientsList();
    }

    static void _ShowAddClientScreen()
    {
        AddClientScreen::ShowAddClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        DeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        UpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        FindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsScreen()
    {
        TransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersScreen()
    {
        ManageUsersScreen::ShowManageUsersMenu();
    }

    static void _ShowLoginRegisterScreen()
    {
        LoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowLogoutScreen()
    {
        currentUser = User::Find("", "");
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void _PerformMainMenuOption(MainMenuOptions option)
    {
        system("cls");
        switch (option)
        {
            case MainMenuOptions::Show_All_Clients: _ShowAllClientsScreen(); _GoBackToMainMenu(); break;
            case MainMenuOptions::Add_Client: _ShowAddClientScreen(); _GoBackToMainMenu(); break;
            case MainMenuOptions::Delete_Client: _ShowDeleteClientScreen(); _GoBackToMainMenu(); break;
            case MainMenuOptions::Update_Client: _ShowUpdateClientScreen(); _GoBackToMainMenu(); break;
            case MainMenuOptions::Find_Client: _ShowFindClientScreen(); _GoBackToMainMenu(); break;
            case MainMenuOptions::Transactions: _ShowTransactionsScreen(); ShowMainMenu(); break;
            case MainMenuOptions::Manage_Users: _ShowManageUsersScreen(); ShowMainMenu(); break;
            case MainMenuOptions::Login_Register: _ShowLoginRegisterScreen(); _GoBackToMainMenu(); break;
            case MainMenuOptions::Logout: _ShowLogoutScreen(); break;
        }
    }

public:	

    static void ShowMainMenu()
    {
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n"; 
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

       _PerformMainMenuOption((MainMenuOptions)_ReadMainMenuOption());
    }
};