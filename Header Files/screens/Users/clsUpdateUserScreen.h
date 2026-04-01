#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/core/clsPermistions.h"
#include "Header Files/core/clsUser.h"
class clsUpdateUserScreen : protected clsScreen
{
private:
    inline static std::string Title = "\t   Update User";

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
    static void _ReadUserInfo(clsUser& user)
    {
        clsScreen::_ClearScreen();
        clsScreen::_DrawHeaderScreen(Title);
        std::cout << "User Card:\n";
        std::cout << "----------------------------\n";
        user.SetFirstName(clsInputValidate::ReadString("Enter first name: "));
        user.SetLastName(clsInputValidate::ReadString("Enter last name: "));
        user.SetPassword(clsInputValidate::ReadString("Enter password: "));
        user.SetPhone(clsInputValidate::ReadString("Enter phone number: "));
        user.SetEmail(clsInputValidate::ReadString("Enter e-mail: "));
        user.SetPermisstion(clsPermistions::_ReadPermisions());
        std::cout << "\n----------------------------\n";
    }
    static void _Update()
    {
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
        clsUser UserToUpdate = clsUser::Find(Username);
        _PrintUser(UserToUpdate);
        if (toupper(clsInputValidate::ReadLetter("Are you sure? [Y/N]: ")) == 'Y')
        {
            _ReadUserInfo(UserToUpdate);
            clsUser::enSaveResult SaveResult = UserToUpdate.save();
            switch (SaveResult)
            {
            case clsUser::enSaveResult::svFailedEmpty:
                std::cout << "\n\nsave failed empty object!\n\n";
                break;
            case clsUser::enSaveResult::svFailedExist:
                std::cout << "\n\nsave failed user already exist!\n\n";
                break;
            case clsUser::enSaveResult::svSucceded:
                std::cout << "\n\nsave succeded!\n\n";
                _PrintUser(UserToUpdate);
                break;
            case clsUser::enSaveResult::svFailedFileProblem:
                std::cout << "\n\nsave failed there is file problem\n\n";
                break;
            }
        }
        else
            return;

    }

public:
	static void ShowUpdateUserScreen()
	{
        _Update();
	}
};

