#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsstring.h"
#include <fstream>
#include <string>
#include <vector>
class clsUtil
{
private:
        inline static std::vector <std::string> Ones = {
            "", "One ", "Two ", "Three ", "Four ",
            "Five ", "Six ", "Seven ", "Eight ", "Nine "
        };
        inline static std::vector <std::string> Teens = {
            "","Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ",
            "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "
        };
        inline static std::vector <std::string> Tens = {
            "","Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ",
            "Sixty ", "Seventy ", "Eighty ", "Ninety "
        };

        inline static std::vector <std::string> Scales = {
            "","Thousand ", "Million ", "Billion "
        };

        static int getOnes(int number)
        {
            return number % 10;
        }
        static int getTens(int number)
        {
            return (number / 10) % 10;
        }
        static int getHundred(int number)
        {

            return (number / 100) % 10;;
        }

        static std::string _ConvertNumberToWord(int number)
        {
            std::string result = "";
            int ones = getOnes(number);
            int tens = getTens(number);
            int hundred = getHundred(number);
            if (hundred == 0)
            {
                if (tens == 0 && ones == 0)
                    result += Ones.at(ones);
                else if (tens == 0 && ones != 0)
                {
                    result += Ones.at(ones);
                }
                else if (tens == 1 && ones != 0)
                {
                    result += Teens.at(ones);
                }
                else if (tens != 0 && ones == 0)
                {
                    result += Tens.at(tens);
                }
                else if (tens > 1 && ones > 0)
                {
                    result += Tens.at(tens) + Ones.at(ones);
                }
            }
            else
            {
                if (tens == 0 && ones != 0)
                {
                    result += Ones.at(hundred) + "Hundred " + Ones.at(ones);
                }
                else if (tens == 1 && ones != 0)
                {
                    result += Ones.at(hundred) + "Hundred " + Teens.at(ones);
                }
                else if (tens != 0 && ones == 0)
                {
                    result += Ones.at(hundred) + "Hundred " + Tens.at(tens);
                }
                else if (tens > 1 && ones > 0)
                {
                    result += Ones.at(hundred) + "Hundred " + Tens.at(tens) + Ones.at(ones);
                }
                else if (tens == 0 && ones == 0)
                {
                    result += Ones.at(hundred) + "Hundred ";
                }

            }
            return result;
        }

        


    
public:
     enum IsPrime {
        Prime,
        NotPrime
    };
     enum enCharactersType {
        None = 0,        // لا شيء
        SmallLetter = 1,   // الحروف الصغيرة
        CapitalLetter = 2,   // الحروف الكبيرة
        Digit = 3,   // الأرقام
        Space = 4,   // المسافات
        Punctuation = 5,   // علامات الترقيم
        MixChar = 6,
        All = 7
    };
    static int ReverseNumber(int number) {
        int reminder = 0, reversedNumber = 0;
        while (number > 0) {
            reminder = number % 10;
            number = number / 10;
            reversedNumber = reversedNumber * 10 + reminder;
        }
        return reversedNumber;
    }

    static bool CheckIfPalindrome(int number) {
        return ReverseNumber(number) == number;
    }

    static bool CheckIfIsPerfectNumber(int number) {
        if (number <= 1) {
            return false;
        }

        int sum = 0;
        for (int i = 1; i < number; i++) {
            if (number % i == 0) {
                sum += i;
            }
        }
        return sum == number;
    }

    static IsPrime IsPrimeNumber(int number) {
        if (number <= 1) {
            return IsPrime::NotPrime;
        }
        for (int i = 2; i * i <= number; i++) {
            if (number % i == 0) {
                return IsPrime::NotPrime;
            }
        }
        return IsPrime::Prime;
    }

