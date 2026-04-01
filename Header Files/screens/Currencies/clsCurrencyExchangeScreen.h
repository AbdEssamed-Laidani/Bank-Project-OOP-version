#pragma once
#include <iostream>
#include <string>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeMenu
	{
		List = 1,
		Find = 2,
		Update = 3,
		CurrencyCalculator = 4,
		MainMenu = 5
	};
	static void _GoBackToMenuScreen()
	{
		std::cout << "Press any key to go back to menu screen...";
		system("pause>0");
		ShowExchangeMenu();
	}
	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}
	static void _PerformCurrencyExchangeMenu(enCurrencyExchangeMenu Option)
	{
		switch (Option)
		{
		case enCurrencyExchangeMenu::List:
			clsScreen::_ClearScreen();
			_ShowCurrenciesListScreen();
			_GoBackToMenuScreen();
			break;
		case enCurrencyExchangeMenu::Find:
			clsScreen::_ClearScreen();
			_ShowFindCurrencyScreen();
			_GoBackToMenuScreen();
			break;
		case enCurrencyExchangeMenu::Update:
			clsScreen::_ClearScreen();
			_ShowUpdateRateScreen();
			_GoBackToMenuScreen();
			break;
		case enCurrencyExchangeMenu::CurrencyCalculator:
			clsScreen::_ClearScreen();
			_ShowCurrencyCalculatorScreen();
			_GoBackToMenuScreen();
			break;
		case enCurrencyExchangeMenu::MainMenu:
			break;
		default:
			break;
		}
	}
	static int ReadMenuOption()
	{
		return clsInputValidate::ReadPositiveNumberInRange<int>("Choose an option [1-5]: ", 1, 5);
	}
public:

	static void ShowExchangeMenu()
	{
		_ClearScreen();
		clsScreen::_DrawHeaderScreen("\tCurrency Exchange Main Screen");
		std::cout << "\t\t\t\t\t======================================" << std::endl;
		std::cout << "\t\t\t\t\t        Currency Exchange Menu       " << std::endl;
		std::cout << "\t\t\t\t\t======================================" << std::endl;
		std::cout << "\t\t\t\t\t[1] List Currencies" << std::endl;
		std::cout << "\t\t\t\t\t[2] Find Currency" << std::endl;
		std::cout << "\t\t\t\t\t[3] Update Rate" << std::endl;
		std::cout << "\t\t\t\t\t[4] Curreny Calculator" << std::endl;
		std::cout << "\t\t\t\t\t[5] Main Menu" << std::endl;
		std::cout << "\t\t\t\t\t======================================" << std::endl;
		std::cout << "\t\t\t\t\t";_PerformCurrencyExchangeMenu((enCurrencyExchangeMenu)ReadMenuOption());

	}



};

