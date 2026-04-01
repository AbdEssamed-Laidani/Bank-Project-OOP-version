#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <iomanip>
#include "clsString.h"
#include "clsInputValidate.h"

class clsDate
{
private:
    short _Year;
    short _Month;
    short _Day;
    void ConvertStringToDate(std::string DateText, std::string Delimiter = "/")
    {

        std::vector <std::string> vDate = clsString::SplitText(DateText, Delimiter);
        _Day = stoi(vDate.at(0));
        _Month = stoi(vDate.at(1));
        _Year = stoi(vDate.at(2));
    }
   
    

    void DayOfYearToDate(short DayOrderInYear, short Year)
    {
        short MaxDays = clsDate::NumberOfDaysInYear(Year);
        if (DayOrderInYear < 1 || DayOrderInYear > MaxDays)
        {
            std::cout << "Invalid DayOfYear value for this year";
            _Year = Year;
            _Month = 1;
            _Day = 1;
            return;
        }
        short MonthCounter = 1;
        short NumberOfDayInMonth = clsDate::NumberOfDaysInMonth(Year, MonthCounter);
        while (DayOrderInYear > NumberOfDayInMonth)
        {
            DayOrderInYear -= NumberOfDayInMonth;
            MonthCounter++;
            NumberOfDayInMonth = clsDate::NumberOfDaysInMonth(Year, MonthCounter);
        }
        _Day = DayOrderInYear;
        _Month = MonthCounter;
        _Year = Year;
    }


public:

