#pragma once
#include <iostream>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include "Header Files/core/clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
{
private:
	static void _ClearScreen()
	{
		std::system("cls");
	}
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
	static void _WithdrawAmount()
	{
		clsScreen::_DrawHeaderScreen("\t      Withdraw Amount Screen");
		std::string AccountNumber = clsInputValidate::ReadString("Enter account number: ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			while (clsBankClient::IsClientExist(AccountNumber))
			{
				clsScreen::_ClearScreen();
				clsScreen::_DrawHeaderScreen("\t      Withdraw Amount Screen");
				if (toupper(clsInputValidate::ReadLetter("Account number not exist, search again? [Y/N]: ")) == 'Y')
					AccountNumber = clsInputValidate::ReadString("r-enter account number: ");
				else
					return;
			}
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		double Amount = clsInputValidate::ReadPositiveNumber<double>("Enter amount to withdraw: ");
		while (Amount > Client.GetBalance())
		{
			Amount = clsInputValidate::ReadPositiveNumber<double>("It's greater then avalible, enter amount to withdraw: ");
		}
		if (toupper(clsInputValidate::ReadLetter("Are you sure you want to withdraw [" + std::to_string(Amount) + "] from account number [" + AccountNumber + "]? [Y/N]: ")) == 'Y')
		{
			Client.WithDrawAmount(Amount);
			std::cout << "\n\nAmount withdrawed successfully :-)\n\n";
			std::cout << "New balance is: " << Client.GetBalance() << std::endl;
		}
		else
			return;

	}
public:
	static void ShowWithdrawSreen()
	{
		_WithdrawAmount();
	}
};

