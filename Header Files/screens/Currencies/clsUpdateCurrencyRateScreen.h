#pragma once
#include <iostream>
#include "Header Files/core/clsCurrency.h"
#include <cctype>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static void _PrintCurrencyData(clsCurrency& Currency)
	{
		std::cout << "Currency Card:\n\n";
		std::cout << "--------------------\n";
		std::cout << "Country  : " << Currency.GetCountry() << std::endl;
		std::cout << "Code     : " << Currency.GetCurrencyCode() << std::endl;
		std::cout << "Name     : " << Currency.GetCurrencyName() << std::endl;
		std::cout << "Rate(1$) : " << Currency.GetRate() << std::endl;
		std::cout << "--------------------\n";
	}
	static clsCurrency _FindCurrency()
	{
		std::string CurrencyCode = clsInputValidate::ReadString("Enter currency code: ");
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}
	static void _UpdateRate(clsCurrency& Currency)
	{
		std::cout << "\nUpdate currency rate: \n";
		std::cout << "------------------------\n";
		float NewRate = clsInputValidate::ReadPositiveNumber<float>("Enter new rate: ");
		if (Currency.TryUpdateRate(NewRate))
			std::cout << "\nUpdate succeded!\n\n";
		else
			std::cout << "\nUpdate failed, file problem!\n\n";

	}
	static void _UpdateCurrencyRate()
	{
		_DrawHeaderScreen("\tUpdate Currency");
		clsCurrency Currency = _FindCurrency();
		if (!Currency.IsEmpty())
		{
			_PrintCurrencyData(Currency);
			if (toupper(clsInputValidate::ReadLetter("Are you sure? [Y/N]: ")) == 'Y')
				_UpdateRate(Currency);
			else
				return;
		}
		else
		{
			std::cout << "Currency was not fuond!\n";
		}

	}

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		_UpdateCurrencyRate();
	}

};