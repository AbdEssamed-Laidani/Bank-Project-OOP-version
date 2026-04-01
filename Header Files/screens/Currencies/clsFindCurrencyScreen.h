#pragma once
#include <iostream>
#include "Header Files/core/clsCurrency.h"
#include "Header Files/lib/clsInputValidate.h"
#include <cctype>
#include "Header Files/screens/clsScreen.h"
class clsFindCurrencyScreen: protected clsScreen
{
private:
	enum enSeachMethod { ByCode = 1, ByCountry };
	static void _PrintCurrencyData(clsCurrency &Currency)
	{
		std::cout << "Currency Card:\n\n";
		std::cout << "--------------------\n";
		std::cout << "Country  : " << Currency.GetCountry() << std::endl;
		std::cout << "Code     : " << Currency.GetCurrencyCode() << std::endl;
		std::cout << "Name     : " << Currency.GetCurrencyName() << std::endl;
		std::cout << "Rate(1$) : " << Currency.GetRate() << std::endl;
		std::cout << "--------------------\n";
	}
	static void _FindByCode()
	{
		std::string CurrencyCode = clsInputValidate::ReadString("Enter currency code: ");
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		if (!Currency.IsEmpty())
		{
			std::cout << "Currency found!\n";
			_PrintCurrencyData(Currency);
		}
		else
			std::cout << "Currency not found!\n";
	}
	static void _DrawHeader()
	{
		std::string title = "\tFind Currency Screen";
		_DrawHeaderScreen(title);
	}
	static void _FindByCountry()
	{

		std::string CountryName = clsInputValidate::ReadString("Enter country name: ");
		clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
		if (!Currency.IsEmpty())
		{
			std::cout << "Currency found!\n";
			_PrintCurrencyData(Currency);
		}
		else
			std::cout << "Currency not found!\n";
	}
	static void _FindCurrency()
	{
		_DrawHeader();
		enSeachMethod SearchMethod = (enSeachMethod)clsInputValidate::ReadPositiveNumberInRange<int>("Find by: [1] Code, [2] Country: ", 1, 2);
		switch (SearchMethod)
		{
		case enSeachMethod::ByCode:
			_FindByCode();
			break;
		case enSeachMethod::ByCountry:
			_FindByCountry();
				break;
		}

	}

public:


	static void ShowFindCurrencyScreen()
	{
		_FindCurrency();
	}


};

