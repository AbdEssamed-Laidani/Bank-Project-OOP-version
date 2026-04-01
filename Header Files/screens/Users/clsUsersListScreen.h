#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "Header Files/screens/clsScreen.h"
#include "Header Files/core/clsUser.h"
class clsUsersListScreen : protected clsScreen
{
private:

	static void _PrintUserCard(clsUser &User)
	{
		std::cout << "\t|" << std::left << std::setw(10) << User.GetUsername()
			<< std::right << " | " << std::left << std::setw(25) << User.GetFullName()
			<< std::right << "| " << std::left << std::setw(15) << User.GetPhone()
			<< std::right << "| " << std::left << std::setw(25) << User.GetEmail()
			<< std::right << "| " << std::left << std::setw(10) << User.GetPassword()
			<< std::right << "| " << std::left << std::setw(15) << User.GetPermistions()
			<< std::right << "|" << std::endl;
	}

	static void _ShowList()
	{
		std::vector <clsUser> vUsers = clsUser::GetUsersList();
		std::string title = "\t     Users List", SubTitle = "\t   (" + std::to_string((int)vUsers.size()) + ") User (s).";
		clsScreen::_DrawHeaderScreen(title, SubTitle);
		std::cout << "\t-----------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t|" << std::left << std::setw(10) << " UserName"
			<< std::right << " |" << std::left << std::setw(25) << " FullName"
			<< std::right << " |" << std::left << std::setw(15) << " Phone"
			<< std::right << " |" << std::left << std::setw(25) << " Email"
			<< std::right << " |" << std::left << std::setw(10) << " Password"
			<< std::right << " |" << std::left << std::setw(15) << " Permissions" 
			<< std::right << " |" << std::endl;
		std::cout << "\t-----------------------------------------------------------------------------------------------------------------" << std::endl;

		for (clsUser& U : vUsers)
		{
			_PrintUserCard(U);
		}
		std::cout << "\t-----------------------------------------------------------------------------------------------------------------" << std::endl;
	}

public:


	static void ShowUsersListScreen()
	{
		_ShowList();
	}


};

