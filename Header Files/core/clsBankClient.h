#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Header Files/lib/clsString.h"
#include "Header Files/core/clsPerson.h"
#include "Header Files/core/clsUser.h"
#include "Global.h"
class clsBankClient :public clsPerson
{


public:

	struct stTransferLog
	{
		double sourceBalance = 0.0f;
		double ReciverBalance = 0.0f;
		double TransferAmount = 0.0f;
		std::string TransferDate;
		std::string sourceAccNumber;
		std::string ReciverAccNumber;
		std::string UserName;
	};

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	std::string _AccountNumber;
	std::string _PinCode;
	double _Balance;
	bool _MarkForDelete = false;

	static stTransferLog _ConvertTransferLineToLog(const std::string& Line, const std::string& Delimiter = " #//# ")
	{
		stTransferLog _TransferLog;
		std::vector <std::string> vLog = clsString::SplitText(Line, Delimiter);
		_TransferLog.TransferDate = vLog.at(0);
		_TransferLog.sourceAccNumber = vLog.at(1);
		_TransferLog.ReciverAccNumber = vLog.at(2);
		_TransferLog.TransferAmount = std::stod(vLog.at(3));
		_TransferLog.sourceBalance = std::stod(vLog.at(4));
		_TransferLog.ReciverBalance = std::stod(vLog.at(5));
		_TransferLog.UserName = vLog.at(6);
		return _TransferLog;
	}
	static std::vector <stTransferLog> _LoadTransfersLog()
	{
		std::vector <stTransferLog> vLogs;
		std::fstream TransfersLogFile;
		TransfersLogFile.open("Data/TransferLogs.txt", std::ios::in);
		if (TransfersLogFile.is_open())
		{
			std::string TransfersLine;
			while (std::getline(TransfersLogFile, TransfersLine))
			{
				vLogs.push_back(_ConvertTransferLineToLog(TransfersLine, " #//# "));
			}
			TransfersLogFile.close();
		}
		
		return vLogs;
	}


