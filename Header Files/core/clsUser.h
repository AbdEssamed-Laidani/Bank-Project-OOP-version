#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/core/clsPerson.h"
#include "Header Files/lib/clsString.h"
#include "Header Files/lib/clsDate.h"
#include "Header Files/lib/clsUtil.h"
class clsUser : public clsPerson
{
public:
	struct stLoginRegister
	{
		std::string RegisterDate;
		std::string Username;
		std::string Passowrd;
		int Permisstion = 0;
	};

private:
	enum enMode { EmptyMode = 0, UpdateMode, AddNewMode };
	enMode _Mode;
	std::string _UserName;
	std::string _Password;
	bool _MarkedForDeleted = false;
	int _Permisstions;
	
	static stLoginRegister _ConvertLoginLineToRegister(const std::string& Line, const std::string& Delimiter)
	{
		stLoginRegister _LoginRegister;
		std::vector <std::string> vRegister = clsString::SplitText(Line, Delimiter);
		_LoginRegister.RegisterDate = vRegister.at(0);
		_LoginRegister.Username = vRegister.at(1);
		_LoginRegister.Passowrd = clsUtil::DecryptionText(vRegister.at(2), 2);
		_LoginRegister.Permisstion = std::stoi(vRegister.at(3));
		return _LoginRegister;
	}
	
	static std::vector <stLoginRegister> _LoadUsersLoginRegister()
	{
		std::vector <stLoginRegister> vLogs;
		std::fstream LoginFile;
		LoginFile.open("Data/Logs.txt", std::ios::in);
		if (LoginFile.is_open())
		{
			std::string RegisterLine;
			while (std::getline(LoginFile, RegisterLine))
			{
				vLogs.push_back(_ConvertLoginLineToRegister(RegisterLine, " #//# "));
			}
		}
		LoginFile.close();
		
		return vLogs;
	}
	std::string _PrepareLoginRegisterRecord(std::string Delimiter = " #//# ")
	{
		std::string record;
		record += clsDate::GetSystemDateString() + Delimiter;
		record += _UserName + Delimiter;
		record += clsUtil::EncryptionText(GetPassword(), 2) + Delimiter;
		record += std::to_string(_Permisstions);
		return record;
	}
	
	static clsUser _ConvertLineToUserObject(const std::string &Line,const std::string &Delimiter)
	{
		std::vector <std::string> vUser;
		vUser = clsString::SplitText(Line, Delimiter);
		return clsUser(enMode::UpdateMode, vUser.at(0), vUser.at(1), vUser.at(2), vUser.at(3),
			vUser.at(4), clsUtil::DecryptionText(vUser.at(5), 2), stoi(vUser.at(6)));
	}
    static std::string _ConvertUserObjectToLine(clsUser& User,const std::string &Delimiter)
	{
		std::string Record;
		Record += User.GetFirstName() + Delimiter;
		Record += User.GetLastName() + Delimiter;
		Record += User.GetEmail() + Delimiter;
		Record += User.GetPhone() + Delimiter;
		Record += User.GetUsername() + Delimiter;
		Record += clsUtil::EncryptionText(User.GetPassword(), 2) +Delimiter;
		Record += std::to_string(User.GetPermistions());
		return Record;
	}
	static std::vector <clsUser> _LoadUserDataFromFile()
	{
		std::fstream MyFile;
		std::vector <clsUser> vUsers;
		MyFile.open("Data/Users.txt", std::ios::in);
		if (MyFile.is_open())
		{
			std::string Line;
			while (std::getline(MyFile, Line))
			{
				vUsers.push_back(_ConvertLineToUserObject(Line, " #//# "));
			}
		}
		MyFile.close();

		return vUsers;
	}
	static clsUser _GetEmptyObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	bool _SaveUsersDataToFile(std::vector <clsUser>& vUsers)
	{
		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::out);
		if (MyFile.is_open())
		{
			for (clsUser& U : vUsers)
			{
				if (!U.MarkedForDeleted())
					MyFile << _ConvertUserObjectToLine(U, " #//# ") << std::endl;
			}
			MyFile.close();
			return true;
		}
		MyFile.close();

