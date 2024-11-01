#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"
#include "ZString.h"
using namespace std;

class User : public Person
{
private:
	enum Mode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	Mode _mode;
	string _userName;
	string _password;
	int _permissions;
	bool _markedForDelete = false;

	/* ------------------------------------------ Private Functions ------------------------------------------ */
		/* --- Data Management --- */
	static User _LineToUser(string line, string delimator = "#//#")
	{
		vector<string> info = ZString::Split(line, delimator);
		
		return User(Mode::UpdateMode, info[0], info[1], info[2], info[3], info[4], ZString::Decrypt(info[5], 3), stoi(info[6]));
	}

	static string _UserToLine(User user, string delimator = "#//#")
	{
		string line = "";

		line += user.FirstName + delimator; line += user.LastName + delimator;
		line += user.Email + delimator; line += user.Phone + delimator;
		line += user.UserName + delimator; line += ZString::Encrypt(user.Password, 3) + delimator;
		line += to_string(user.Permissions);

		return line;
	}

	static User _GetEmptyUser()
	{
		return User(Mode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<User> _LoadUsersDataFromFile()
	{
		vector<User> users;

		fstream file("users.txt", ios::in);

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				users.push_back(_LineToUser(line));
			}

			file.close();
		}

		return users;
	}

	static void _SaveUsersDataToFile(vector<User> users)
	{
		fstream file("users.txt", ios::out);

		if (file.is_open())
		{
			for (User& user : users)
			{
				if (!user._markedForDelete)
				{
					string line = _UserToLine(user);
					file << line << endl;
				}
			}

			file.close();
		}
	}

	static void _AddNewLineToFile(string line)
	{
		fstream file("users.txt", ios::app);

		if (file.is_open())
		{
			file << line << endl;

			file.close();
		}
	}

	void _Update()
	{
		vector<User> users;
		users = _LoadUsersDataFromFile();

		for (User& user : users)
		{
			if (user.UserName == UserName)
			{
				user = *this;
				break;
			}
		}

		_SaveUsersDataToFile(users);
	}

	void _AddNew()
	{
		_AddNewLineToFile(_UserToLine(*this));
	}

	/* ------------------------------------------ Private Functions _Finished_ ------------------------------------------ */


	/* ------------------------------------------ Private Log Functions ------------------------------------------ */

	struct LogInfo;
	static LogInfo _LineToLog(string line)
	{
		vector<string> info = ZString::Split(line, "#//#");
		LogInfo log;

		log.date = info[0]; log.userName = info[1];
		log.password = info[2]; log.permissions = stoi(info[3]);

		return log;
	}
	/* ------------------------------------------ Private Log Functions _Finished_ ------------------------------------------ */

public:

	enum PermissionsEnum {
		All = -1, ListClients = 1, AddClient = 2, DeleteClient = 4, UpdateClient = 8, FindClient = 16,
		Transactions = 32, ManageUsers = 64, LoginRegister = 128
	};

	User(Mode mode, string firstName, string lastName, string email, string phone, string userName,
		string password, int permissions) : Person(firstName, lastName, email, phone)
	{
		_mode = mode;
		_userName = userName;
		_password = password;
		_permissions = permissions;
	}


	/* ------------------------------------------ Getter And Setters ------------------------------------------ */
	bool IsEmpty() { return _mode == Mode::EmptyMode; }

	string GetUserName() { return _userName; }
	void SetUserName(string value) { _userName = value; }
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	string GetPassword() { return _password; }
	void SetPassword(string value) { _password = value; }
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	int GetPermissions() { return _permissions; }
	void SetPermissions(int value) { _permissions = value; }
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
	/* ------------------------------------------ Getter And Setters _Finished_ ------------------------------------------ */


	/* ------------------------------------------ Public Functions ------------------------------------------ */

	static User Find(string userName)
	{
		vector<User> users;

		fstream reader("users.txt", ios::in);

		if (reader.is_open())
		{
			string line;

			while (getline(reader, line))
			{
				User user = _LineToUser(line);

				if (user.UserName == userName)
				{
					reader.close();
					return user;
				}
			}

			reader.close();
		}

		return _GetEmptyUser();
	}

	static User Find(string userName, string password)
	{
		vector<User> users;

		fstream reader("users.txt", ios::in);

		if (reader.is_open())
		{
			string line;

			while (getline(reader, line))
			{
				User user = _LineToUser(line);

				if (user.UserName == userName && user.Password == password)
				{
					reader.close();
					return user;
				}
			}

			reader.close();
		}

		return _GetEmptyUser();
	}

	enum SaveResult { FailedEmpty = 0, Succeded = 1 };

	SaveResult Save()
	{
		switch (_mode)
		{
		case Mode::EmptyMode: return SaveResult::FailedEmpty;
		case Mode::UpdateMode: _Update(); return SaveResult::Succeded;
		case Mode::AddNewMode: _AddNew(); return SaveResult::Succeded;
		}
	}

	bool Delete()
	{
		vector<User> users = _LoadUsersDataFromFile();

		for (User& user : users)
		{
			if (user.UserName == UserName)
			{
				user._markedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(users);

		*this = _GetEmptyUser();

		return true;
	}

	static bool DoesUserExists(string userName)
	{
		User user = User::Find(userName);

		return !user.IsEmpty();
	}

	static User AddNewUser(string userName)
	{
		return User(Mode::AddNewMode, "", "", "", "", userName, "", 0);
	}

	static vector<User> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(User::PermissionsEnum permission)
	{
		if (this->Permissions == PermissionsEnum::All) return true;
		if ((permission & this->Permissions) == permission) return true;

		return false;
	}

	string LoginRecordLine()
	{
		string line;
		string delimator = "#//#";
		line += ZDate::GetCurrentTime() + delimator;
		line += UserName + delimator;
		line += Password + delimator;
		line += to_string(Permissions);

		return line;
	}

	/* ------------------------------------------ Public Functions _Finished_ ------------------------------------------ */


	/* ------------------------------------------ Public Log Functions ------------------------------------------ */

	struct LogInfo
	{
		string date;
		string userName;
		string password;
		int permissions;
	};

	static void SaveLog(string line)
	{
		fstream file("log.txt", ios::out | ios::app);

		if (file.is_open())
		{
			file << line << endl;

			file.close();
		}
	}

	static vector<LogInfo> LoadLogs()
	{
		fstream file("log.txt", ios::in);

		vector<LogInfo> logs;

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				logs.push_back(_LineToLog(line));
			}

			file.close();
		}

		return logs;
	}
	/* ------------------------------------------ Log Functions _Finished_ ------------------------------------------ */
};