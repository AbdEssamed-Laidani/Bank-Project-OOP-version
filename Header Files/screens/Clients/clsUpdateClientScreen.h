#pragma once
#include <iostream>
#include <string>
#include "Header Files/core/clsBankClient.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
class clsUpdateClientScreen : clsScreen
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
	static void ReadClientInfo(clsBankClient& Client)
	{

		Client.SetFirstName(clsInputValidate::ReadString("Enter your first name: "));
		Client.SetLastName(clsInputValidate::ReadString("Enter your last name: "));
		Client.SetEmail(clsInputValidate::ReadString("Enter your email: "));
		Client.SetPhone(clsInputValidate::ReadString("Enter your phone number: "));
		Client.SetPinCode(clsInputValidate::ReadString("Enter your pincode: "));
		Client.SetBalance(clsInputValidate::ReadPositiveNumber<double>("Enter your balance: "));

	}
	static void _UpdateClient()
	{
		if (!clsScreen::CheckPermitionRight(clsUser::enPermistions::pUpdate))
			return;

		clsScreen::_DrawHeaderScreen("\t   Update Client Screen");
		std::string AccountNumber = clsInputValidate::ReadString("Enter you account number: ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			clsScreen::_ClearScreen();
			clsScreen::_DrawHeaderScreen("\t   Update Client Screen");
			if (toupper(clsInputValidate::ReadLetter("Account number not exist, search again? [Y/N]: ")) == 'Y')
				AccountNumber = clsInputValidate::ReadString("r-enter account number: ");
			else
				return;
		}
		clsScreen::_ClearScreen();
		clsScreen::_DrawHeaderScreen("\t   Update Client Screen");

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);
		if (toupper(clsInputValidate::ReadLetter("Are you sure you want to update client with number [" + AccountNumber + "]? [Y/N]: ")) == 'Y')
		{
			ReadClientInfo(Client1);
			clsBankClient::enSaveResult SaveResult = Client1.save();
			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svFailedEmpty:
				std::cout << "\n\nsave falied empty object :-(\n\n";
				break;
			case clsBankClient::enSaveResult::svSucceded:
				std::cout << "\n\nsave succeded :-)\n\n";
				break;
			case clsBankClient::enSaveResult::svFailedFileProblem:
				std::cout << "\n\nsave failed there is file problem\n\n";
				break;
			}
			_PrintClient(Client1);
		}
		else
			return;
	}
public:

	static void ShowUpdateClientScreen()
	{
		_UpdateClient();
	}

};