		return false;

	}
	bool _TryUpdate()
	{
		std::vector <clsUser> vUsers = _LoadUserDataFromFile();
		for (clsUser& U : vUsers)
		{
			if (GetUsername() == U.GetUsername())
			{
				U = *this;
				break;
			}
		}
		return _SaveUsersDataToFile(vUsers);
	}
	bool _TryAddUserToFile(const std::string& UserDataLine)
	{
		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::app);
		if (MyFile.is_open())
		{
			MyFile << UserDataLine << std::endl;
			return true;
		}
		MyFile.close();
		return false;
	}
	bool _AddNewUser()
	{
		return _TryAddUserToFile(_ConvertUserObjectToLine(*this, " #//# "));
	}
		
public:

	enum enPermistions {
		All = -1, pList = 1, pAdd = 2,
		pDelete = 4, pUpdate = 8, pFind = 16,
		pTransactions = 32, pManage = 64, pLoginRegister = 128
	};



	clsUser(enMode Mode, const std::string& FirstName, const std::string& LastName,
		const std::string& Email, const std::string& Phone,const std::string &UserName,
		const std::string &Password, int Permisstions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permisstions = Permisstions;
	}
	bool MarkedForDeleted()
	{
		return _MarkedForDeleted;
	}
	void SetMakedForDeleted(bool Delete)
	{
		_MarkedForDeleted = Delete;
	}
	std::string GetUsername()
	{
		return _UserName;
	}
	void SetUserName(const std::string& UserName)
	{
		_UserName = UserName;
	}
	std::string GetPassword()
	{
		return _Password;
	}
	void SetPassword(const std::string& Password)
	{
		_Password = Password;
	}
	int GetPermistions()
	{
		return _Permisstions;
	}
	void SetPermisstion(int Permisstions)
	{
		_Permisstions = Permisstions;
	}
	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}
	bool Delete()
	{
		std::vector <clsUser> vUsers = _LoadUserDataFromFile();
		for (clsUser& U : vUsers)
		{
			if (U.GetUsername() == _UserName)
			{
				U.SetMakedForDeleted(true);
				break;
			}
		}
		*this = _GetEmptyObject();
		_SaveUsersDataToFile(vUsers);
		return true;
	}
	static clsUser Find(std::string UserName)
	{
		std::fstream MyFile("Data/Users.txt", std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			while (std::getline(MyFile, Line))
			{
				clsUser user = _ConvertLineToUserObject(Line, " #//# ");
				if (user.GetUsername() == UserName)
				{
					MyFile.close();
					return user;
				}
			}
		}
		MyFile.close();
		return _GetEmptyObject();
	}
	static clsUser Find(const std::string& UserName,const std::string& Password)
	{
		std::fstream MyFile("Data/Users.txt", std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;
			while (std::getline(MyFile, Line))
			{
				clsUser user = _ConvertLineToUserObject(Line, " #//# ");
				if (user.GetUsername() == UserName && user.GetPassword() == Password)
				{
					MyFile.close();
					return user;
				}
			}
		}
		MyFile.close();
		return _GetEmptyObject();
	}
	static bool isUserExist(const std::string& UserName)
	{
		clsUser User = Find(UserName);
		return !User.isEmpty();
	}
	static std::vector <clsUser> GetUsersList()
	{
		return _LoadUserDataFromFile();
	}
	static clsUser GetAddNewUserObject(const std::string &UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}
	enum enSaveResult { svSucceded = 1, svFailedEmpty, svFailedExist,svFailedFileProblem };
    enSaveResult save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (isEmpty())
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
			if (isUserExist(GetUsername()))
				return enSaveResult::svFailedExist;
			else
			{
				if (_AddNewUser())
				{
					_Mode = UpdateMode;
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

	bool CheckAccessPermistion(enPermistions Permistion)
	{
		if (((this->_Permisstions & Permistion) == Permistion) || (Permistion == enPermistions::All))
			return true;
		else
			return false;
	}
	bool TrySaveRegisterLogin()
	{
		std::string record = _PrepareLoginRegisterRecord();
		std::fstream MyFile;
		MyFile.open("Data/Logs.txt", std::ios::app);
		if (MyFile.is_open())
		{
			MyFile << record << std::endl;
			MyFile.close();
			return true;
		}
		MyFile.close();
		return false;
	}

	static std::vector <stLoginRegister> GetUserLoginRegisterList()
	{
		return _LoadUsersLoginRegister();
	}


};