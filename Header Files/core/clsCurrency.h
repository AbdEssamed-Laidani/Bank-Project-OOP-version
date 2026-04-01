#pragma once
#include <iostream>
#include "Header Files/lib/clsString.h"
#include "Header Files/lib/clsInputValidate.h"
#include <vector>
#include <fstream>
#include <string>
class clsCurrency
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate;
	enMode _Mode;
	float _ConvertToUSD(float Amount)
	{
		return Amount / GetRate();
	}
	static clsCurrency _ConvertLineToObject(const std::string& Line, const std::string& Delimiter = " #//# ")
	{
		std::vector <std::string> vLine = clsString::SplitText(Line, Delimiter);
		return clsCurrency(enMode::UpdateMode, vLine.at(0), vLine.at(1), vLine.at(2),
			std::stof(vLine.at(3)));
	}
	static clsCurrency _GetEmptyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0.0f);
	}
	static std::vector <clsCurrency> _LoadCurrencyFromFile()
	{
		std::vector <clsCurrency> vCurrencies;
		std::fstream MyFile;
		MyFile.open("Data/Currencies.txt", std::ios::in);
		if (MyFile.is_open())
		{
			std::string Line;
			while (std::getline(MyFile, Line))
			{
				vCurrencies.push_back(_ConvertLineToObject(Line, " #//# "));
			}
		}
		
		MyFile.close();

		return vCurrencies;
	}
	std::string _ConvertObjectToLine(clsCurrency& Object, const std::string Delimiter = " #//# ")
	{
		std::string Line;
		Line += Object.GetCountry() + Delimiter;
		Line += Object.GetCurrencyCode() + Delimiter;
		Line += Object.GetCurrencyName() + Delimiter;
		Line += std::to_string(Object.GetRate());
		return Line;
	}
	bool _TrySaveToFile(std::vector <clsCurrency> &vCurrencies)
	{
		std::fstream MyFile;
		MyFile.open("Data/Currencies.txt", std::ios::out);
		if (MyFile.is_open())
		{
			for (clsCurrency& C : vCurrencies)
			{
				MyFile << _ConvertObjectToLine(C) << std::endl;
			}
			MyFile.close();
			return true;
		}
		MyFile.close();
		return false;

	}
	bool _TryUpdate()
	{
		std::vector <clsCurrency> vCurrencies = _LoadCurrencyFromFile();

		for (clsCurrency& C : vCurrencies)
		{
			if (C.GetCurrencyCode() == GetCurrencyCode())
			{
				C = *this;
				break;
			}
		}
		return _TrySaveToFile(vCurrencies);
	}
public:

	clsCurrency(enMode Mode, const std::string& Country, const std::string& CurrencyCode,
		const std::string& CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	std::string GetCountry() const
	{
		return _Country;
	}
	std::string GetCurrencyCode() const
	{
		return _CurrencyCode;
	}
	std::string GetCurrencyName() const
	{
		return _CurrencyName;
	}
	bool TryUpdateRate(float NewRate)
	{
		_Rate = NewRate;
		return _TryUpdate();
	}
	 float GetRate() const
	{
		return _Rate;
	}

	bool IsEmpty() const
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsCurrency FindByCode(const std::string &CurrencyCode)
	{
		std::fstream MyFile("Data/Currencies.txt", std::ios::in);
		if (MyFile.is_open())
		{
			std::string Line;
			
			while (std::getline(MyFile, Line))
			{
				clsCurrency currency = _ConvertLineToObject(Line, " #//# ");
				if (clsString::UpperAllLetterOfString(currency.GetCurrencyCode()) 
					== clsString::UpperAllLetterOfString(CurrencyCode))	
				{
					MyFile.close();
					return currency;
				}

			}
		}
		
		MyFile.close();
		return _GetEmptyObject();
	}

	static clsCurrency FindByCountry(const std::string &Country)
	{
		std::fstream MyFile("Data/Currencies.txt", std::ios::in);
		if (MyFile.is_open())
		{
			std::string Line;

			while (std::getline(MyFile, Line))
			{
				clsCurrency currency = _ConvertLineToObject(Line, " #//# ");
				if (clsString::UpperAllLetterOfString(currency.GetCountry())
					== clsString::UpperAllLetterOfString(Country))
				{
					MyFile.close();
					return currency;
				}
			}
		}
		
		MyFile.close();
		return _GetEmptyObject();
	}
	static bool isCurrencyExist(const std::string& CurrencyCode)
	{
		clsCurrency currency = FindByCode(CurrencyCode);
		return !currency.IsEmpty();
	}
	static std::vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyFromFile();
	}

    

    float ConvertToOtherCurrency(float Amount,const clsCurrency &Currency2)
	{
		float AmountInUSD = _ConvertToUSD(Amount);
		if (Currency2.GetCurrencyCode() == "USD")
		{
			return AmountInUSD;
		}
		return AmountInUSD * Currency2.GetRate();
	}

};

