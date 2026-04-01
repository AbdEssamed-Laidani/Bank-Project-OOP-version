#pragma once
#include <iostream>
#include "Header Files/screens/clsScreen.h"
#include "Header Files/lib/clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clstotalBalancesScreen.h"
#include "Header Files/core/clsUser.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionScreen : protected clsScreen
{

private:
	enum enTransactionsMenu { Deposit = 1, Withdraw, TotalBalances, Transfer, TransferLog, MainMenu };
	static short _ReadTransactionMenuOption()
	{
		return clsInputValidate::ReadPositiveNumberInRange<int> ("Choose an option [1-6]: ", 1, 6);
	}
	static void _ClearScreen()
	{
		std::system("cls");
	}
	static void _GoBackToTransactionScreen()
	{
		std::cout << "Press any key to go back to Transaction screen...";
		system("pause>0");
		ShowTransactionScreen();	
	}
	static void _DepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _WithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawSreen();
	}
	static void _TotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLog();
	}
	static void _PerformTransactionMenuOption(enTransactionsMenu TransactionMenuOption)
	{

			switch (TransactionMenuOption)
			{
			case Deposit:
				_ClearScreen();
				_DepositScreen();
				_GoBackToTransactionScreen();
				break;
			case Withdraw:
				_ClearScreen();
				_WithdrawScreen();
				_GoBackToTransactionScreen();
				break;
			case TotalBalances:
				_ClearScreen();
				_TotalBalancesScreen();
				_GoBackToTransactionScreen();
				break;
			case Transfer:
				_ClearScreen();
				clsTransferScreen::ShowTransferScreen();
				_GoBackToTransactionScreen();
				break;
			case TransferLog:
				_ClearScreen();
				_ShowTransferLogScreen();
				_GoBackToTransactionScreen();
				break;
			case MainMenu:
				break;
			default:
				break;
			}
	}
public:

	static void ShowTransactionScreen()
	{
		if (!clsScreen::CheckPermitionRight(clsUser::enPermistions::pList))
			return;

		_ClearScreen();
		clsScreen::_DrawHeaderScreen("\t   Transaction menu");
		std::cout << "\t\t\t\t\t======================================" << std::endl;
		std::cout << "\t\t\t\t\t        Welcome to Bank System       " << std::endl;
		std::cout << "\t\t\t\t\t======================================" << std::endl;
		std::cout << "\t\t\t\t\t[1] Deposit" << std::endl;
		std::cout << "\t\t\t\t\t[2] Withdraw" << std::endl;
		std::cout << "\t\t\t\t\t[3] Total Balances" << std::endl;
		std::cout << "\t\t\t\t\t[4] Transfer" << std::endl;
		std::cout << "\t\t\t\t\t[5] Transfer Logs" << std::endl;
		std::cout << "\t\t\t\t\t[6] Main Menu" << std::endl;
		std::cout << "\t\t\t\t\t======================================" << std::endl;
		std::cout << "\t\t\t\t\t"; _PerformTransactionMenuOption((enTransactionsMenu)_ReadTransactionMenuOption());
	}

};

