#pragma once
#include "Header Files/screens/clsScreen.h"
#include <iostream>
#include <string>
#include "Header Files/core/clsBankClient.h"
#include "Header Files/lib/clsInputValidate.h"
class clsDeleteClientScreen : protected clsScreen
{
private:

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
	static void _DeleteClient()
	{
		if (!clsScreen::CheckPermitionRight(clsUser::enPermistions::pDelete))
			return;

		clsScreen::_DrawHeaderScreen("\t   Delete Client Screen");
		std::string AccountNumber = clsInputValidate::ReadString("Enter account number: ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			clsScreen::_ClearScreen();
			clsScreen::_DrawHeaderScreen("\t   Delete Client Screen");
			if (toupper(clsInputValidate::ReadLetter("Account number not exist, search again? [Y/N]: ")) == 'Y')
				AccountNumber = clsInputValidate::ReadString("r-enter account number: ");
			else
				return;
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		if (toupper(clsInputValidate::ReadLetter("Are you sure you want to delete client with number [" + AccountNumber + "]? [Y/N]: ")) == 'Y')
		{
			if (Client.Delete(AccountNumber))
			{
				std::cout << "Delete succeded !";
				_PrintClient(Client);
			}
		}
		else
			return;
	}
public:


	static void ShowDeleteClientScreen()
	{
		_DeleteClient();
	}

};