	 std::string _PrepareTransferLogsToRecord(double Amount, clsBankClient& ClientTransferTo, const std::string& Delimiter = " #//# ")
	{
		std::string record;
		record += clsDate::GetSystemDateString() + Delimiter;
		record += _AccountNumber + Delimiter;
		record += ClientTransferTo.GetAccountNumber() + Delimiter;
		record += std::to_string(Amount) + Delimiter;
		record += std::to_string(_Balance) + Delimiter;
		record += std::to_string(ClientTransferTo.GetBalance()) + Delimiter;
		record += CurrentUser.GetUsername();
		return record;
	}
	 void _TransferRegister(double Amount, clsBankClient& ClientTransferTo)
	 {
		 std::string record = _PrepareTransferLogsToRecord(Amount, ClientTransferTo);
		 std::fstream MyFile;
		 MyFile.open("Data/TransferLogs.txt", std::ios::app);
		 if (MyFile.is_open())
		 {
			 MyFile << record << std::endl;
			 MyFile.close();
		 }
		 MyFile.close();
	 }
	static clsBankClient _ConvertLineToClientObject(const std::string &Line,std::string Delimiter = " #//# ")
	{
		std::vector <std::string> vClient = clsString::SplitText(Line, Delimiter);
		return clsBankClient(enMode::UpdateMode, vClient.at(0), vClient.at(1), vClient.at(2),
			vClient.at(3), vClient.at(4), vClient.at(5), stod(vClient.at(6)));
	}
	static clsBankClient _GetEmptyClientObejct()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static std::vector <clsBankClient> _LoadDataFromFile()
	{
		std::string DataLine = "";
		std::vector <clsBankClient> vClient;
		std::fstream MyFile("Data/Client.txt", std::ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, DataLine))
			{
				vClient.push_back(_ConvertLineToClientObject(DataLine));
			}
			MyFile.close();
		}
		MyFile.close();
		return vClient;
	}
	std::string _ConvertObjectToLine(clsBankClient& Client, std::string Delimiter = " #//# ")
	{
		std::string Line = "";
		Line += Client.GetFirstName() + Delimiter;
		Line += Client.GetLastName() + Delimiter;
		Line += Client.GetPhone() + Delimiter;
		Line += Client.GetEmail() + Delimiter;
		Line += Client.GetAccountNumber() + Delimiter;
		Line += Client.GetPinCode() + Delimiter;
		Line += std::to_string(Client.GetBalance());
		return Line;
	}
	bool _TrySaveVectorToFile(std::vector <clsBankClient> &vClient)
	{
		std::fstream MyFile("Data/Client.txt", std::ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClient)
			{
				if(!C._MarkForDelete)
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
		std::vector <clsBankClient> vClient = _LoadDataFromFile();
		for (clsBankClient& C : vClient)
		{
			if (GetAccountNumber() == C.GetAccountNumber())
			{
				C = *this;
				break;
			}
		}
		return _TrySaveVectorToFile(vClient);
	}
	bool _AddLineToFile(const std::string &Line)
	{
		std::fstream MyFile("Data/Client.txt", std::ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << std::endl;
			MyFile.close();
			return true;

		}
		MyFile.close();
		return false;
	}
	bool _TryAddNew()
	{
		return _AddLineToFile(_ConvertObjectToLine(*this));
	}
public:
	clsBankClient(enMode Mode, const std::string& FirstName, const std::string& LastName, const std::string& Phone, const std::string& Email, const std::string& AccountNumber, const std::string& PinCode, const double& Balance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_AccountNumber = AccountNumber;
		_Balance = Balance;
		_PinCode = PinCode;
		_Mode = Mode;
	}
	std::string GetAccountNumber()
	{
		return _AccountNumber;
	}
	void SetBalance(const double& Balance)
	{
		_Balance = Balance;
	}
	double GetBalance()
	{
		return _Balance;
	}
	void SetPinCode(const std::string& PinCode)
	{
		_PinCode = PinCode;
	}
	std::string GetPinCode()
	{
		return _PinCode;
	}
	std::string GetFullName()
	{
		return GetFirstName() + " " + GetLastName();
	}
	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient Find(const std::string &AccountNumber)
	{
		std::vector <clsBankClient> vClient;
		std::string Line;
		std::fstream MyFile("Data/Client.txt", std::ios::in);
		while (getline(MyFile, Line))
		{
			clsBankClient Client = _ConvertLineToClientObject(Line);
			if (Client.GetAccountNumber() == AccountNumber)
			{
				MyFile.close();
				return Client;
			}
			vClient.push_back(Client);
		}
		MyFile.close();

		return _GetEmptyClientObejct();
	}
	static clsBankClient Find(const std::string& AccountNumber, const std::string& PinCode)
	{
		std::vector <clsBankClient> vClient;
		std::string Line;
		std::fstream MyFile("Data/Client.txt", std::ios::in);
		while (getline(MyFile, Line))
		{
			clsBankClient Client = _ConvertLineToClientObject(Line);
			if (Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
			{
				return Client;
			}
			vClient.push_back(Client);
		}
		MyFile.close();
		return _GetEmptyClientObejct();
	}
	static bool IsClientExist(const std::string &AccountNumber)
	{
		clsBankClient client = client.Find(AccountNumber);
		return !client.isEmpty();
	}
	
	static clsBankClient GetNewClientObject(std::string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	enum enSaveResult { svFailedEmpty = 0, svSucceded = 1, svFailedExist = 3, svFailedFileProblem = 4 };

	enSaveResult save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if(isEmpty())
			return enSaveResult::svFailedEmpty;
			break;
		case enMode::UpdateMode:

			if (_TryUpdate())
			{
				return enSaveResult::svSucceded;
			}
			else
				return enSaveResult::svFailedFileProblem;
			break;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResult::svFailedExist;
			else
			{
				if (_TryAddNew())
				{
					_Mode = enMode::UpdateMode;
					return enSaveResult::svSucceded;
				}
				else
					return enSaveResult::svFailedFileProblem;
			}
			break;
		default:
			break;
		}
		return enSaveResult::svFailedEmpty;
	}
	bool Delete(const std::string &AccountNumbeer)
	{
		std::vector <clsBankClient> vClient = _LoadDataFromFile();
		for (clsBankClient& C : vClient)
		{
			if (C.GetAccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		*this = _GetEmptyClientObejct();
		_TrySaveVectorToFile(vClient);
		return true;
	}
	static std::vector <clsBankClient> GetClientsList()
	{
		return _LoadDataFromFile();
	}

	static double GetTotalBalances()
	{
		std::vector <clsBankClient> vClient = _LoadDataFromFile();

		double total = 0;
		for (clsBankClient& i : vClient)
		{
			total = total + i.GetBalance();
		}
		return total;
	}
    void DepositAmount(double Amount)
	{
		_Balance += Amount;
		save();
	}
	void WithDrawAmount(double Amount)
	{
		DepositAmount(-1 * Amount);
	}
	

	bool TransferAmount(double Amount, clsBankClient& ClientTransferTo)
	{
		if (Amount > _Balance)
		{
			return false;
		}
		WithDrawAmount(Amount);
		ClientTransferTo.DepositAmount(Amount);
		_TransferRegister(Amount, ClientTransferTo);
		return true;

	}

	static std::vector <stTransferLog> GetTransfersLogList()
	{
		return _LoadTransfersLog();
	}

	
};

