#pragma once
#include <iostream>
#include <iomanip>
#include "Header Files/core/clsUser.h"
#include "Global.h"
#include "Header Files/lib/clsDate.h"
class clsScreen
{

protected:
	static void ShowSystemDate()
	{
		clsDate Date;
		
		std::cout << "\t\t\t\t\tDate: " << Date.GetDay() << "/" << Date.GetMonth() << "/" << Date.GetYear() << std::endl;
	}
	static void ShowUserName()
	{
		std::cout << "\t\t\t\t\tUser: " << CurrentUser.GetUsername() << std::endl << std::endl;
	}
	static void _DrawHeaderScreen(const std::string& Title, const std::string& SubTitle = "")
	{
		std::cout << "\t\t\t\t\t--------------------------------------" << std::endl;
		std::cout << "\t\t\t\t\t" << Title << std::endl << std::endl;
		if (!SubTitle.empty())
		std::cout << "\t\t\t\t\t" << SubTitle << std::endl;
		std::cout << "\t\t\t\t\t--------------------------------------" << std::endl << std::endl;
		ShowSystemDate();
		ShowUserName();
	}
	static void _ClearScreen()
	{
		system("cls");
	}

	static bool CheckPermitionRight(clsUser::enPermistions Permistion)
	{
		if (!CurrentUser.CheckAccessPermistion(Permistion))
		{
			_DrawHeaderScreen("Access Denide Contact Your Admin");
			return false;
		}
		else
			return true;
	}
};