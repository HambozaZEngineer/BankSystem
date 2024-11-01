#pragma once
#include <iostream>
#include <fstream>
#include "Screen.h"
#include "User.h"
#include "MainScreen.h"
#include "ZInputValidate.h"
#include "Global.h"

class LoginScreen : protected Screen
{
private:

	static void _Login()
	{
		cout << "\nEnter UserName: ";
		string userName = ZInputValidate::ReadString();

		cout << "\nEnter Password: ";
		string password = ZInputValidate::ReadString();
		
		currentUser = User::Find(userName, password);

		while (currentUser.IsEmpty())
		{
			trials--;

			if (trials == 0) break;

			cout << "\nLogin failed, UserName or Password is invalid";
			cout << "\nYou have " << trials << " Trials to login." << endl;
			cout << "\nEnter UserName: "; userName = ZInputValidate::ReadString();
			cout << "\nEnter Password: "; password = ZInputValidate::ReadString();
			currentUser = User::Find(userName, password);
		}

		if (trials == 0)
		{
			cout << "You are locked after 3 failed trials" << endl;
			return;
		}

		User::SaveLog(currentUser.LoginRecordLine());
		MainScreen::ShowMainMenu();
	}

public:

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		_Login();
	}
};