    clsDate()
    {
        GetSystemDate();
    }
    clsDate(std::string Date, std::string Delimiter = "/")
    {
        ConvertStringToDate(Date, Delimiter);
    }
    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }
    clsDate(short DayOrderInYear, short Year)
    {
        DayOfYearToDate(DayOrderInYear, Year);
    }
    // propertie set and get:

    void setDay(short Day)
    {
        _Day = Day;
    }
    short GetDay()
    {
        return _Day;
    }
    void setMonth(short Month)
    {
        _Month = Month;
    }
    short GetMonth()
    {
        return _Month;
    }
    void setYear(short Year)
    {
        _Year = Year;
    }
    short GetYear()
    {
        return _Year;
    }
    void setDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    static std::string DateToString(clsDate& Date)
    {
        std::string date;
        date += std::to_string(Date.GetYear()) + "/" + std::to_string(Date.GetMonth()) + "/" + std::to_string(Date.GetDay());
        return date;
    }
    static std::string GetSystemDateString()
    {
        time_t currentTime = time(0);
        tm* strTime = localtime(&currentTime);
        unsigned Year = 0, Month = 0, Day = 0, Hour = 0, Min = 0, Sec = 0;

        Year = strTime->tm_year + 1900;
        Month = strTime->tm_mon + 1;
        Day = strTime->tm_mday;
        Hour = strTime->tm_hour;
        return std::to_string(Year) + "/" + std::to_string(Month) + "/" + std::to_string(Day) + " - "
            + std::to_string(Hour) + ":" + std::to_string(strTime->tm_min) + ":" + std::to_string(strTime->tm_sec);
    }

    static bool isLeapYear(short& Year)
    {
        return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
    }
    bool isLeapYear()
    {
        return isLeapYear(_Year);
    }

    void GetSystemDate()
    {

        time_t currentTime = time(0);
        tm* strTime = localtime(&currentTime);
        _Year = strTime->tm_year + 1900;
        _Month = strTime->tm_mon + 1;
        _Day = strTime->tm_mday;
    }
   
  
   static int NumberOfDaysInYear(short& Year)
   {
       return (clsDate::isLeapYear(Year)) ? 366 : 365;

   }
   int NumberOfDaysInYear()
   {
       return NumberOfDaysInYear(_Year);
   }



   static int NumberOfHoursInYear(short& Year)
   {
       return 24 * NumberOfDaysInYear(Year);
   }
   int NumberOfHoursInYear()
   {
       return NumberOfHoursInYear(_Year);
   }


  static int NumberOfMinutesInYear(short& Year)
   {
       return 60 * NumberOfHoursInYear(Year);
   }

  int NumberOfMinutesInYear()
  {
      return NumberOfMinutesInYear(_Year);
  }

   static int NumberOfSecondsInYear(short& Year)
   {

       return 60 * NumberOfMinutesInYear(Year);
   }
   int NumberOfSecondsInYear()
   {
       return NumberOfSecondsInYear(_Year);
   }



  static int NumberOfDaysInMonth( clsDate Date)
   {
       if (Date._Month < 1 || Date._Month>12)
           return 0;
       return (Date._Month == 2) ? (clsDate::isLeapYear(Date._Year) ? 29 : 28) : (Date._Month == 4 || Date._Month == 6 || Date._Month == 9 || Date._Month == 11) ? 30 : 31;
   }
  static int NumberOfDaysInMonth(short Year,short Month)
  {
      if (Month < 1 || Month>12)
          return 0;
      return (Month == 2) ? (clsDate::isLeapYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
  }

   int NumberOfDaysInMonth()
   {
       return NumberOfDaysInMonth(*this);
   }

   static int NumberOfHoursInMonth(const clsDate &Date)
   {
       return 24 * NumberOfDaysInMonth(Date);
   }
   int NumberOfHoursInMonth()
   {
       return NumberOfHoursInMonth(*this);
   }




   static int NumberOfMinutesInMonth(const clsDate &Date)
   {
       return 60 * NumberOfHoursInMonth(Date);
   }

   int NumberOfMinutesInMonth()
   {
       return NumberOfMinutesInMonth(*this);
   }


  static int NumberOfSecondsInMonth(const clsDate &Date)
   {
       return 60 * NumberOfMinutesInMonth(Date);
   }
  int NumberOfSecondsInMonth()
  {
      return NumberOfSecondsInMonth(*this);
  }


   enum DaysOfWeek
  {
      Sunday = 0,
      Monday,
      Tuesday,
      Wednesday,
      Thursday,
      Friday,
      Saturday
  };

  static DaysOfWeek FindOrderOfDay(clsDate Date)
  {
      int a, y, m;
      short DayNumber;
      a = (14 - Date._Month) / 12;
      y = Date._Year - a;
      m = Date._Month + 12 * a - 2;

      DayNumber = (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
      return static_cast<DaysOfWeek>(DayNumber);
  }
  DaysOfWeek FindOrderOfDay(short Year, short Month, short Day)
  {
      int a, y, m;
      short DayNumber;
      a = (14 - Month) / 12;
      y = Year - a;
      m = Month + 12 * a - 2;

      DayNumber = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
      return static_cast<DaysOfWeek>(DayNumber);
  }

  DaysOfWeek FindOrderOfDay()
  {
      return FindOrderOfDay(*this);
  }

  static std::string NameOfDay(DaysOfWeek DayName)
  {
      switch (DayName)
      {
      case Sunday:
          return "Sunday";
      case Monday:
          return "Monday";

      case Tuesday:
          return "Tuesday";

      case Wednesday:
          return "Wednesday";

      case Thursday:
          return "Thursday";

      case Friday:
          return"Friday";
      case Saturday:
          return "Saturday";
      default:
          return "Invalid Day";

      }
  }

  static std::string NameOfMonth(short MonthNumber)
  {
      std::string arrMonths[] =
      {
          "Jan", "Feb", "Mar", "Apr", "May", "Jun",
          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
      };

      return arrMonths[MonthNumber - 1];
  }

  std::string NameOfMonth()
  {
      return NameOfMonth(_Month);
  }

  static void PrintDays()
  {
      std::string arrDays[] =
      {
          "  Sun", "  Mon", "  Tue", "  Wed", "  Thu", "  Fri", "  Sat"
      };
      std::cout << arrDays[0] << arrDays[1] << arrDays[2] << arrDays[3] << arrDays[4] << arrDays[5] << arrDays[6] << std::endl;

  }
  static void PrintCalendar( short Year,  short Month)
   {
      int NumberOfDaysInMonth = clsDate::NumberOfDaysInMonth(Year, Month);
      short DayOrder = clsDate::FindOrderOfDay(clsDate(1, Month, Year));
      std::string MonthName = NameOfMonth(Month);

      std::cout << std::right << std::setw(16) << "______________" << MonthName << std::right << std::setw(17) << "________________\n";
      PrintDays();

      int i = 0;
      for (i = 0; i < DayOrder; i++)
      {
          std::cout << std::setw(5) << " ";
      }
      for (int j = 1; j <= NumberOfDaysInMonth; j++)
      {
          std::cout << std::right << std::setw(5) << j;
          if (++i == 7)
          {
              i = 0;
              std::cout << std::endl;
          }
      }
      std::cout << std::setw(39) << "\n  _________________________________\n";
  }

  void PrintYearCalander(const short& Year)
  {
      std::cout << std::setw(39) << "\n  _________________________________\n\n";
      std::cout << std::right << std::setw(25) << ("Calander - " + std::to_string(Year));
      std::cout << std::setw(39) << "\n  _________________________________\n";

      for (short i = 1; i <= 12; i++)
      {
          if (i == 12)
          {
              PrintCalendar(Year, i);
              break;
          }
          PrintCalendar(Year, i);
      }
  }

 static bool IsDate1LessThenDate2(const clsDate &Date1,const clsDate &Date2)
  {

      return (Date1._Year < Date2._Year) ? true : (Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month) ? true : (Date1._Month == Date2._Month) ? Date1._Day < Date2._Day : false : false;
  }
 bool IsDateLessThenDate2(clsDate Date2)
 {
     return IsDate1LessThenDate2(*this, Date2);
 }

 static bool IsDate1EqualToDate2(const clsDate& Date1, const clsDate& Date2)
  {

      return (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day);
  }
 bool IsDateEqualToDate2(clsDate Date2)
 {
     return IsDate1EqualToDate2(*this, Date2);
 }


 static bool IsLastDayInMonth(clsDate& Date1)
 {

     return (Date1._Day) == clsDate::NumberOfDaysInMonth(Date1);
 }


 static bool IsLastMonthInYear(const clsDate& Date1)
 {
     return (Date1._Month) == 12;
 }


 static clsDate IncreaseDateByOneDay(clsDate Date)
 {
     bool isLastDayInMonth = clsDate::IsLastDayInMonth(Date);
     bool isLastMonthInYear = clsDate::IsLastMonthInYear(Date);
     if (isLastDayInMonth && isLastMonthInYear)
     {
         Date._Day = 1;
         Date._Month = 1;
         Date._Year += 1;
         return Date;
     }
     else if (isLastDayInMonth && !isLastMonthInYear)
     {
         Date._Day = 1;
         Date._Month++;
         return Date;
     }
     else if (!isLastDayInMonth && isLastMonthInYear)
     {
         Date._Day++;

         return Date;
     }
     else if (!isLastDayInMonth && !isLastMonthInYear)
     {
         Date._Day++;
         return Date;
     }

     return Date;

 }

 clsDate IncreaseDateByOneDay()
 {
     return IncreaseDateByOneDay(*this);
 }

 static short GetDayOrderInYear(clsDate Date)
 {
     short TotalDays = 0;
     for (short i = 1; i < Date._Month; i++)
     {
         
         TotalDays += clsDate::NumberOfDaysInMonth(Date._Year, i);

     }

     return TotalDays + Date._Day;
 }

 short GetDayOrderInYear()
 {
     return GetDayOrderInYear(*this);
 }


 static bool IsFirstDayInMonth(const clsDate &Date)
 {
     return Date._Day == 1;
 }
 bool IsFirstDayInMonth()
 {
     return IsFirstDayInMonth(*this);
 }
 static bool IsFirstMonthInYear(const clsDate& Date)
 {
     return Date._Month == 1;
 }
 bool IsFirstMonthInYear()
 {
     return IsFirstMonthInYear(*this);
 }


 static short DiffrenceDaysBetweenDates( clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
 {
     short DiffrenceDays = 0;
     short Sign = 1;

     if (clsDate::IsDate1EqualToDate2(Date1, Date2))
     {
         return IncludeEndDay ? 1 : 0;
     }

     if (!clsDate::IsDate1LessThenDate2(Date1, Date2))
     {
         std::swap(Date1, Date2);
         Sign = -1;
     }

     while (clsDate::IsDate1LessThenDate2(Date1, Date2))
     {
         Date1 = clsDate::IncreaseDateByOneDay(Date1);
         DiffrenceDays++;
     }

     if (IncludeEndDay)
         DiffrenceDays++;

     return DiffrenceDays * Sign;
 }

 short DiffrenceDaysBetweenDates(clsDate Date2, bool IncludeEndDay = false)
 {
     return DiffrenceDaysBetweenDates(*this, Date2, IncludeEndDay);
 }


 static bool IsDayEndOfWeek(short DayOrder)
 {
     return DayOrder == 6;
 }
 bool IsDayEndOfWeek()
 {
     return IsDayEndOfWeek(clsDate::FindOrderOfDay());
 }

 static bool IsWeekEnd(short DayOrder)
 {
     return DayOrder == 5 || DayOrder == 6;
 }
 bool IsWeekEnd()
 {
     return IsWeekEnd(clsDate::FindOrderOfDay());
 }
 static bool IsItBusinessDay(short DayOrder)
 {
     return !IsWeekEnd(DayOrder);
 }
 bool IsItBusinessDay()
 {
     return IsItBusinessDay(clsDate::FindOrderOfDay());
 }
 static short DaysUntilEndOfWeek(clsDate Date)
 {

     return 6 - FindOrderOfDay(Date);

 }
 short DaysUntilEndOfWeek()
 {
     return DaysUntilEndOfWeek(*this);
 }

 static short DaysUntilEndOfMonth(clsDate Date)
 {
     short DaysInMnth = clsDate::NumberOfDaysInMonth(Date);
     clsDate Date2 = Date;
     Date2._Day = DaysInMnth;
     return clsDate::DiffrenceDaysBetweenDates(Date, Date2, true);
 }
 short DaysUntilEndOfMonth()
 {
     return DaysUntilEndOfMonth(*this);
 }

 static short DaysUntilEndOfYear(clsDate Date)
 {
     clsDate Date2 = Date;
     Date2._Day = 31;
     Date2._Month = 12;
     return clsDate::DiffrenceDaysBetweenDates(Date, Date2, true);
 }

 short DaysUntilEndOfYear()
 {
     return DaysUntilEndOfYear(*this);
 }

 static bool isValidDate(clsDate Date)
 {
     if (Date._Day < 1 || Date._Day > clsDate::NumberOfDaysInMonth(Date) || Date._Month < 1 || Date._Month > 12 || Date._Year < 1)
     {
         return false;
     }
     return true;
 }

 bool isValidDate()
 {
     return isValidDate(*this);
 }

 static clsDate DecreaseDateByOneDay(clsDate Date)
 {
     bool isFirstDayInMonth = clsDate::IsFirstDayInMonth(Date);
     bool isFirstMonthInYear = clsDate::IsFirstMonthInYear(Date);

     if (isFirstDayInMonth && isFirstMonthInYear)
     {
         Date._Month = 12;
         Date._Day = 31;
         Date._Year--;
     }
     else if (isFirstDayInMonth)
     {
         Date._Month--;
         Date._Day = clsDate::NumberOfDaysInMonth(Date._Year, Date._Month);
     }
     else
     {
         Date._Day--;
     }

     return Date;
 }

 clsDate DecreaseDateByOneDay()
 {
     return DecreaseDateByOneDay(*this);
 }

 static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
 {
     return !clsDate::IsDate1LessThenDate2(Date1, Date2) && !clsDate::IsDate1EqualToDate2(Date1, Date2);
 }
 bool IsDateAfterDate2(clsDate Date2)
 {
     return IsDate1AfterDate2(*this, Date2);
 }
  void print()
  {
      std::cout << _Day << "/" << _Month << "/" << _Year;

  }

    
};

