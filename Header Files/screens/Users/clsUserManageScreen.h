#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include "Header Files/core/clsUser.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUser.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateuserScreen.h"
#include "clsFindUserScreen.h"

class clsUserManageScreen : protected clsScreen
{
private:
    enum enManageUserMenu 
    { UsersList = 1, AddUser, DelteUser, UpdateUser, FindUser, MainMenu };
	
    static short _ReadOption()
    {
        return clsInputValidate::ReadPositiveNumberInRange<short> ("Choose an option [1-6]: ", 1, 6);
    }
    static void _GoBackToMainScreen()
    {
        std::cout << "Press any key to go back to main screen...";
        system("pause>0");
        ShowManageUserScreen();
    }
    static void _ShowUsersListScreen()
    {
        clsUsersListScreen::ShowUsersListScreen();
    }
    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }
    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    static void _ShowAddUserScreen()
    {
        clsAddNewUser::ShowAddNewUserScreen();
    }
    
    static void _PerformManageUsersOption(enManageUserMenu Option)
    {
        switch (Option)
        {
        case enManageUserMenu::UsersList:
            clsScreen::_ClearScreen();
            _ShowUsersListScreen();
            _GoBackToMainScreen();
            break;
        case enManageUserMenu::AddUser:
            clsScreen::_ClearScreen();
            _ShowAddUserScreen();
            _GoBackToMainScreen();
                break;
        case enManageUserMenu::DelteUser:
            clsScreen::_ClearScreen();
            _ShowDeleteUserScreen();
            _GoBackToMainScreen();
                break;
        case enManageUserMenu::FindUser:
            clsScreen::_ClearScreen();
            _ShowFindUserScreen();
            _GoBackToMainScreen();
                break;
        case enManageUserMenu::UpdateUser:
            clsScreen::_ClearScreen();
            _ShowUpdateUserScreen();
            _GoBackToMainScreen();
                break;
        case enManageUserMenu::MainMenu:
            break;
        default:
            break;
        }
    }
public:



	static void ShowManageUserScreen()
	{
        if (!clsScreen::CheckPermitionRight(clsUser::enPermistions::pList))
            return;

		std::string Title = "\t     Manage Users";
		clsScreen::_ClearScreen();
		clsScreen::_DrawHeaderScreen(Title);
        std::cout << "\t\t\t\t\t======================================\n";
        std::cout << "\t\t\t\t\t           Manage Users Menu\n";
        std::cout << "\t\t\t\t\t======================================\n\n";
        std::cout << "\t\t\t\t\t[1] List Users.\n";
        std::cout << "\t\t\t\t\t[2] Add New User.\n";
        std::cout << "\t\t\t\t\t[3] Delete User.\n";
        std::cout << "\t\t\t\t\t[4] Update User.\n";
        std::cout << "\t\t\t\t\t[5] Find User.\n";
        std::cout << "\t\t\t\t\t[6] Main Menu.\n";
        std::cout << "\n\t\t\t\t\t======================================\n";
        std::cout << "\t\t\t\t\t"; _PerformManageUsersOption((enManageUserMenu)_ReadOption());
	}

};

