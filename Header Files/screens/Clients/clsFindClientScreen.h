#pragma once
#include <iostream>
#include <string>
#include "Header Files/core/clsBankClient.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include <cctype>
class clsFindClientScreen :protected clsScreen
{
	static void _PrintClient(clsBankClient& Client)
	{
		std::cout << "Client Card:\n";
		std::cout << "-------------------------------\n";
		std::cout << "First Name: " << Client.GetFirstName() << std::endl;
		std::cout << "Last Name: " << Client.GetLastName() << std::endl;
		std::cout << "Full Name: " << Client.GetFullName() << std::endl;
		std::cout << "Account Number: " << Client.GetAccountNumber() << std::endl;
		std::cout << "Password: " << Client.GetPinCode() << std::endl;
		std::cout << "E-mail: " << Client.GetEmail() << std::endl;
		std::cout << "Phone: " << Client.GetPhone() << std::endl;
		std::cout << "Balance: " << Client.GetBalance() << std::endl;
		std::cout << "-------------------------------\n";
	}
	static void _FindClient()
	{
		if (!clsScreen::CheckPermitionRight(clsUser::enPermistions::pFind))
			return;

		clsScreen::_DrawHeaderScreen("\t   Find Client");
		std::string AccountNumber = clsInputValidate::ReadString("Enter you account number: ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			clsScreen::_ClearScreen();
			clsScreen::_DrawHeaderScreen("\t   Find Client");
			if (toupper(clsInputValidate::ReadLetter("Account number not exist, search again? [Y/N]: ")) == 'Y')
				AccountNumber = clsInputValidate::ReadString("r-enter account number: ");
			else
				return;
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		if (Client.isEmpty())
		{
						std::cout << "\nError client not found\n\n";		
		}
		else
			std::cout << "\nclient found successfully :-)\n\n";
		_PrintClient(Client);
	}
public:
	static void ShowFindClientScreen()
	{
		_FindClient();
	}


};

