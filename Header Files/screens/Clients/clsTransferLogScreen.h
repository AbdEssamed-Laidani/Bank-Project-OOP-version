#pragma once
#include <iostream>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/core/clsBankClient.h"
#include <iomanip>
#include "Header Files/screens/clsScreen.h"

class clsTransferLogScreen:protected clsScreen
{
private:
	static void _PrintTransfersLog(clsBankClient::stTransferLog& TransferLog)
	{
		std::cout << "\t" << "| " << std::left << std::setw(30) << TransferLog.TransferDate << std::right
			<< "| " << std::left << std::setw(20) << TransferLog.sourceAccNumber << std::right
			<< "| " << std::left << std::setw(20) << TransferLog.ReciverAccNumber << std::right
			<< "| " << std::left << std::setw(20) << TransferLog.TransferAmount << std::right
			<< "| " << std::left << std::setw(20) << TransferLog.sourceBalance << std::right
			<< "| " << std::left << std::setw(20) << TransferLog.ReciverBalance << std::right
			<< "| " << std::left << std::setw(20) << TransferLog.UserName << std::right
			<< "| " << std::endl;
	}

	static void _ShowTransferLog()
	{

		std::vector <clsBankClient::stTransferLog> vTransfers = clsBankClient::GetTransfersLogList();
		std::string Title = "\tTransfers Log List Screen";
		std::string Subtitle = "\t     (" + std::to_string(vTransfers.size()) + ") Record(s).";
		clsScreen::_DrawHeaderScreen(Title, Subtitle);
		std::cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout 
			<< "\t|" << std::left << std::setw(30) << " Date & Time" << std::right 
			<< " |" << std::left << std::setw(20) << " s.Acc Number" << std::right 
			<< " |" << std::left << std::setw(20) << " d.Acc Number" << std::right 
			<< " |" << std::left << std::setw(20) << " Transfer Amount" << std::right 
			<< " |" << std::left << std::setw(20) << " s.Balance" << std::right 
			<< " |" << std::left << std::setw(20) << " d.Balance" << std::right 
			<< " |" << std::left << std::setw(20) << " User" << std::right 
			<< " |" << std::endl;
		std::cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

		for (clsBankClient::stTransferLog& i : vTransfers)
		{
			_PrintTransfersLog(i);
		}
		std::cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

	}

public:

	static void ShowTransferLog()
	{
		_ShowTransferLog();
	}

};

