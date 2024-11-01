#pragma once
#include <iostream>
#include <iomanip>
#include "Screen.h"
#include "User.h"
#include "ZInputValidate.h"

class AddUserScreen : protected Screen
{
private:

    static void _ReadUserInfo(User& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = ZInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = ZInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = ZInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = ZInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = ZInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += User::PermissionsEnum::ListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::AddClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::DeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::UpdateClient;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::FindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::Transactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::ManageUsers;
        }

        cout << "\nLogin Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += User::PermissionsEnum::LoginRegister;
        }

        return Permissions;

    }

public:

    static void ShowAddUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\nPlease Enter UserName: ";
        UserName = ZInputValidate::ReadString();
        while (User::DoesUserExists(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = ZInputValidate::ReadString();
        }

        User NewUser = User::AddNewUser(UserName);

        _ReadUserInfo(NewUser);

        User::SaveResult SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
            case  User::SaveResult::Succeded:
                cout << "\nUser Added Successfully :-)\n";
                _PrintUser(NewUser);
                break;

            case User::SaveResult::FailedEmpty:
                cout << "\nError User was not saved because it's Empty";
                break;
        }
    }



};
