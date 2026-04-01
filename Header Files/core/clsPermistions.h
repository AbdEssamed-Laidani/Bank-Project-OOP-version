#pragma once
#include <iostream>
#include "Header Files/lib/clsInputValidate.h"
#include <string>
#include <cctype>
#include "Header Files/core/clsUser.h"
#include "Header Files/screens/clsScreen.h"
#include <vector>
class clsPermistions : protected clsScreen
{

public:
    static int _ReadPermisions()
    {
        int permistions = 0;


        if (toupper(clsInputValidate::ReadLetter("Do you want to give all permissions? [Y/N]: ")) == 'Y')
            return clsUser::enPermistions::All;
        else
        {
            std::vector < std::string> vMenuItems = { "Show Client List","Add New Client",
            "Delete Client","Update Client Info","Find Client","Transaction","Manage Users",
                "Login Register"};
            std::vector < clsUser::enPermistions > vPermisions = { clsUser::enPermistions::pList, clsUser::enPermistions::pAdd,
                clsUser::enPermistions::pDelete, clsUser::enPermistions::pUpdate, clsUser::enPermistions::pFind,
                clsUser::enPermistions::pTransactions, clsUser::enPermistions::pManage,clsUser::enPermistions::pLoginRegister };

            for (short i = 0; i < (int)vMenuItems.size(); i++)
            {
                if (toupper(clsInputValidate::ReadLetter("Do you want to give access to \"" +
                    vMenuItems.at(i) + "\" ? [Y / N] : ")) == 'Y')
                {
                    permistions |= vPermisions.at(i);
                }
            }
        }
        return permistions;
    }

};

