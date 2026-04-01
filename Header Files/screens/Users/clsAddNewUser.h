#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Header Files/lib/clsString.h"
#include "Header Files/lib/clsInputValidate.h"
#include "Header Files/screens/clsScreen.h"
#include <cctype>
#include "Header Files/core/clsUser.h"
#include <vector>
#include "Header Files/core/clsPermistions.h"

class clsAddNewUser : protected clsScreen 
{
private:

    static void _ReadUserInfo(clsUser& user)
    {

        user.SetFirstName(clsInputValidate::ReadString("Enter first name: "));
        user.SetLastName(clsInputValidate::ReadString("Enter last name: "));
        user.SetPassword(clsInputValidate::ReadString("Enter password: "));
        user.SetPhone(clsInputValidate::ReadString("Enter phone number: "));
        user.SetEmail(clsInputValidate::ReadString("Enter e-mail: "));
        user.SetPermisstion(clsPermistions::_ReadPermisions());
    }
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

    static void _AddNewUserScreen()
    {
        clsScreen::_ClearScreen();
        std::string Title = "\t   Add New User Screen";
        clsScreen::_DrawHeaderScreen(Title);
        std::string UserName = clsInputValidate::ReadString("Enter username: ");
        while (clsUser::isUserExist(UserName))
        {
            clsScreen::_ClearScreen();
            clsScreen::_DrawHeaderScreen(Title);
            if (toupper(clsInputValidate::ReadLetter("This user already exist, try again? [Y/N]: ")) == 'Y')
                UserName = clsInputValidate::ReadString("R-enter username: ");
            else
                return;
        }
        clsScreen::_ClearScreen();
        clsScreen::_DrawHeaderScreen(Title);
        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);
        clsScreen::_ClearScreen();
        clsScreen::_DrawHeaderScreen(Title);
        clsUser::enSaveResult SaveResult = NewUser.save();
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
            _PrintUser(NewUser);
            break;
        case clsUser::enSaveResult::svFailedFileProblem:
            std::cout << "\n\nsave failed there is file problem\n\n";
            break;
        }
    }
public:
    static void ShowAddNewUserScreen()
    {
        _AddNewUserScreen();
    }
};

