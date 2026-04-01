#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/Clients/clsClientListScreen.h"
#include "Header Files/screens/Clients/clsAddClientScreen.h"
#include "Header Files/screens/Clients/clsDeleteClientScreen.h"
#include "Header Files/screens/Clients/clsUpdateClientScreen.h"
#include "Header Files/screens/Clients/clsFindClientScreen.h"
#include "Header Files/screens/Clients/clsTransactionScreen.h"
#include "Header Files/screens/Users/clsUserManageScreen.h"
#include "Global.h"
#include "Header Files/screens/Users/clsLoginRegister.h"
#include "Header Files/screens/Currencies/clsCurrencyExchangeScreen.h"
class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOptions {
		enShowClientList = 1,
		enAddNewClient = 2,
		enDeleteClient = 3,
		enUpdateClientInfo = 4,
		enFindClient = 5,
		enTransaction = 6,
		enManageUsers = 7,
		enLoginRegister = 8,
		enCurrencyExchange = 9,
		enLogout = 10
	};
	static void _ClearScreen()
	{
		std::system("cls");
	}
	static void _GoBackToMainScreen()
	{
		std::cout << "Press any key to go back to main screen...";
		system("pause>0");
		ShowMainScreen();
	}
	static void _ShowClientListScreen()
	{
		clsClientListScreen::ShowClientList();
	}
	static void _AddNewClientScreen()
	{
		clsAddClientScreen::ShowAddClientScreen();
	}
	static void _DeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _UpdateClientInfoScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _FindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _TransactionScreen()
	{
		clsTransactionScreen::ShowTransactionScreen();
	}
	static void _ManageUsersScreen()
	{
		clsUserManageScreen::ShowManageUserScreen();
	}
	static void _ShowLoginRegister()
	{
		clsLoginRegister::ShowLoginRegister();
	}
	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowExchangeMenu();
	}
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}
	static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
	{

		switch (MainMenuOption)
		{
		case enShowClientList:
			_ClearScreen();
			_ShowClientListScreen();
			_GoBackToMainScreen();
			break;
		case enAddNewClient:
			_ClearScreen();
			_AddNewClientScreen();
			_GoBackToMainScreen();
			break;
		case enDeleteClient:
			_ClearScreen();
			_DeleteClientScreen();
			_GoBackToMainScreen();
			break;
		case enUpdateClientInfo:
			_ClearScreen();
			_UpdateClientInfoScreen();
			_GoBackToMainScreen();
			break;
		case enFindClient:
			_ClearScreen();
			_FindClientScreen();
			_GoBackToMainScreen();
			break;
		case enTransaction:
			_ClearScreen();
			_TransactionScreen();
			_GoBackToMainScreen();
			break;
		case enManageUsers:
			_ClearScreen();
			_ManageUsersScreen();
			_GoBackToMainScreen();
			break;
		case enLoginRegister:
			_ClearScreen();
			_ShowLoginRegister();
			_GoBackToMainScreen();
			break;
		case enCurrencyExchange:
			_ClearScreen();
			_ShowCurrencyExchangeScreen();
			_GoBackToMainScreen();
			break;
		case enLogout:
			_ClearScreen();
			_Logout();
			break;
		default:
			break;
		}
	}
	static short _ReadMainMenuOption()
	{
		return clsInputValidate::ReadPositiveNumberInRange<int>("Choose an option [1-10]: ", 1, 10);
	}
	public:
		static void ShowMainScreen()
		{
			_ClearScreen();
			clsScreen::_DrawHeaderScreen("\t       Main Menu");
			std::cout << "\t\t\t\t\tHello, " << CurrentUser.GetFullName() << std::endl << std::endl;
			std::cout << "\t\t\t\t\t======================================" << std::endl;
			std::cout << "\t\t\t\t\t        Welcome to Bank System       " << std::endl;
			std::cout << "\t\t\t\t\t======================================" << std::endl;
			std::cout << "\t\t\t\t\t[1] Show Client List" << std::endl;
			std::cout << "\t\t\t\t\t[2] Add New Client" << std::endl;
			std::cout << "\t\t\t\t\t[3] Delete Client" << std::endl;
			std::cout << "\t\t\t\t\t[4] Update Client Info" << std::endl;
			std::cout << "\t\t\t\t\t[5] Find Client" << std::endl;
			std::cout << "\t\t\t\t\t[6] Transaction" << std::endl;
			std::cout << "\t\t\t\t\t[7] Manage Users" << std::endl;
			std::cout << "\t\t\t\t\t[8] Login Register" << std::endl;
			std::cout << "\t\t\t\t\t[9] Currency Exchange" << std::endl;
			std::cout << "\t\t\t\t\t[10] Logout" << std::endl;
			std::cout << "\t\t\t\t\t======================================" << std::endl;
			std::cout << "\t\t\t\t\t"; _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
		}
};

