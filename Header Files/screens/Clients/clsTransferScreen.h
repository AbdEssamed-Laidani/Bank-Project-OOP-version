#pragma once
#include <iostream>
#include <string>
#include "Header Files/screens/clsScreen.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/core/clsBankClient.h"

#include <cctype>
class clsTransferScreen: protected clsScreen
{
private:

	static std::string GetValidAccountNumber(const std::string &message)
	{
		std::string AccountNumber = clsInputValidate::ReadString(message);
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			clsScreen::_ClearScreen();
			clsScreen::_DrawHeaderScreen("\t   Transfer Screen");
			AccountNumber = clsInputValidate::ReadString("Account number not exist, r-enter account number: ");
		}
		return AccountNumber;
	}
	static double _GetValidAmount(clsBankClient& Client, const std::string& message)
	{
		double amount = 0.0;
		double CurrentBalance = Client.GetBalance();
		amount = clsInputValidate::ReadPositiveNumber<double>(message);
		while (amount > CurrentBalance || amount <= 0)
		{
			clsScreen::_ClearScreen();
			clsScreen::_DrawHeaderScreen("\t   Transfer Screen");
			if (amount > CurrentBalance)
				amount = clsInputValidate::ReadPositiveNumber<double>("This amount is greater than available, r-enter amount: ");
			else
				amount = clsInputValidate::ReadPositiveNumber<double>("Enter valid amount to transfer : ");

		} 
		return amount;
		
	}
	static void _TransferValidAmount(clsBankClient& ClientTransferFrom, clsBankClient& ClientTransferTo)
	{
		double AmountToTransfer = _GetValidAmount(ClientTransferFrom, "Enter valid amount to transfer: ");
		if (toupper(clsInputValidate::ReadLetter("Are you sure? [Y/N]: ")) == 'Y')
		{
			if (ClientTransferFrom.TransferAmount(AmountToTransfer, ClientTransferTo))
			{
				_ShowSuccessScreen(ClientTransferFrom, ClientTransferTo);
			}
			else
			{
				std::cout << "\nTransfer failed.\n";
			}
		}
	}
	static void _PrintClientCard(clsBankClient &Client)
	{
		std::cout << "client card: " << std::endl;
		std::cout << "------------------\n";
		std::cout << "Full Name: " << Client.GetFullName() << std::endl;
		std::cout << "Acc. Number: " << Client.GetAccountNumber() << std::endl;
		std::cout << "Balance: " << Client.GetBalance() << std::endl;
		std::cout << "------------------\n";
	}
	static void _ShowSuccessScreen(clsBankClient& ClientTransferFrom, clsBankClient& ClientTransferTo)
	{
		clsScreen::_ClearScreen();
		clsScreen::_DrawHeaderScreen("\t   Transfer Screen");
		std::cout << "Transfer successded!\n";
		_PrintClientCard(ClientTransferFrom);
		std::cout << std::endl << std::endl;
		_PrintClientCard(ClientTransferTo);
	}
	static void _Transfer()
	{
		clsScreen::_ClearScreen();
		clsScreen::_DrawHeaderScreen("\t   Transfer Screen");
		std::string AccountTransferFrom;
		std::string AccountTransferTo;
		AccountTransferFrom = GetValidAccountNumber("Enter account number to transfer from: ");
		clsBankClient ClientTransferFrom = clsBankClient::Find(AccountTransferFrom);
		_PrintClientCard(ClientTransferFrom);
		AccountTransferTo = GetValidAccountNumber("Enter account number to transfer to: ");

		while (AccountTransferFrom == AccountTransferTo) 
		{
			AccountTransferTo = GetValidAccountNumber("Cannot transfer to the same account. Enter another: ");
		}
		clsBankClient ClientTransferTo = clsBankClient::Find(AccountTransferTo);
		_PrintClientCard(ClientTransferTo);
		_TransferValidAmount(ClientTransferFrom, ClientTransferTo);
	}

public:

	static void ShowTransferScreen()
	{
		_Transfer();
	}


};

