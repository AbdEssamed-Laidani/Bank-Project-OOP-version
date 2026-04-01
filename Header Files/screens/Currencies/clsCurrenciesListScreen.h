#pragma once
#include <iostream>
#include "Header Files/screens/clsScreen.h"
#include "Header Files/core/clsCurrency.h"
#include <iomanip>
class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyLine(clsCurrency& Currency)
	{
		std::cout << "\t|" << std::left << std::setw(35) << Currency.GetCountry()
			<< std::right << " | " << std::left << std::setw(10) << Currency.GetCurrencyCode()
			<< std::right << "| " << std::left << std::setw(40) << Currency.GetCurrencyName()
			<< std::right << "| " << std::left << std::setw(15) << Currency.GetRate()
			<< std::right << "|" << std::endl;
	}
	static void _DrawHeader(const short CurrenciesSize)
	{
		std::string title = "\tCurrencies List Screen";
		std::string SubTitle = "\t(" + std::to_string(CurrenciesSize) + ") Currency.";
		_DrawHeaderScreen(title, SubTitle);
		std::cout << "\t-------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t|" << std::left << std::setw(35) << " Country" 
			<< std::right << " |" << std::left << std::setw(10) << " Code" 
			<< std::right << " |" << std::left << std::setw(40) << " Name" 
			<< std::right << " |" << std::left << std::setw(15) << " Rate/(1$)" 
			<< std::right << " |" << std::endl;
		std::cout << "\t-------------------------------------------------------------------------------------------------------------" << std::endl;
	}
	static void _ShowCurrenciesListScreen()
	{
		std::vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		_DrawHeader((short)vCurrencies.size());
		for (clsCurrency& C : vCurrencies)
		{
			_PrintCurrencyLine(C);
		}
		std::cout << "\t-------------------------------------------------------------------------------------------------------------" << std::endl;

	}




	public:
	static void ShowCurrenciesListScreen()
	{
		_ShowCurrenciesListScreen();
	}
};

