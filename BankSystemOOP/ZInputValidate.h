//ProgrammingAdivces.com
//Mohammed Abu-Hadhoud

#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "ZString.h"
#include "ZDate.h"

class ZInputValidate
{

public:

	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(int Number , int From, int To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsDateBetween(ZDate Date, ZDate From, ZDate To)
	{
		//Date>=From && Date<=To
		if ((ZDate::IsDate1AfterDate2(Date, From) || ZDate::IsDate1EqualDate2(Date, From)) 
			&&
			(ZDate::IsDate1BeforeDate2(Date, To) || ZDate::IsDate1EqualDate2(Date, To))
		  )
		{
			return true;
		}
		
		//Date>=To && Date<=From
		if ((ZDate::IsDate1AfterDate2(Date, To) || ZDate::IsDate1EqualDate2(Date, To)) 
			&&
			(ZDate::IsDate1BeforeDate2(Date, From) || ZDate::IsDate1EqualDate2(Date, From))
		   )
		{
			return true;
		}

		return false;
	}

	static string ReadString()
	{
		string result;

		getline(cin, result);

		return result;
	}

	static int ReadIntNumber(string ErrorMessage="Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage ;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage="Number is not within range, Enter again:\n")
	{
		int Number=ReadIntNumber();

		while (!IsNumberBetween(Number,From,To)) 
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static bool IsValideDate(ZDate Date)
	{
		return	ZDate::IsValidDate(Date);
	}

};

