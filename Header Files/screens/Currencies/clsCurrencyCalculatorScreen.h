#pragma once
#include <iostream>
#include <cctype>
#include "Header Files/core/clsCurrency.h"
#include "Header Files/screens/clsScreen.h"
#include "Header Files/lib/clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static void _DrawHeader()
	{
		std::string title = "\tCurrency Calculator Screen";
		_DrawHeaderScreen(title);
	}
	static clsCurrency _FindCurrency(const std::string& message)
	{
		std::string CurrencyCode = clsInputValidate::ReadString(message);
		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			CurrencyCode = clsInputValidate::ReadString("This currency does not exist, r-enter code: ");
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}
	static void _PrintCurrencyData(clsCurrency& Currency)
	{
		std::cout << "Convert From: \n";
		std::cout << "--------------------\n";
		std::cout << "Country  : " << Currency.GetCountry() << std::endl;
		std::cout << "Code     : " << Currency.GetCurrencyCode() << std::endl;
		std::cout << "Name     : " << Currency.GetCurrencyName() << std::endl;
		std::cout << "Rate(1$) : " << Currency.GetRate() << std::endl;
		std::cout << "--------------------\n";
	}
	static float _ReadExchangeAmount()
	{
		return clsInputValidate::ReadPositiveNumber<float>("Enter amount to exchange: ");
	}
	
	static void _PrintExchange(float Amount, const std::string& Currency1Code, const std::string& Currency2Code, float ExchangedAmount)
	{
		std::cout << Amount << " "
			<< Currency1Code << " = "
			<< ExchangedAmount
			<< " " << Currency2Code << std::endl;
	}
	
	static void _ShowCalculatorScreen()
	{
		do
		{
			_ClearScreen();
			_DrawHeader();
			clsCurrency Currency1 = _FindCurrency("Enter currency1 code: ");
			clsCurrency Currency2 = _FindCurrency("Enter currency2 code: ");
			float Amount = _ReadExchangeAmount();
			float ExchangeAmount = Currency1.ConvertToOtherCurrency(Amount, Currency2);
			_PrintCurrencyData(Currency1);
			
			_PrintExchange(Amount, Currency1.GetCurrencyCode(), Currency2.GetCurrencyCode(), ExchangeAmount);
			

		} while (toupper(clsInputValidate::ReadLetter("Do you want to perform another calculation? [Y/N]: ")) == 'Y');

	}


public:
	static void ShowCurrencyCalculatorScreen()
	{
		_ShowCalculatorScreen();
	}

};

