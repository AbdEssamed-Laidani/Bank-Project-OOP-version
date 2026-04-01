#pragma once
#include <iostream>
#include "Header Files/core/clsUser.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include <cctype>
#include <string>

class clsFindUserScreen : protected clsScreen
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
    static void _FindUser()
    {
        std::string Title = "\t   Find User";
        clsScreen::_DrawHeaderScreen(Title);
        std::string Username = clsInputValidate::ReadString("Enter username: ");

        while (!clsUser::isUserExist(Username))
        {
            clsScreen::_ClearScreen();
            clsScreen::_DrawHeaderScreen(Title);
            if (toupper(clsInputValidate::ReadLetter("User not found, search again? [Y/N]: ")) == 'Y')
                Username = clsInputValidate::ReadString("R-enter username: ");
            else
                return;
        }
        clsUser user = clsUser::Find(Username);
        if (!user.isEmpty())
        {
            std::cout << "\nUser found :-)\n";
        }
        else
        {
            std::cout << "\nUser was not found!\n";
        }
        _PrintUser(user);


    }


public:

    static void ShowFindUserScreen()
    {
        _FindUser();
    }
};