    static int FrequencyInNumber(int number, int DigitTarget) {
        int reminder = 0;
        int frequency = 0;
        do {
            reminder = number % 10;
            number /= 10;
            if (reminder == DigitTarget) {
                frequency++;
            }
        } while (number != 0);

        return frequency;
    }

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }
    static int GenRandomNumber(int from, int to) {
        return rand() % (to - from + 1) + from;
    }

    static int SumNumbersInArray(int arr[], int arrLength) {
        int Sum = 0;
        for (int i = 0; i < arrLength; i++) {
            Sum += arr[i];
        }
        return Sum;
    }
    static float AverageOfNumbersInArray(int arrElements[], int arrLength) {
        if (arrLength == 0) return 0;
        return (float)SumNumbersInArray(arrElements, arrLength) / arrLength;
    }
    static int MinNumberInArray(int arrElements[], int arrLength) {

        if (arrLength == 0) return 0;
        int minNumber = arrElements[0];
        for (int i = 1; i < arrLength; i++) {
            if (arrElements[i] < minNumber) {
                minNumber = arrElements[i];
            }
        }
        return minNumber;
    }

    static int MaxNumberInArray(int arr[], int arrLength) {
        if (arrLength == 0) return 0; // التعامل مع المصفوفة الفارغة
        int maxNumber = arr[0];
        for (int i = 1; i < arrLength; i++) {
            if (arr[i] > maxNumber) {
                maxNumber = arr[i];
            }
        }
        return maxNumber;
    }

    static  int FindNumberPositionInArray(int arr[], int arrLength, int Target) {
        for (int i = 0; i < arrLength; i++) {
            if (Target == arr[i]) {
                return i;
            }
        }
        return -1;
    }

    static  bool IsNumberInArray(int arr[], int arrLength, int NumberToSearchFor) {
        return FindNumberPositionInArray(arr, arrLength, NumberToSearchFor) != -1;
    }

    static int CountEvenNumbersInArray(int arr[], int arrLength) {
        int counter = 0;
        for (int i = 0; i < arrLength; i++) {
            if (arr[i] % 2 == 0) {
                counter++;
            }
        }
        return counter;
    }

    static int CountOddNumbersInArray(int arr[], int arrLength) {
        int counter = 0;
        for (int i = 0; i < arrLength; i++) {
            if (arr[i] % 2 != 0) {
                counter++;
            }
        }
        return counter;
    }

    static int CountPositiveNumbersInArray(int arr[], int arrLength) {
        int counter = 0;
        for (int i = 0; i < arrLength; i++) {
            if (arr[i] > 0) {
                counter++;
            }
        }
        return counter;
    }

    static int TimesRepeatedInArray(int arrElements[], int arrLength, int Digit) {
        int counter = 0;
        for (int i = 0; i < arrLength; i++) {
            if (Digit == arrElements[i]) {
                counter++;
            }
        }
        return counter;
    }

    static void AddArrayElements(int number, int arr[], int& arrLength) {
        arrLength++;
        arr[arrLength - 1] = number;
    }

    static void CopyDistinctArray(int arr[], int arrLength, int arr2[], int& arrLength2) {
        for (int i = 0; i < arrLength; i++) {
            if (!IsNumberInArray(arr2, arrLength2, arr[i])) {
                AddArrayElements(arr[i], arr2, arrLength2);
            }
        }
    }

    static bool IsPalindromArray(int arrElements[], int arrLength) {
        for (int i = 0; i < arrLength / 2; i++) {
            if (arrElements[i] != arrElements[arrLength - 1 - i]) {
                return false;
            }
        }

        return true;
    }

    static void ShuffleArrayElements(int arrElements[], int arrLength) {
        for (short i = 0; i < arrLength; i++) {
            std::swap(arrElements[GenRandomNumber(1, arrLength) - 1], arrElements[GenRandomNumber(1, arrLength) - 1]);
        }
    }

   static char GenerateCharacter(enCharactersType enCharType) {
        switch (enCharType) {
        case Punctuation:
            return char(GenRandomNumber(33, 47));
        case SmallLetter:
            return char(GenRandomNumber(97, 122));
        case CapitalLetter:
            return char(GenRandomNumber(65, 90));
        case Digit:
            return char(GenRandomNumber(48, 57));
        case MixChar:
            return char(GenRandomNumber(65, 122));
        default:
            return ' '; // إرجاع قيمة افتراضية
        }
    }

    static std::string GenerateWord(enCharactersType enCharType, int wordLength) {
        std::string word = "";
        for (int i = 0; i < wordLength; i++) {
            word += GenerateCharacter(enCharType);
        }
        return word;
    }

    static std::string GenerateKey(enCharactersType enCharType, int wordLength) {
        std::string key;
        key = GenerateWord(enCharType, wordLength) + "-";
        key += GenerateWord(enCharType, wordLength) + "-";
        key += GenerateWord(enCharType, wordLength) + "-";
        key += GenerateWord(enCharType, wordLength);
        return key;
    }
    static void PrintArray(int arr[], int arrLength) {
        for (int i = 0; i < arrLength; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    static void PrintArray(std::string arr[], int arrLength) {
        for (int i = 0; i < arrLength; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    static void FillArrayWithRandomNumbers(int arr[], int& arrLength, int From, int To) {
        std::cout << "enter array length: ";
        std::cin >> arrLength;
        for (int i = 0; i < arrLength; i++) {
            arr[i] = GenRandomNumber(From, To);
        }
    }
    static void FillArrayWithRandomWord(std::string arr[], int& arrLength,enCharactersType enCharType, int WordLength) {
        std::cout << "enter array length: ";
        std::cin >> arrLength;
        for (int i = 0; i < arrLength; i++) {
            arr[i] = GenerateWord(enCharType, WordLength);
        }
    }


    static void Swap(int& A, int& B)
    {
        int temp = A;
        A = B;
        B = temp;
    }
    static void Swap(clsDate& Date1, clsDate& Date2)
    {
        clsDate temp = Date1;
        Date1 = Date2;
        Date2 = temp;
    }
    

    static void RemoveElement(int arr[], int& arrLength, int Target)
    {
        int StartPoint = FindNumberPositionInArray(arr, arrLength, Target);
        if (StartPoint != -1)
        {
            for (int i = StartPoint; i < arrLength - 1; i++)
            {

                arr[i] = arr[i + 1];

            }
            arrLength--;

        }
    }

    static void SortArray(int arr[], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            int minIndex = i;
            for (int j = i; j < arrLength; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]);
        }
    }

    static void RemoveDuplicateElements(int arr[], int& arrLength)
    {
        SortArray(arr, arrLength);
        short UniqIndex = 0;
        for (int i = 0; i < arrLength; i++)
        {
            if (arr[i] != arr[UniqIndex])
            {
                UniqIndex++;
                arr[UniqIndex] = arr[i];
            }
        }
        arrLength = UniqIndex + 1;
    }

    static void LoadFileDataToVector(const std::string& FilePath, std::vector <std::string>& vlines)
    {
        vlines.clear();
        std::fstream Myfile(FilePath, std::ios::in);
        std::string Line;

        if (Myfile.is_open())
        {
            while (getline(Myfile, Line))
            {
                vlines.push_back(Line);
            }
            Myfile.close();
        }
        else
        {
            std::cout << "Error: Could not open file \"" << FilePath << "\" for reading.\n";
            return;
        }
    }

    static void AppendLinesInFile(const std::string& FilePath, std::vector <std::string>& vlines)
    {
        std::fstream Myfile(FilePath, std::ios::out | std::ios::app);//append mod
        if (Myfile.is_open())
        {
            for (std::string& i : vlines)
            {
                Myfile << i << "\n";
            }
            Myfile.close();
        }
        else
        {
            std::cout << "Error: Could not open file \"" << FilePath << "\" for appending.\n";
            return;
        }
    }
    static void SaveVectorToFile(const std::string& FilePath, std::vector <std::string>& vlines)
    {
        std::fstream Myfile(FilePath, std::ios::out);//append mod
        if (Myfile.is_open())
        {
            for (std::string& i : vlines)
            {
                if (!i.empty())
                    Myfile << i << std::endl;
            }
            Myfile.close();

        }
        else
        {
            std::cout << "Error: Could not open file \"" << FilePath << "\" for writing.\n";
        }

    }

    static void PrintfileContent(const std::string& FilePath)
    {
        std::fstream Myfile(FilePath, std::ios::in);
        if (Myfile.is_open())
        {
            std::string line;
            while (getline(Myfile, line))
            {
                std::cout << line << std::endl;
            }
            Myfile.close();
        }
        else
        {
            std::cout << "Error: Could not open file \"" << FilePath << "\" for reading.\n";
            return;
        }
    }

    static void DeleteRecordFromFile(const std::string& FilePath, std::string Record)
    {
        std::vector <std::string> vlines;
        LoadFileDataToVector(FilePath, vlines);
        for (std::string& i : vlines)
        {
            if (i == Record)
                i.clear();
        }
        SaveVectorToFile(FilePath, vlines);
    }

    static void UpdateRecordInFile(const std::string& FilePath, std::string Record, std::string UpdatedRecord)
    {
        std::vector <std::string> vlines;
        LoadFileDataToVector(FilePath, vlines);
        for (std::string& i : vlines)
        {
            if (i == Record)
            {
                i = UpdatedRecord;
                break;
            }
        }
        SaveVectorToFile(FilePath, vlines);
    }
    static void UpdateMultiRecordInFile(short NumberOfRecords, const std::string& FilePath)
    {

        std::string Record;
        std::string UpdatedRecord;

        for (int i = 1; i <= NumberOfRecords; i++)
        {
            std::cout << "enter record n[" << i << "]: ";
            std::getline(std::cin, Record);


            std::cout << "enter updated record n[" << i << "]: ";
            std::getline(std::cin, UpdatedRecord);


            UpdateRecordInFile(FilePath, Record, UpdatedRecord);
        }
    }

    static std::string Tabs(int NumberOfTabs)
    {
        std::string Result = "";
        for (int i = 1; i <= NumberOfTabs; i++)
        {
            Result += "\t";
        }
        return Result;
    }

    static std::string EncryptionText(std::string Text, short EncryptionKey)
    {
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char(int(Text[i]) + EncryptionKey);
        }
        return Text;
    }
    static std::string DecryptionText(std::string Text, short DecryptionKey)
    {
       for (int i = 0; i < Text.length(); i++)
       {
           Text[i] = char(int(Text[i]) - DecryptionKey);
       }
       return Text;
    }


   static void FillMatrixWithRandomNumbers(int arr[3][3], int Rows, int Cols, short From, short To)
   {
       for (int i = 0; i < Rows; i++)
       {

           for (int j = 0; j < Cols; j++)
           {
               arr[i][j] = GenRandomNumber(From, To);
           }
       }

   }

   static void PrintMatrix(int arr[3][3], int Rows, int Cols, short PrintFormat = 0)
   {
       for (int i = 0; i < Rows; i++)
       {

           for (int j = 0; j < Cols; j++)
           {
               if (PrintFormat == 0)
                   std::cout << std::left << std::setw(4) << arr[i][j] << "  ";
               else
                   printf("%0*d\t", 2, arr[i][j]);
           }
           std::cout << std::endl;
       }
   }

   static int SumOfRowInMatrix(int arr[3][3], int Row, int Cols)
   {
       int sum = 0;

       for (int i = 0; i < Cols; i++)
       {
           sum += arr[Row][i];
       }
       return sum;
   }

   static void FillRowSumInArray(int arr[], int Matrix[3][3], int Rows, int Cols)
   {

       for (int i = 0; i < Cols; i++)
       {
           arr[i] = SumOfRowInMatrix(Matrix, Rows, i);
       }

   }

   static int ColsSum(int Matrix[3][3], int Rows, int Cols)
   {
       int sum = 0;
       for (int i = 0; i < Rows; i++)
       {
           sum += Matrix[i][Cols];

       }
       return sum;
   }

   static void FillColSumInArray(int arr[], int Matrix[3][3], int Rows, int Cols)
   {

       for (int i = 0; i < Cols; i++)
       {
           arr[i] = ColsSum(Matrix, Rows, i);
       }

   }
   static void MultiplyTwoMatirces(int Matrix1[3][3], int Matrix2[3][3], int Matrix3[3][3], int Rows, int Cols)
   {
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               Matrix3[i][j] = (Matrix1[i][j] * Matrix2[i][j]);
           }
       }
   }

   static int MatrixSum(int Matrix[3][3], int Rows, int Cols)
   {
       int sum = 0;
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               sum += Matrix[i][j];
           }
       }
       return sum;
   }

   static bool IsMatricesSumEqual(int Matrix1[3][3], int Matrix2[3][3], int Rows, int Cols)
   {
       return MatrixSum(Matrix1, Rows, Cols) == MatrixSum(Matrix2, Rows, Cols);
   }

   static void PrintMatricesSumEqualResult(int Matrix1[3][3], int Matrix2[3][3], int Rows, int Cols)
   {
       bool IsEqual = IsMatricesSumEqual(Matrix1, Matrix2, Rows, Cols);
       (IsEqual) ? std::cout << "\n\nYes: matrices are equal! \n" : std::cout << "\n\nNo: matrices aren't equal! \n";
   }

   static bool IsMatricesTypicalEqual(int Matrix1[3][3], int Matrix2[3][3], int Rows, int Cols)
   {
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (Matrix1[i][j] != Matrix2[i][j])
                   return false;
           }
       }
       return true;
   }

   static bool IsIndentityMatrix(int Matrix[3][3], int Rows, int Cols)
   {

       if (Rows != Cols)
           return false;


       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (i == j && Matrix[i][j] != 1 || i != j && Matrix[i][j] != 0)
                   return false;
           }
       }
       return true;
   }

   static bool IsScalarMatrix(int Matrix[3][3], int Rows, int Cols)
   {
       if (Rows != Cols)
           return false;
       if (IsIndentityMatrix(Matrix, Rows, Cols))
           return true;
       short SpecialValue = Matrix[0][0];

       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (i == j && Matrix[i][j] != SpecialValue || i != j && Matrix[i][j] != 0)
                   return false;
           }
       }
       return true;
   }
   static short CountNumberInMatrix(int Matrix[3][3], int Rows, int Cols, short Target)
   {
       short counter = 0;
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (Matrix[i][j] == Target)
                   counter++;
           }
       }
       return counter;
   }

   static bool IsSparseMatrix(int Matrix[3][3], int Rows, int Cols)
   {
       return CountNumberInMatrix(Matrix, Rows, Cols, 0) > Rows * Cols / 2;
   }

   static bool IsNumberExistsInMatrix(int Matrix[3][3], int Rows, int Cols, int Target)
   {
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (Matrix[i][j] == Target)
                   return true;
           }
       }
       return false;
   }

   static void PrintIntersectedNumbersInMatrices(int Matrix1[3][3], int Matrix2[3][3], int Rows, int Cols)
   {

       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (IsNumberExistsInMatrix(Matrix2, Rows, Cols, Matrix1[i][j]))
                   std::cout << std::left << std::setw(3) << Matrix1[i][j] << "   ";
           }
       }

   }

   static short FindMinNumberInMatrix(int Matrix[3][3], int Rows, int Cols)
   {
       short MinNumber = Matrix[0][0];
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (MinNumber > Matrix[i][j])
               {
                   MinNumber = Matrix[i][j];
               }
           }

       }
       return MinNumber;

   }

   static short FindMaxNumberInMatrix(int Matrix[3][3], int Rows, int Cols)
   {
       short MaxNumber = Matrix[0][0];
       for (int i = 0; i < Rows; i++)
       {
           for (int j = 0; j < Cols; j++)
           {
               if (MaxNumber < Matrix[i][j])
               {
                   MaxNumber = Matrix[i][j];
               }
           }

       }
       return MaxNumber;

   }
   static bool IsPalindromMatrix(int Matrix[3][3], int Rows, int Cols)
   {
       for (int i = 0; i < Rows; i++)
       {

           for (int j = 0; j < Cols / 2; j++)
           {
               if (Matrix[i][j] != Matrix[i][Cols - j - 1])
               {
                   return false;
               }
           }
       }
       return true;
   }

    static std::string numberToWords(int num)
   {
       if (num < 0 || num > INT32_MAX)
           return "";
       else if (num == 0)
           return "Zero";
       std::string result = "";
       int TempeNumber = num;
       std::vector <std::string> vResults;

       int counter = 0;
       do
       {
           TempeNumber = num % 1000;
           num = num / 1000;

           if (TempeNumber != 0)
               result = _ConvertNumberToWord(TempeNumber) + Scales.at(counter);

           vResults.push_back(result);
           result.clear();
           counter++;
       } while (num != 0);
       for (int i = static_cast<int>(vResults.size() - 1); i >= 0; i--)
       {
           result += vResults.at(i);
       }
       return  result.substr(0, result.size() - 1);
   }
};

