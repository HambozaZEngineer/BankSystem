#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person
{
private:
	string _firstName;
	string _lastName;
	string _email;
	string _phone;

public:
	Person(string firstName, string lastName, string email, string phone)
	{
		_firstName = firstName;
		_lastName = lastName;
		_email = email;
		_phone = phone;
	}


	/* ------------------------------------------ Getter And Setters ------------------------------------------ */
	string GetFirstName() { return _firstName; }
	void SetFirstName(string value) { _firstName = value; }
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	string GetLastName() { return _lastName; }
	void SetLastName(string value) { _lastName = value; }
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	string GetFullName() { return _firstName + " " + _lastName; }

	string GetEmail() { return _email; }
	void SetEmail(string value) { _email = value; }
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	string GetPhone() { return _phone; }
	void SetPhone(string value) { _phone = value; }
	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;
	/* ------------------------------------------ Getter And Setters _Finished ------------------------------------------ */

};