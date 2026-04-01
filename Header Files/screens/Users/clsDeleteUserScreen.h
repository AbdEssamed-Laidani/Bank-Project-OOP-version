#pragma once
#include <iostream>
#include "Header Files/core/clsUser.h"
#include "Header Files/lib/clsInputValidate.h"
#include <string>
#include "Header Files/screens/clsScreen.h"
#include <cctype>
class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser& user)
    {
        std::cout << "User Card: \n";
        std::cout << "--------------------------------\n";
        std::cout << "First Name: " << user.GetFirstName() << std::endl;
        std::cout << "Last Name: " << user.GetLastName() << std::endl;
        std::cout << "Full Name: " << user.GetFullName() << std::endl;
        std::cout << "Phone: " << user.GetPhone() << std::endl;
        std::cout << "E-mail: " << user.GetEmail() << std::endl;
        std::cout << "Username: " << user.GetUsername() << std::endl;
        std::cout << "Password: " << user.GetPassword() << std::endl;
        std::cout << "Pemisions: " << user.GetPermistions() << std::endl;
        std::cout << "--------------------------------\n";
    }

	static void _DeleteUser()
	{
        std::string Title = "\t   Delete User";
        clsScreen::_DrawHeaderScreen(Title);
        std::string Username = clsInputValidate::ReadString("Enter username: ");
        while (!clsUser::isUserExist(Username))
        {
            clsScreen::_ClearScreen();
            clsScreen::_DrawHeaderScreen(Title);
            if (toupper(clsInputValidate::ReadLetter("This user doesn't exist, search again? [Y/N]: ")) == 'Y')
                Username = clsInputValidate::ReadString("R-enter username: ");
            else
                return;
        }
        clsUser UserToDelete = clsUser::Find(Username);
        _PrintUser(UserToDelete);
        if (toupper(clsInputValidate::ReadLetter("Are you sure? [Y/N]: ")) == 'Y')
        {
            if (UserToDelete.Delete())
            {
                std::cout << "User deleted successfuly!\n";
                _PrintUser(UserToDelete);
            }
            else
            {
                std::cout << "Error user was not deleted successfuly!\n";
                return;
            }
        }
        else
            return;
	}


public:
	static void ShowDeleteUserScreen()
	{
        _DeleteUser();
	}


};

