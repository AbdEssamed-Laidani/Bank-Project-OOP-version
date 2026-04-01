#pragma once
#include <iostream>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/core/clsUser.h"
#include "Header Files/screens/clsScreen.h"
class clsLoginRegister : protected clsScreen
{
private:

	static void _PrintLoginRegister(clsUser::stLoginRegister &LoginRegister)
	{
		std::cout << "\t" << "| " << std::left << std::setw(30) << LoginRegister.RegisterDate << std::right << "| " << std::left << std::setw(20) << LoginRegister.Username << std::right << "| " << std::left << std::setw(20) << LoginRegister.Passowrd << std::right << "| " << std::left << std::setw(20) << LoginRegister.Permisstion << std::right << "|" << std::endl;

	}
	static void _ShowLoginRegister()
	{
		if (!clsScreen::CheckPermitionRight(clsUser::enPermistions::pLoginRegister))
			return;

		std::vector <clsUser::stLoginRegister> vRegister = clsUser::GetUserLoginRegisterList();
		std::string Title = "\tLogin Register List Screen";
		std::string Subtitle = "\t     (" + std::to_string(vRegister.size())+") Registers";
		clsScreen::_DrawHeaderScreen(Title, Subtitle);
		std::cout << "\t---------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t|" << std::left << std::setw(30) << " Date" << std::right << " |" << std::left << std::setw(20) << " Username" << std::right << " |" << std::left << std::setw(20) << " Password" << std::right << " |" << std::left << std::setw(20) << " Permisstions" << std::right << " |" << std::endl;
		std::cout << "\t---------------------------------------------------------------------------------------------------" << std::endl;
		for (clsUser::stLoginRegister& i : vRegister)
		{
			_PrintLoginRegister(i);
		}
		std::cout << "\t---------------------------------------------------------------------------------------------------" << std::endl;

	}

public:

	static void ShowLoginRegister()
	{
		_ShowLoginRegister();
	}
};

