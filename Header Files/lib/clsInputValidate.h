#pragma once
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include "clsDate.h"

class clsInputValidate
{
public:
    template <typename T> static T ReadNumber(std::string message, std::string ErrorMessage = "Invlaid input, re-enter: ") {
        T number = 0;
        std::cout << message;
        std::cin >> number;
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << ErrorMessage;
            std::cin >> number;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return number;
    }

    template <typename T> static T ReadPositiveNumber(std::string message, std::string ErrorMessage = "Invlaid input, re-enter: ") {
        T number = 0;
        do 
        {
            number =  ReadNumber<T>(message);
            if (number <= 0)
                std::cout << ErrorMessage;
        } while (number <= 0);

        return number;
    }
 
    template <typename T> static T ReadPositiveNumberInRange(std::string message, T From, T To, std::string ErrorMessage = "Invlaid input, re-enter: ") {
        T number = 0;
        do
        {
            number = ReadNumber<T>(message);
            if (IsNumberInRange(number, From, To))
            {
                return number;
            }
            std::cout << ErrorMessage << std::endl;
        } while (true);


        return number;
    }

    template <typename T> static bool IsNumberInRange(const T& number, const T& from, const T& to)
    {
        return number >= from && number <= to;
    }

    static bool IsDateBetween(const clsDate& CurrentDate, const clsDate& Date1,const clsDate &Date2)
    {
        return (clsDate::IsDate1AfterDate2(CurrentDate, Date1) || clsDate::IsDate1EqualToDate2(CurrentDate, Date1)) && (clsDate::IsDate1LessThenDate2(CurrentDate, Date2) || clsDate::IsDate1EqualToDate2(CurrentDate, Date2));
    }

    static bool isValidDate(const clsDate &Date)
    {
        return clsDate::isValidDate(Date);
    }

    static std::string ReadString(const std::string& message)
    {
        std::string text = "";
        std::cout << message;
        std::getline(std::cin >> std::ws, text);
        return text;
    }

    static char ReadLetter(const std::string &Message) {
        char letter;
        std::cout << Message;
        std::cin >> letter;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return letter;
    }
};