#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Person.h"
#include "ZString.h"
#include "ZDate.h"
#include "Global.h"
using namespace std;

class BankClient : public Person
{
private:
	enum Mode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	Mode _mode;

	string _accountNumber;
	string _pinCode;
	float _accountBalance;
	bool _markedForDelete = false;

	/* ------------------------------------------ Private Functions ------------------------------------------ */
	/* --- Data Management --- */
	static BankClient _LineToClient(string line, string delimator = "#//#")
	{
		vector<string> info = ZString::Split(line, delimator);

		return BankClient(Mode::UpdateMode, info[0], info[1], info[2], info[3], info[4], info[5], stod(info[6]));
	}

	static string _ClientToLine(BankClient client, string delimator = "#//#")
	{
		string line = "";

		line += client.FirstName + delimator; line += client.LastName + delimator;
		line += client.Email + delimator; line += client.Phone + delimator;
		line += client.GetAccountNumber() + delimator; line += client.PinCode + delimator;
		line += to_string(client.AccountBalance);

		return line;
	}

	static BankClient _GetEmptyClient()
	{
		return BankClient(Mode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<BankClient> _LoadClientsDataFromFile()
	{
		vector<BankClient> clients;

		fstream file("clients.txt", ios::in);

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clients.push_back(_LineToClient(line));
			}

			file.close();
		}

		return clients;
	}

	static void _SaveClientsDataToFile(vector<BankClient> clients)
	{
		fstream file("clients.txt", ios::out);

		if (file.is_open())
		{
			for (BankClient& client : clients)
			{
				if(!client._markedForDelete)
				{
					string line = _ClientToLine(client);
					file << line << endl;
				}
			}

			file.close();
		}
	}

	static void _AddNewLineToFile(string line)
	{
		fstream file("clients.txt", ios::app);

		if (file.is_open())
		{
			file << line << endl;

			file.close();
		}
	}

	void _Update()
	{
		vector<BankClient> clients;
		clients = _LoadClientsDataFromFile();

		for (BankClient& client : clients)
		{
			if (client.GetAccountNumber() == _accountNumber)
			{
				client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(clients);
	}

	void _AddNew()
	{
		_AddNewLineToFile(_ClientToLine(*this));
	}

	/* ------------------------------------------ Private Functions _Finished_ ------------------------------------------ */


	/* ------------------------------------------ Private TransferLog Functions ------------------------------------------ */
	struct TransferLog;

	static string _TransferLogToLine(string firstClientAc, string secondClientAc, float amount, float firstBalance, float secondBalance)
	{
		string line = "";
		string delimator = "#//#";
		line += ZDate::GetCurrentTime() + delimator; line += firstClientAc + delimator;
		line += secondClientAc + delimator; line += to_string(amount) + delimator;
		line += to_string(firstBalance) + delimator; line += to_string(secondBalance) + delimator;
		line += currentUser.UserName;

		return line;
	}

	static TransferLog _LineToTransferLog(string line)
	{
		vector<string> info = ZString::Split(line, "#//#");
		TransferLog log;

		log.date = info[0]; log.firstClientAccountNumber = info[1];
		log.secondClientAccountNumber = info[2]; log.amount = stod(info[3]);
		log.firstClientBalanceAfterTransfer = stod(info[4]); log.secondClientBalanceAfterTransfer = stod(info[5]);
		log.userName = info[6];

		return log;
	}

	static void _SaveTransferLog(string line)
	{
		fstream file("transfer_log.txt", ios::out | ios::app);

		if (file.is_open())
		{
			file << line << endl;
			file.close();
		}
	}

	static vector<TransferLog> _LoadTransferLogs()
	{
		fstream file("transfer_log.txt", ios::in);
		
		vector<TransferLog> logs;

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				logs.push_back(_LineToTransferLog(line));
			}

			file.close();
		}

		return logs;
	}
	/* ------------------------------------------ Private TransferLog Functions _Finished_ ------------------------------------------ */


public:
	BankClient(Mode mode, string firstName, string lastName, string email, string phone, string accountNumber, 
		string pinCode, float accountBalance) : Person(firstName, lastName, email, phone)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = accountBalance;
	}


	/* ------------------------------------------ Getter And Setters ------------------------------------------ */
	bool IsEmpty() { return _mode == Mode::EmptyMode; }

	string GetAccountNumber() { return _accountNumber; }

	string GetPinCode() { return _pinCode; }
	void SetPinCode(string value) { _pinCode = value; }
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	float GetAccountBalance() { return _accountBalance; }
	void SetAccountBalance(float value) { _accountBalance = value; }
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	/* ------------------------------------------ Getter And Setters _Finished_ ------------------------------------------ */

	/* ------------------------------------------ Public TransferLog Functions ------------------------------------------ */

	struct TransferLog
	{
		string date;
		string firstClientAccountNumber;
		string secondClientAccountNumber;
		float amount;
		float firstClientBalanceAfterTransfer;
		float secondClientBalanceAfterTransfer;
		string userName;
	};

	static vector<TransferLog> GetTransferLogs()
	{
		return _LoadTransferLogs();
	}
	/* ------------------------------------------ Public TransferLog Functions _Finished_------------------------------------------ */

	/* ------------------------------------------ Public Functions ------------------------------------------ */

	static BankClient Find(string accountNumber)
	{
		vector<BankClient> clients;

		fstream reader("clients.txt", ios::in);

		if (reader.is_open())
		{
			string line;

			while (getline(reader, line))
			{
				BankClient client = _LineToClient(line);

				if (client.GetAccountNumber() == accountNumber)
				{
					reader.close();
					return client;
				}
			}

			reader.close();
		}

		return _GetEmptyClient();
	}

	static BankClient Find(string accountNumber, string pinCode)
	{
		vector<BankClient> clients;

		fstream reader("clients.txt", ios::in);

		if (reader.is_open())
		{
			string line;

			while (getline(reader, line))
			{
				BankClient client = _LineToClient(line);

				if (client.GetAccountNumber() == accountNumber && client.PinCode == pinCode)
				{
					reader.close();
					return client;
				}
			}

			reader.close();
		}

		return _GetEmptyClient();
	}

	enum SaveResult { FailedEmpty = 0, Succeded = 1};

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
		vector<BankClient> clients = _LoadClientsDataFromFile();

		for (BankClient& client : clients)
		{
			if (client.GetAccountNumber() == _accountNumber)
			{
				client._markedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(clients);

		*this = _GetEmptyClient();

		return true;
	}

	void Deposit(float amount)
	{
		_accountBalance += amount;
		_Update();
	}

	bool Withdraw(float amount)
	{
		if (amount > AccountBalance) return false;

		_accountBalance -= amount;
		_Update();

		return true;
	}

	void Transfer(float amount, BankClient& client2)
	{
		this->Withdraw(amount);
		client2.Deposit(amount);
		_SaveTransferLog(_TransferLogToLine(_accountNumber, client2.GetAccountNumber(), amount, _accountBalance, client2.AccountBalance));
	}

	static bool DoesClientExists(string accountNumber)
	{
		BankClient client = BankClient::Find(accountNumber);

		return !client.IsEmpty();
	}

	static BankClient AddNewClient(string accountNumber)
	{
		return BankClient(Mode::AddNewMode, "", "", "", "", accountNumber, "", 0);
	}

	static vector<BankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		vector<BankClient> clients = _LoadClientsDataFromFile();
		float totalBalances = 0;

		for (BankClient& client : clients)
		{
			totalBalances += client.AccountBalance;
		}

		return totalBalances;
	}

	/* ------------------------------------------ Public Functions _Finished_ ------------------------------------------ */



};
