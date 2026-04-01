#pragma once
#include <iostream>
#include "Header Files/core/clsBankClient.h"
#include "Header Files/screens/clsScreen.h"
#include <iomanip>
#include <vector>
#include <string>
class clsClientListScreen : protected clsScreen
{
private:
	static void PrintClientDataLine(clsBankClient& ClientData)
	{
		std::cout << "\t" << "| " << std::left << std::setw(15) << ClientData.GetAccountNumber() << std::right << "| " << std::left << std::setw(25) << ClientData.GetFullName() << std::right << "| " << std::left << std::setw(15) << ClientData.GetPhone() << std::right << "| " << std::left << std::setw(30) << ClientData.GetEmail() << std::right << "| " << std::left << std::setw(14) << ClientData.GetPinCode() << std::right << " |" << std::left << std::setw(15) << ClientData.GetBalance() << std::right << "|" << std::endl;

	}

public:

	static void ShowClientList()
	{
		if(!clsScreen::CheckPermitionRight(clsUser::enPermistions::pList))
			return;

		std::vector <clsBankClient> vClient = clsBankClient::GetClientsList();
		std::string title = "\t     Client List", SubTitle = "\t   (" + std::to_string((int)vClient.size()) + ") Client(s).";
		clsScreen::_DrawHeaderScreen(title, SubTitle);
		std::cout << "\t-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t|" << std::left << std::setw(15) << " Account Number" << std::right << " |" << std::left << std::setw(25) << " Client Name" << std::right << " |" << std::left << std::setw(15) << " Phone" << std::right << " |" << std::left << std::setw(30) << " Email" << std::right << " |" << std::left << std::setw(15) << " Pin code" << std::right << " |" << std::left << std::setw(15) << " Balance" << std::right << "|" << std::endl;
		std::cout << "\t-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		for (clsBankClient& C : vClient)
		{
			PrintClientDataLine(C);
		}
		std::cout << "\t-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
};

