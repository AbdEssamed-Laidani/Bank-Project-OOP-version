#pragma once
#include <iostream>
#include <vector>
#include "Header Files/lib/clsUtil.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include "Header Files/core/clsBankClient.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void PrintClientRecordBalanceLine(clsBankClient& Client)
{
	std::cout << "|" << std::left << std::setw(35) << Client.GetAccountNumber() << std::right << " |" << std::left << std::setw(35) << Client.GetFullName() << std::right << " |" << std::left << std::setw(35) << Client.GetBalance() << std::right << "|" << std::endl;
}
	static void _ShowTotalBalances()
	{
		std::vector <clsBankClient> vClient = clsBankClient::GetClientsList();
		if (vClient.empty())
		{
			std::cout << "\nNot client availabe in the system!\n";
		}
		else
		{
			double total = clsBankClient::GetTotalBalances();
			std::string Title = "\t Total Balances Screen";
			std::string SubTitle = "\t    Client List (" + std::to_string(vClient.size()) + ")\n";
			clsScreen::_DrawHeaderScreen(Title, SubTitle);
			std::cout << "---------------------------------------------------------------------------------------------------------------" << std::endl;
			std::cout << "|" << std::left << std::setw(35) << " Account Number" << std::right << " |" << std::left << std::setw(35) << " Client Name" << std::right << " |" << std::left << std::setw(35) << " Balance" << std::right << "|" << std::endl;
			std::cout << "---------------------------------------------------------------------------------------------------------------" << std::endl;
			for (clsBankClient& C : vClient)
			{
				PrintClientRecordBalanceLine(C);
			}
			std::cout << "---------------------------------------------------------------------------------------------------------------" << std::endl;
			std::cout << "                                             Total Balance = " << total << std::endl;
			std::cout << "                                      (" << clsUtil::numberToWords((int)total) << ")\n\n";
		}
	}


public:
	static void ShowTotalBalances()
	{
		_ShowTotalBalances();
	}

};

