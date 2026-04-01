#pragma once
#include <iostream>


class clsPerson
{
private:

	std::string _FirstName;
	std::string _LastName;
	std::string _Email;
	std::string _Phone;
	

public:

	clsPerson(const std::string &FirstName,const std::string &LastName,const std::string &Email,const std::string &Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	//property set and get: 

	void SetFirstName(const std::string &FirstName)
	{
		_FirstName = FirstName;
	}
     std::string GetFirstName()
	{
		return _FirstName;
	}
	void SetLastName(const std::string &LastName)
	{
		_LastName = LastName;
	}
	std::string GetLastName()
	{
		return _LastName;
	}
	void SetEmail(const std::string& Email)
	{
		_Email = Email;
	}
	std::string GetEmail()
	{
		return _Email;
	}
	void SetPhone(const std::string &Phone)
	{
		_Phone = Phone;
	}
	std::string GetPhone()
	{
		return _Phone;
	}
	std::string GetFullName()
	{
		return GetFirstName() + " " + GetLastName();
	}
};

